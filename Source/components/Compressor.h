/*
  ==============================================================================

    Compressor.h
    Created: 20 Apr 2021 10:28:00pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once

class Compressor {
    
public:
    
    Compressor();
    
    float processSample();
    
    void setBPM(float newBPM);
    
    void setAttack(float newAttack);
    
    float getAttack();
    
    void setRelease(float newRelease);
    
    float getRelease();
    
    void setAttackNote(float newAttackNote);
    
    void setReleaseNote(float newReleaseNote);
    
    
private:
    
    float bpm = 120.f;
    
    float attack = 10.0f;
    
    float release = 125.0f;
    
    float attackNote = 16.f;
    
    float releaseNote = 1.f;

    
};
