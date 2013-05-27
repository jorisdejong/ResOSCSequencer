//
//  Cell.h
//  ResOSCSequencer
//
//  Created by Joris de Jong on 2/18/13.
//  Copyright (c) 2013 Hybrid Visuals. All rights reserved.
//

#include "ofMain.h"
#include "testApp.h"
   

#ifndef ResOSCSequencer_Cell_h
#define ResOSCSequencer_Cell_h

class GridCell
{
public:
    
    //vars
    int mode;
    ofVec2f pos;
    ofVec2f centerPos;
    int w;
    
    int clip;
    int layer;
    
    bool hasTriggered;
    
    //constructor
    GridCell(ofVec2f pos, int w, int x, int y);
    
    //destructor
    //~GridCell();
    
    //meth
    void setup();
    string trigger();
    void draw();
    
    bool mouseOver(ofVec2f posRelease);
    
    bool targetMode;
    float targetModeAngle;
    int targetClip;
    int targetClipNew;
    
    ofVec2f currMouse;
};

#endif
