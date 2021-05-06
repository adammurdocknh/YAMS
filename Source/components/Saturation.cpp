/*
  ==============================================================================

    Saturation.cpp
    Created: 20 Apr 2021 6:40:11pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Saturation.h"
//#include "Biquad.h"

Saturation::Saturation(){}

float Saturation::processSample(float input,float drive, int channel) {
//	drive = Decibels::decibelsToGain(drive);

	drive *=.5;
	lowShelf.setAmpdB(drive * .25);
	lowPass.setFreq(20000.f-(1000*drive));
	
	float output = cubicDist(input, drive);
	output = cubicDist(output, drive);
	
	output = lowShelf.processSample(output, channel);
	output = lowPass.processSample(output, channel);
//	output *= juce::Decibels::decibelsToGain(12);
	return output;
}

float Saturation::cubicDist(float sample, float drive) {
	return (sample - drive * std::pow( sample, 3 ));
}
