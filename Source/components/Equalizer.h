/*
  ==============================================================================

    Equalizer.h
    Created: 20 Apr 2021 10:27:45pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once
#include "Biquad.h"
#include <iterator>
#include <map>

class Equalizer {
public:
	Equalizer();
	float processSample(float input, float channel, float subGain, float lowGain, float midGain, float highGain, float airGain);
	
	void setSubFreq(float freq);
	void setLowFreq(float freq);
	void setMidFreq(float freq);
	void setHighFreq(float freq);
	void setAirFreq(float freq);
	
	void setKey(int key);
	
	void setFs(int Fs);
	
private:
	Biquad subHPF = Biquad(Biquad::FilterType::HPF,1.4142f);
	Biquad subPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	
	Biquad lowPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	Biquad midPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	Biquad highPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4142f);
	Biquad airShelf = Biquad(Biquad::FilterType::HSHELF,1.4142f);

	float keyOfC[5] = {32.7, 65.41, 1046.50, 2093.00, 16744.f};
	float keyOfDb[5] = {34.64, 65.41, 1108.73, 2217.46, 17736.f};
	float keyOfD[5] = {36.7, 69.30, 1174.66, 2349.32, 18794.56f};
	float keyOfEb[5] = {38.9, 77.8, 1244.8, 2489.6, 14937.6f};
	float keyOfE[5] = {41.2, 82.4, 1318.4, 2636.8, 15820.8};
	float keyOfF [5] = {43.66, 87.32, 1397.12, 2794.24, 16765.44};
	float keyOfGb[5] = {46.24, 92.48, 1479.68, 2959.36, 17756.16};
	float keyOfG[5] = {49, 98, 1568, 3136, 12544};
	float keyOfAb[5] = {51.92, 103.84, 830.72, 3322.88, 13291.52};
	float keyOfA[5] = {55, 110, 880, 1760, 14080};
	float keyOfB[5] = {58.28, 116.56, 932.48, 3729.92, 14919.68};

	
	
//	typedef std::map<std::string,float[5]> myMap;
//	typedef std::map<std::string,float[5]> myMap2;
//	myMap2.insert(std::pair<1,float[5]>(1,keyOfC));
	
//	myMap.insert(std::pair<std::string,float[5]>("C",keyOfC));
	
	float currentKey[5];
	
	float keys[11][5] {
		{32.7, 65.41, 1046.50, 2093.00, 16744.f},
		{34.64, 65.41, 1108.73, 2217.46, 17736.f},
		{36.7, 69.30, 1174.66, 2349.32, 18794.56f},
		{38.9, 77.8, 1244.8, 2489.6, 14937.6f},
		{41.2, 82.4, 1318.4, 2636.8, 15820.8},
		{43.66, 87.32, 1397.12, 2794.24, 16765.44},
		{46.24, 92.48, 1479.68, 2959.36, 17756.16},
		{49, 98, 1568, 3136, 12544},
		{51.92, 103.84, 830.72, 3322.88, 13291.52},
		{55, 110, 880, 1760, 14080},
		{58.28, 116.56, 932.48, 3729.92, 14919.68},
	};
	
	float Fs = 48000.f;
	
};
