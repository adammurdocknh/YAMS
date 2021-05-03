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
//	float arr[4];
//	arr[0] = {16.35f,17.32f,18.35f,19.45f,20.60f,21.83f,23.12f,24.50f,25.96f,27.50f,29.14f,30.87f};
//	arr[1] = {65.41f,69.30f,73.42f,77.78f,82.41f,87.31f,92.50f,98.00f,103.83f,110.00f,116.54f,123.47f};
//	arr[2] = {1046.50f,1108.73f,1174.66f,1174.66f,1318.51f,1396.91f,1479.98f,1567.98f,1661.22f,1760.00f,1864.66f,1975.53f};
//	arr[3] ={2093.00f,2217.46f,2349.32f,2489.02f,2637.02f,2793.83f,2959.96f,3135.96f,3322.44f,3520.00f,3729.31f,3951.07f};
	
};

