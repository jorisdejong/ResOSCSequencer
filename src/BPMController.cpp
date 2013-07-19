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
    offsetMillis = 0;
    tapCount = 0;
    
    tapper.set(10,y,100,100);
    pitcher.set(230,y,600,100);
    puller.set(120,y,100,100);
    pusher.set(840,y,100,100);
    
}

int BPMController::getBeat()
{
    //calculate time of one beat in millis
    float oneBeat = 60000.0 / bpm;
    
    //calculate the number of elapsed beats
    //todo: figure out a way of calculating the current beat correctly after a bpm change
    
    numberOfBeats = lastUpdateTimeBeats + ( ofGetElapsedTimeMillis() - lastUpdateTimeMillis - syncTimeMillis + offsetMillis ) / oneBeat;
    fourBeat = numberOfBeats % 4;  
    return numberOfBeats;    
}

float BPMController::getBpm()
{
    return bpm;
}

void BPMController::setBpm(float bpm_)
{
    bpm = bpm_;
    lastUpdateTimeMillis = ofGetElapsedTimeMillis();
    lastUpdateTimeBeats = numberOfBeats;
}

void BPMController::changeSpeed(float amount)
{
    bpm += amount;
    lastUpdateTimeMillis = ofGetElapsedTimeMillis();
    lastUpdateTimeBeats = numberOfBeats;
}

void BPMController::sync()
{
    syncTimeMillis = ofGetElapsedTimeMillis();
    offsetMillis = 0;
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
    
    //draw puller and pusher;
    ofSetColor(0);
    ofNoFill();
    ofRectRounded(puller.x, puller.y, puller.z, puller.w, 10);
    ofRectRounded(pusher.x, pusher.y, pusher.z, pusher.w, 10);
}

bool BPMController::mouseOverTapper(ofVec2f pos)
{
    if(pos.x > tapper.x && pos.x < tapper.z + tapper.x && pos.y > tapper.y && pos.y < tapper.y + tapper.w)
        return true;
    else
        return false;
}

bool BPMController::mouseOverPitcher(ofVec2f pos)
{
    if(pos.x > pitcher.x && pos.x < pitcher.z + pitcher.x && pos.y > pitcher.y && pos.y < pitcher.y + pitcher.w)
        return true;
    else
        return false;
}

bool BPMController::mouseOverPuller(ofVec2f pos)
{
    if(pos.x > puller.x && pos.x < puller.z + puller.x && pos.y > puller.y && pos.y < puller.y + puller.w)
        return true;
    else
        return false;
}

bool BPMController::mouseOverPusher(ofVec2f pos)
{
    if(pos.x > pusher.x && pos.x < pusher.z + pusher.x && pos.y > pusher.y && pos.y < pusher.y + pusher.w)
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
        lastUpdateTimeMillis = ofGetElapsedTimeMillis();
        lastUpdateTimeBeats = numberOfBeats;

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

void BPMController::push()
{
    offsetMillis+=10;
}

void BPMController::pull()
{
    offsetMillis-=10;
}
