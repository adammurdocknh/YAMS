/*
  ==============================================================================

    Equalizer.h
    Created: 20 Apr 2021 10:27:45pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once
#include "Biquad.h"

class Equalizer {
public:
	Equalizer();
	float processSample(float input, float channel);
	
	void setSubFreq(float freq);
	void setLowFreq(float freq);
	void setMidFreq(float freq);
	void setHighFreq(float freq);
	void setAirFreq(float freq);
	void setFs(int Fs);
private:
	Biquad subHPF = Biquad(Biquad::FilterType::HPF,1.4142f);
	Biquad subPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	
	Biquad lowPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	Biquad midPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	Biquad highPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	Biquad airShelf = Biquad(Biquad::FilterType::HSHELF,1.4142f);
	
	
	float Fs = 48000.f;
	
};

