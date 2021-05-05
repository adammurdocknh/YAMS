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
}

void Compressor::setAttack(float newAttack){
    attack = newAttack;
}

float Compressor::getAttack(){
    return attack;
}

void Compressor::setRelease(float newRelease){
    release = newRelease;
}

float Compressor::getRelease(){
    return release;
}

void Compressor::setAttackNote(float newAttackNote){
    attackNote = newAttackNote;
    
    float attackBPMQuarter = (60000.f/bpm);
    float attackBPMSet = attackBPMQuarter/attackNote;
    
    setAttack(attackBPMSet);
}

void Compressor::setReleaseNote(float newReleaseNote){
    releaseNote = newReleaseNote;
    
    float releaseBPMQuarter = (60000.f/bpm);
    float releaseBPMSet = releaseBPMQuarter/releaseNote;
    
    setRelease(releaseBPMSet);
}
