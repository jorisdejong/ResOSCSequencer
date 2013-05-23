//
//  Cell.cpp
//  ResOSCSequencer
//
//  Created by Joris de Jong on 2/18/13.
//  Copyright (c) 2013 Hybrid Visuals. All rights reserved.
//

#include <iostream>
#include "GridCell.h"


GridCell::GridCell(ofVec2f pos_, int w_, int x, int y)
{
    pos = pos_;
    w = w_;
    clip = x;
    layer = y;
    mode = 0;
    hasTriggered = false;
    
    
}

void GridCell::draw()
{
    switch (mode)
    {
        case 0:
            ofSetColor(32);
            ofFill();
            ofRectRounded(pos, w, w, 10);
            ofNoFill();
            ofSetColor(0);
            ofRectRounded(pos, w, w, 10);
            break;
        case 1:
            ofSetColor(255);
            ofFill();
            ofEllipse(pos.x+w/2, pos.y+w/2,w, w);
            ofNoFill();
            ofSetColor(0);
            ofEllipse(pos.x+w/2, pos.y+w/2, w, w);
            break;
        case 2:
            ofSetColor(255,0,0);
            ofFill();
            ofRectRounded(pos, w, w, 10);
            ofNoFill();
            ofSetColor(0);
            ofRectRounded(pos, w, w, 10);
            break;
    }


}

string GridCell::triggerAll()
{

    //string message = "/layer"+ofToString(layer+1)+"/clip1/connect";
    string message = "/layer"+ofToString(layer+1)+"/clip"+ofToString(clip+1)+"/connect";
        
    hasTriggered = true;
    switch(mode)
    {
        case 0:
            return "";
            break;
        
        case 1:
            return message;
            cout << "start " + message << endl;
            break;        
        
        case 2:
            cout << "eject " + ofToString(layer+1) <<endl;
            return "";
            break;
    }
}

string GridCell::triggerOne()
{
    
    string message = "/layer"+ofToString(layer+1)+"/clip1/connect";
    //string message = "/layer"+ofToString(layer+1)+"/clip"+ofToString(clip+1)+"/connect";
    
    hasTriggered = true;
    switch(mode)
    {
        case 0:
            return "";
            break;
            
        case 1:
            return message;
            cout << "start " + message << endl;
            break;        
            
        case 2:
            cout << "eject " + ofToString(layer+1) <<endl;
            return "";
            break;
    }
}

void GridCell::mouseOver(float x, float y, int mode_)
{
    if(x > pos.x && x < pos.x + w && y > pos.y && y < pos.y + w)
    {
        if (mode == 0) 
            mode = mode_;
        else
            mode = 0;
    }
}
