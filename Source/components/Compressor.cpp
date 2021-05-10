/*
  ==============================================================================

    Compressor.cpp
    Created: 20 Apr 2021 10:28:00pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Compressor.h"

Compressor::Compressor(){}

void Compressor::setBPM(float newBPM){
    bpm = newBPM;
    setRelease();
    setLimitRelease();
}

void Compressor::setRelease(){
    float releaseBPMQuarter = (60000.f/bpm);
    float releaseBPMSet = releaseBPMQuarter/0.5f; // set compressor release time to half note
    
    release = releaseBPMSet;
}

float Compressor::getRelease(){
    return release;
}

void Compressor::setLimitRelease(){
    float releaseBPMQuarter = (60000.f/bpm);
    float releaseBPMSet = releaseBPMQuarter/64.f; // set limit release time to 256th note
    
    limitRelease = releaseBPMSet;
}

float Compressor::getLimitRelease(){
    return limitRelease;
}
