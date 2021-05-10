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

	
	lowShelf.setAmpdB(drive);
	lowShelf.setFreq(60.f);
	lowPass.setFreq(20000.f-(1000.f*drive));
	
	drive *=.5;
	
	float output = lowShelf.processSample(input, channel);
	output = lowPass.processSample(output, channel);
	
	output = cubicDist(output, drive);
	
	return output;
}

float Saturation::cubicDist(float sample, float drive) {
	return (sample - drive * std::pow( sample, 3 ));
}
