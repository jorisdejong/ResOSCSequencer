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
    layers = 5;
    cellWidth = 50;
    rowLength = 16;
    cellNum = layers * rowLength;
    gridStartHeight = 100;  // in pixels
    
    int x = 0;
    int y = 0;
    for(int i = 0; i < cellNum; i++)
    {   
        ofVec2f pos;
         
        pos.set( x * (cellWidth+10) + 10, gridStartHeight + y * (cellWidth+10) );
        cells.push_back(GridCell(pos, cellWidth, x, y));
        x++;
        if(x>rowLength-1)
        {
            x=0;
            y++;
        }
    }
    
    bpmController = new BPMController(500);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    bpmController->update();
    
    //set beat and playhead based on current BPM
    playhead = (bpmController->getBeat() % rowLength);
    currentPlayheadPositionX = playhead * (cellWidth + 10) + 10;
    
    //if we've gone a full loop of the sequencer
    //todo this still doesn't work correctly for the first beat
    if ( playhead == 0 )
    {
        //re-arm all the cells
        for(int i = 0; i < cells.size(); i++)
            cells[i].hasTriggered = false;
    }
    
    //check if the playhead has triggered an event
    for(int i = 0; i < cells.size(); i++)
    {
        if ( playhead == cells[i].clip && cells[i].hasTriggered == false )
        {
            string message;
            message = cells[i].trigger();

            if ( message != "" )
            {
                m.setAddress(message);
                m.addIntArg(1);
                sender.sendMessage ( m );
                m.clear();
                
            }
        }
    }
    
    //check for button held time, and initiate target popup if we were over a button
    if ( ofGetElapsedTimeMillis() -  mouseStartMillis > 250 && mouseDown )
    {
        for(int i = 0; i < cells.size(); i++)
        {
            if(cells[i].mouseOver(mouseStart))
            {
                cells[i].targetMode = true;
                
                float angle = - (mouseRelease-cells[i].centerPos).angle (ofVec2f(0,1))-180;
                cells[i].targetModeAngle = angle;
                
                int targetClip = 9 + ((angle/360) * 8);
                cells[i].targetClip = targetClip;
            }
        }
    }
    
    //if we were over the pitcher when we started the mouse action
    if(bpmController->mouseOverPitcher(mouseStart) && mouseDown)
    {
        float amount = ( mouseRelease.x - mouseStart.x ) / 1000;
        bpmController->changeSpeed(amount);
    }
    
    //check for incoming OSC messages
    while(receiver.hasWaitingMessages())
    {
        ofxOscMessage receivedMessage;
        receiver.getNextMessage(&receivedMessage);
        
        if(receivedMessage.getAddress() == "/playbackcontroller/bpm")
        {
            float bpm = receivedMessage.getArgAsFloat(0)*498 + 2;  //translate to 2-500
            bpmController->setBpm(bpm);
        }
        
        if(receivedMessage.getAddress() == "/playbackcontroller/resync")
        {
            bpmController->sync();
        }
        
    }
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    for(int i = 0; i < cellNum; i++)
    { 
        cells[i].draw();
    }
    
    //draw playhead
    ofSetColor(255);
    ofFill();
    ofRectRounded(currentPlayheadPositionX, gridStartHeight + (( cellWidth+10 )* layers), cellWidth, cellWidth, 10);
    
    bpmController->draw();
    
    ofDrawBitmapString(ofToString(bpmController->getBpm()), 10,10);

    
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
    mouseRelease = mouseStart;
    mouseStartMillis = ofGetElapsedTimeMillis();
    
    if(bpmController->mouseOverTapper(mouseStart))
    {
        bpmController->tap();
    }
    //cout << mouseStartMillis << "...." << mouseEndMillis << endl;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    mouseDown = false;
    mouseEndMillis = ofGetElapsedTimeMillis();
    mouseRelease.set(x,y);
    
    //if we were over a button when we started the mouse action
    for(int i = 0; i < cells.size(); i++)
    {
        if(cells[i].mouseOver(mouseStart))
        {
            //change the cell mode
            if (cells[i].mode == 0)
                cells[i].mode = 1;
            else if(!cells[i].targetMode)
                cells[i].mode = 0;
            
                //turn off targetMode
            cells[i].targetMode = false;
            

            
            //change the targetClip for all clips on that layer
            //todo: needs something like a nextTargetClip, because now disarming and rearming a trigger fucks with the logic
            for(int j = 0; j < cells.size(); j++)
            {
                if(cells[j].layer == cells[i].layer && cells[j].mode == 0)
                    cells[j].targetClip = cells[i].targetClip;
            }
        }
    }
    

    

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