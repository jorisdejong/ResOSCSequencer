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

}

//--------------------------------------------------------------
void testApp::update(){
    metronome+=1;
    
    if(metronome>rowLength*(cellWidth+10)+10)
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
    
    cout << bpm << endl;

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