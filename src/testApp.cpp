#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    mouseDown = false;
    
    //OSC setup
    sender.setup("localhost", 7000);
    receiver.setup(7001);
    
    //create cellgrid;
    cellWidth = 40;
    rowLength = 16;
    cellNum = 3 * rowLength;
    int x = 0;
    int y = 0;
    for(int i = 0; i < cellNum; i++)
    {   
        ofVec2f pos;
        
        pos.set(x*(cellWidth+10)+10, ofGetHeight()/2-y*(cellWidth+10));
        cells.push_back(GridCell(pos, cellWidth, x, y));
        x++;
        if(x>rowLength-1)
        {
            x=0;
            y++;
        }
    }
    
    metronome = 10;
    currentBeat = 0;
    bpm = 120;
    
}

//--------------------------------------------------------------
void testApp::update(){
        
    //calculate time of one beat in millis
    float oneBeat = 60000.0/bpm;
    
    //calculate the number of elapsed beats, and calculate metronome position based on that...
    //todo: figure out a way of calculating the current beat correctly after a bpm change
    
    numberOfBeats = ( ofGetElapsedTimeMillis() - syncTimeMillis ) / oneBeat;
    currentBeat = numberOfBeats % 4;
    metronome = (numberOfBeats % rowLength) * (cellWidth + 10) + 10;
    
    //if we've gone a full loop of the sequencer
    if(numberOfBeats % rowLength == 0)
    {
        //re-arm all the cells
        for(int i = 0; i < cells.size(); i++)
            cells[i].hasTriggered = false;
    }
    
    //check if the metronome has triggered an event
    for(int i = 0; i < cells.size(); i++)
    {
        if (metronome >= cells[i].pos.x && cells[i].hasTriggered == false)
        {
            string message;
            message = cells[i].trigger();

            if(message != "")
            {
                m.setAddress(message);
                m.addIntArg(1);
                sender.sendMessage(m);
            }
        }
        
    }
    
    //check for button held time, and initiate target popup if necessary
    if ( ofGetElapsedTimeMillis() -  mouseStartMillis > 250 && mouseDown )
    {
        for(int i = 0; i < cells.size(); i++)
        {
            if(cells[i].mouseOver(mouseStart))
            {
                cells[i].targetMode = true;
                
                float angle = -(mouseRelease-cells[i].centerPos).angle(ofVec2f(0,1))-180;
                cells[i].targetModeAngle = angle;
                
                int targetClip = 9 + ((angle/360) * 8);
                cells[i].targetClip = targetClip;
                cells[i].targetClipNew = targetClip;
                
            }
        }
    }
    
    //check for incoming OSC messages
    while(receiver.hasWaitingMessages())
    {
        ofxOscMessage receivedMessage;
        receiver.getNextMessage(&receivedMessage);
        
        if(receivedMessage.getAddress() == "/playbackcontroller/bpm")
        {
            bpm = receivedMessage.getArgAsFloat(0)*498 + 2;  //translate to 2-500
            //lastBpmChangeMillis = ofGetElapsedTimeMillis();
        }
        
        if(receivedMessage.getAddress() == "/playbackcontroller/resync")
        {
            metronome = 10;
            syncTimeMillis = ofGetElapsedTimeMillis();
            //lastBpmChangeMillis = 0;
        }
        
    }
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    for(int i = 0; i < cellNum; i++)
    { 
        cells[i].draw();
    }
    
    ofSetColor(0);
    ofLine(metronome,0,metronome,ofGetHeight());
    
    ofFill();
    ofRect((rowLength-1)*(cellWidth+10)+10,ofGetHeight()/2+cellWidth+10,cellWidth,cellWidth);
    ofPushMatrix();
    ofTranslate((rowLength-1)*(cellWidth+10)+10+cellWidth/2,ofGetHeight()/2+cellWidth+10+cellWidth/2);
    ofRotate(180+currentBeat%4*90, 0, 0, 1);
    ofSetColor(255);
    ofRectRounded(0,0,cellWidth/2-1,cellWidth/2-1,2);
    ofPopMatrix();
    
    ofDrawBitmapString(ofToString(bpm), 10,10);

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    mouseRelease.set(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    mouseDown = true;
    mouseStart.set(x,y);
    mouseStartMillis = ofGetElapsedTimeMillis();
    //cout << mouseStartMillis << "...." << mouseEndMillis << endl;



}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    mouseDown = false;
    mouseEndMillis = ofGetElapsedTimeMillis();
    mouseRelease.set(x,y);
    
    for(int i = 0; i < cells.size(); i++)
    {
        
        //if we were over a button when we started the mouse action
        if(cells[i].mouseOver(mouseStart))
        {
            cells[i].targetMode = false;
            
            if (cells[i].mode == 0) 
            {
                cells[i].mode = 1;
            }
            else
                cells[i].mode = 0;
            
            //change the targetClip for all clips on that layer
            for(int j = 0; j < cells.size(); j++)
            {
                if(cells[j].layer == cells[i].layer && cells[j].mode == 0)
                    cells[j].targetClip = cells[i].targetClip;
            }
            
            
        }

        
    }
    
    //else
    

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}