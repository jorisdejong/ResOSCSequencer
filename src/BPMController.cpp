//
//  BPMController.cpp
//  ResOSCSequencer
//
//  Created by Joris de Jong on 5/28/13.
//  Copyright (c) 2013 Hybrid Visuals. All rights reserved.
//

#include <iostream>
#include "BPMController.h"

BPMController::BPMController(int y)
{
    bpm = 120;
    syncTimeMillis = 0;
    tapCount = 0;
    
    tapper.set(10,y,100,100);
    pitcher.set(120,y,800,100);
}

int BPMController::getBeat()
{
    //calculate time of one beat in millis
    float oneBeat = 60000.0 / bpm;
    
    //calculate the number of elapsed beats
    //todo: figure out a way of calculating the current beat correctly after a bpm change
    
    int numberOfBeats = ( ofGetElapsedTimeMillis() - syncTimeMillis ) / oneBeat;
    fourBeat = numberOfBeats % 4;  
    return numberOfBeats;    
}

int BPMController::getBpm()
{
    return bpm;
}

void BPMController::setBpm(int bpm_)
{
    bpm = bpm_;
}

void BPMController::changeSpeed(float amount)
{
    bpm += amount;
}

void BPMController::sync()
{
    syncTimeMillis = ofGetElapsedTimeMillis();
    tapCount = 0;
}

void BPMController::draw()
{
    //draw pitcher
    ofSetColor(0);
    ofFill();
    ofRectRounded(pitcher.x, pitcher.y, pitcher.z, pitcher.w, 10);
    ofSetColor(255);
    ofLine(pitcher.x + pitcher.z/2, pitcher.y, pitcher.x + pitcher.z/2, pitcher.y + pitcher.w);
    
    //draw the bpm counter
    ofSetColor(0);
    ofRectRounded(tapper.x, tapper.y, tapper.z, tapper.w , 5);
    ofPushMatrix();
    ofTranslate(tapper.x+50, tapper.y+50);
    ofRotate(180 + fourBeat % 4 * 90, 0, 0, 1);
    ofSetColor(255);
    ofRectRounded( 0, 0, 45, 45, 5);
    ofPopMatrix();
}

bool BPMController::mouseOverTapper(ofVec2f pos)
{
    if(pos.x > tapper.x && pos.x < tapper.z + tapper.x && pos.y > tapper.y && pos.y < tapper.y + tapper.w)
        return true;
    else
        return false;
}

void BPMController::tap()
{      
    tapCount++;
    
    if(tapCount == 1)
    {
        firstTap = ofGetElapsedTimeMillis();
        lastTap = firstTap;
    }
    
    if(tapCount >= 2)
    {
        lastTap = ofGetElapsedTimeMillis();
        bpmMillis = (lastTap - firstTap) / (tapCount - 1);
        bpm = 60000 / bpmMillis;
    }
}

void BPMController::update()
{
    if(tapCount >= 2)
    {
        if(ofGetElapsedTimeMillis() - lastTap > (bpmMillis * 2) || ofGetElapsedTimeMillis() - lastTap > 4000)
        {
            tapCount = 0;
        }
    }
}
