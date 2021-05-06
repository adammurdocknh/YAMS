/*
  ==============================================================================

    Equalizer.cpp
    Created: 20 Apr 2021 10:27:45pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::Equalizer(){}

float Equalizer::processSample(float input, float channel, float subGain, float lowGain, float midGain, float highGain, float airGain) {
	
	
	float inputdB = Decibels::decibelsToGain(input);
	
	subPeakFilter.setAmpdB(subGain);
	lowPeakFilter.setAmpdB(lowGain);
	midPeakFilter.setAmpdB(midGain);
	highPeakFilter.setAmpdB(highGain);
	airShelf.setAmpdB(airGain);
	
	input = subHPF.processSample(input, channel);
	input = subPeakFilter.processSample(input, channel);
	
	input = lowPeakFilter.processSample(input, channel);
	input = midPeakFilter.processSample(input, channel);
	input = highPeakFilter.processSample(input, channel);
//	airShelf.setFreq(20000);
	input = airShelf.processSample(input, channel);
	
	
	return (input - (Decibels::decibelsToGain(input)-inputdB));
}



void Equalizer::setFs(int Fs) {
	this->Fs = Fs;
}

void Equalizer::setSubFreq(float freq) {
	subHPF.setFreq(20);
	subPeakFilter.setFreq(freq);
}

void Equalizer::setLowFreq(float freq) {
	lowPeakFilter.setFreq(freq);
}

void Equalizer::setMidFreq(float freq) {
	midPeakFilter.setFreq(freq);
}

void Equalizer::setHighFreq(float freq) {
	highPeakFilter.setFreq(freq);
}

void Equalizer::setAirFreq(float freq) {
	airShelf.setFreq(freq);
	std::cout << freq;
}

void Equalizer::setKey(int key) {
	if(key >= 0 || 11 >= key) {
		setSubFreq(keys[key-1][0]);
		setLowFreq(keys[key-1][1]);
		setMidFreq(keys[key-1][2]);
		setHighFreq(keys[key-1][3]);
		setAirFreq(keys[key-1][4]);
	}
	else {
		
	}
}
