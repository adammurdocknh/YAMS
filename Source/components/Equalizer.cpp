/*
  ==============================================================================

    Equalizer.cpp
    Created: 20 Apr 2021 10:27:45pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::Equalizer(){}

float Equalizer::processSample(float input, float channel) {
	float inputdB = Decibels::decibelsToGain(input);
	
	input = subHPF.processSample(input, channel);
	input = subPeakFilter.processSample(input, channel);
	
	input = lowPeakFilter.processSample(input, channel);
	input = midPeakFilter.processSample(input, channel);
	input = highPeakFilter.processSample(input, channel);
	airShelf.setFreq(20000);
	input = airShelf.processSample(input, channel);
	
	
	return (input - (Decibels::decibelsToGain(input)-inputdB));
}
void Equalizer::setFs(int Fs) {
	this->Fs = Fs;
}

