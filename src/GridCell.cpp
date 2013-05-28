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
    centerPos.x=pos.x+w/2;
    centerPos.y=pos.y+w/2;
    clip = x;
    layer = y;
    mode = 0;
    targetMode = false;
    targetClip = 1;
    
    
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
            ofEllipse(centerPos,w, w);
            ofNoFill();
            ofSetColor(0);
            ofEllipse(centerPos, w, w);
            ofDrawBitmapString(ofToString(targetClip), centerPos);
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
    
    if ( targetMode )
    {
        ofSetColor(255,128,0,128);
        ofFill();
        ofPushMatrix();
        ofTranslate(centerPos);
        ofEllipse(0,0, 100, 100);
        ofRotateZ(targetModeAngle);
        ofSetColor(255);
        ofLine(0,0,0,-50);
        ofDrawBitmapString(ofToString(targetClip), 0,0);
        ofPopMatrix();
        //ofEllipse(currMouse, 20, 20);
    }
        


}


string GridCell::trigger()
{
    
    //string message = "/layer"+ofToString(layer+1)+"/clip1/connect";
    string message = "/layer"+ofToString(layer+1)+"/clip"+ofToString(targetClip)+"/connect";
    
    hasTriggered = true;
    switch(mode)
    {
        case 0:
            return "";
            break;
            
        case 1:
            cout << "trigger " + message << endl;
            return message;
            break;        
            
        case 2:
            cout << "eject " + ofToString(layer+1) <<endl;
            return "";
            break;
            
        default:
            cout << "defaulted" << endl;
            break;
    }
}

bool GridCell::mouseOver(ofVec2f posRelease)
{
    if(posRelease.x - pos.x < w && posRelease.x - pos.x > 0 && posRelease.y - pos.y < w && posRelease.y - pos.y > 0)
        return true;
    else
        return false;
}

