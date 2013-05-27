#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "GridCell.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector <GridCell> cells;
    int cellNum;
    int cellWidth;
    int rowLength;
    
    float metronome;
    float bpm;
    int currentBeat;
    int numberOfBeats;
    float syncTimeMillis;
    float lastBpmChangeMillis;
    

    bool mouseDown;
    float mouseStartMillis;
    float mouseEndMillis;
    ofVec2f mouseStart;
    ofVec2f mouseRelease;
    
    ofxOscMessage m;
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    bool targetMode;
    int getTarget(ofVec2f pos);
    

};
