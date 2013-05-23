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
    int w;
    
    int clip;
    int layer;
    
    bool hasTriggered;
    
    bool triggerColumnMode;
    
    //constructor
    GridCell(ofVec2f pos, int w, int x, int y);
    
    //destructor
    //~GridCell();
    
    //meth
    void setup();
    string triggerAll();
    string triggerOne();
    void draw();
    void mouseOver(float x, float y, int mode);
};

#endif
