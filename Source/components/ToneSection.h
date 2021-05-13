/*
  ==============================================================================

    ToneSection.h
    Created: 10 May 2021 7:43:27pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once
#include "Biquad.h"

class ToneSection {
public:
	ToneSection();
	
	float processSample(float sample, float channel, float toneInput);
	void setFs(float Fs);
	
private:
	Biquad lowFilter = Biquad(Biquad::FilterType::HPF, 0.7071f);
	Biquad lowShelf = Biquad(Biquad::FilterType::LSHELF, 0.7071f);
	
	Biquad highShelf = Biquad(Biquad::FilterType::HSHELF,0.7071f);
};
