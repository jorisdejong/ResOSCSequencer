//
//  BPMController.h
//  ResOSCSequencer
//
//  Created by Joris de Jong on 5/28/13.
//  Copyright (c) 2013 Hybrid Visuals. All rights reserved.
//

#include "testApp.h"

#ifndef ResOSCSequencer_BPMController_h
#define ResOSCSequencer_BPMController_h

class BPMController
{
public: 
    //vars
    float bpm;
    int fourBeat;
    int numberOfBeats;
    float syncTimeMillis;
    float lastUpdateTimeMillis;
    int lastUpdateTimeBeats;
    float offsetMillis;
    int tapCount;
    float bpmMillis;
    
    ofVec4f tapper;
    ofVec4f pitcher;
    ofVec4f puller;
    ofVec4f pusher;
    
    //constructor
    BPMController(int y);
    
    //meth
    void update();
    void draw();
    
    float getBpm();
    int getBeat();
    void setBpm (float bpm);
    void tap();
    void sync();
    void changeSpeed(float amount);
    void push();
    void pull();
    
    bool mouseOverTapper(ofVec2f pos);
    bool mouseOverPitcher(ofVec2f pos);
    bool mouseOverPuller(ofVec2f pos);
    bool mouseOverPusher(ofVec2f pos);
    
    float firstTap;
    float lastTap;

};


#endif
