/*
  ==============================================================================

    ToneSection.cpp
    Created: 10 May 2021 7:43:27pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "ToneSection.h"

ToneSection::ToneSection(){};

float ToneSection::processSample(float sample, float channel, float toneInput) {
	lowFilter.setFreq(20.f);
	lowShelf.setFreq(20.f);
	highShelf.setFreq(12000.f);
	
	// Dark section
	if (toneInput < 0) {
		highShelf.setAmpdB(toneInput);
		// You'll have a negative input so you need to flip the sign.
		toneInput *= -1;
		lowShelf.setAmpdB(toneInput);
		
		return highShelf.processSample(lowShelf.processSample(lowFilter.processSample(sample, channel), channel),channel);
	};
		
	// Bright section
	if (toneInput > 0){
		float lowFreq = 10 * toneInput;
		lowFreq += 20;
		lowFilter.setFreq(lowFreq);
		lowShelf.setFreq(lowFreq);
		lowShelf.setAmpdB(toneInput * -.5);
		highShelf.setAmpdB(toneInput * .5);
		
		return highShelf.processSample(lowShelf.processSample(lowFilter.processSample(sample, channel), channel),channel);
	}
	else {
//		return lowFilter.processSample(sample,channel);
		return sample;
	}
}

void ToneSection::setFs(float Fs) {
	lowFilter.setFs(Fs);
	lowShelf.setFs(Fs);
	highShelf.setFs(Fs);
	
}
