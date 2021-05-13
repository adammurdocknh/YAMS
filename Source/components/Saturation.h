/*
  ==============================================================================

    Saturation.h
    Created: 20 Apr 2021 6:40:11pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Biquad.h"

class Saturation
{
public:
	Saturation();
	
	float processSample(float input, float drive, int channel);
	float atandist(float sample, float drive);
	float cubicDist(float sample, float drive);
	
	Biquad highPass = Biquad(Biquad::FilterType::HPF,0.7071f);
	Biquad highShelf = Biquad(Biquad::FilterType::HSHELF,1.4142f);
	Biquad lowShelf = Biquad(Biquad::FilterType::LSHELF,1.4142f);
	Biquad lowPass = Biquad(Biquad::FilterType::LPF,0.7071f);
	
	void setFs(float Fs);
	
private:
};
