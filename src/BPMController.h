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
    int bpm;
    int fourBeat;
    float syncTimeMillis;
    int tapCount;
    float bpmMillis;
    
    ofVec4f tapper;
    ofVec4f pitcher;
    
    //constructor
    BPMController(int y);
    
    //meth
    void update();
    void draw();
    
    int getBpm();
    int getBeat();
    void setBpm (int bpm);
    void tap();
    void sync();
    void changeSpeed(float amount);
    void push();
    void pull();
    
    bool mouseOverTapper(ofVec2f pos);
    bool mouseOverPitcher(ofVec2f pos);
    
    float firstTap;
    float lastTap;

};


#endif
