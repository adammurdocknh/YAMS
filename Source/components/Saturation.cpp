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
	drive = Decibels::decibelsToGain(drive);

	lowShelf.setAmpdB(drive*.25);
	lowPass.setFreq(20000.f-(1000*drive));
	
	float output = cubicDist(input,drive/30);
	output = cubicDist(output, drive/40);
	
	output = lowShelf.processSample(output, channel);
	output = lowPass.processSample(output, channel);
	output *= juce::Decibels::decibelsToGain(12);
	return output;
}

float Saturation::atandist(float sample, float drive) {
	return (2.f/M_PI) * atan( drive * sample );
}

float Saturation::cubicDist(float sample, float drive) {
	return (sample - .2 * std::pow( sample, 3 ));
}
