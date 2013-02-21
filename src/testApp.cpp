#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    sender.setup("localhost", 7000);
    receiver.setup(7001);
    
    //create cellgrid;
    cellNum = 24;
    cellWidth = 40;
    rowLength = 8;
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
    beats = 0;
    bpm = 180;
    beatMillis = ofGetElapsedTimeMillis();


}

//--------------------------------------------------------------
void testApp::update(){
        
    //calculate time of one beat in millis
    float oneBeat = 60/bpm * 1000;
    if(ofGetElapsedTimeMillis() - beatMillis > oneBeat)
    {
        beatMillis = ofGetElapsedTimeMillis();
        metronome+=(cellWidth+10)/4.0;
        beats++;
    }
    
    
    
    if(metronome>rowLength*(cellWidth+10))
    {
        metronome = 10;
        for(int i = 0; i < cells.size(); i++)
            cells[i].hasTriggered = false;
    }
    
    for(int i = 0; i < cells.size(); i++)
    {
        if (metronome>cells[i].pos.x && cells[i].hasTriggered == false)
        {
            string message = cells[i].trigger();
            if(message != "")
            {
                m.setAddress(message);
                m.addIntArg(1);
                sender.sendMessage(m);
            }
        }
        
    }
    
    while(receiver.hasWaitingMessages())
    {
        ofxOscMessage receivedMessage;
        receiver.getNextMessage(&receivedMessage);
        
        if(receivedMessage.getAddress() == "/playbackcontroller/bpm")
            bpm = receivedMessage.getArgAsFloat(0)*498+2;
        if(receivedMessage.getAddress() == "/playbackcontroller/resync")
        {
            beats=0;
            metronome = 10;
            beatMillis = ofGetElapsedTimeMillis();
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
    ofRotate(180+beats%4*90, 0, 0, 1);
    ofSetColor(255);
    ofRectRounded(0,0,cellWidth/2-1,cellWidth/2-1,2);
    ofPopMatrix();
    
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

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    mouseStartX = x;
    mouseStartY = y;


}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    for(int i = 0; i < cells.size(); i++)
    {
        cells[i].mouseOver(mouseStartX, mouseStartY, 1);
    }
    
    if(abs(mouseStartX - x) > cellWidth + 10)
    {
        for(int i = 0; i < cells.size(); i++)
        {
            cells[i].mouseOver(x,y,2);
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