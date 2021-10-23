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

    void setBPM(float newBPM);
    
    void setRelease();

    float getRelease();
    
    void setLimitRelease();
    
    float getLimitRelease();
    
private:
    
    float bpm = 120.f;
    
    float release = 1000.f;
    
    float limitRelease = 7.8125f;

    
};
