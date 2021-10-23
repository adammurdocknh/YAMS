/*
  ==============================================================================

    Saturation.cpp
    Created: 20 Apr 2021 6:40:11pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Saturation.h"

Saturation::Saturation() {}

float Saturation::processSample(float sample,float drive, int channel) {

    lowShelf.setAmpdB(drive*.25f);
    lowShelf.setFreq(60.f);
    highShelf.setFreq(20000.f-(1000.f*drive));
    highShelf.setAmpdB(drive*.25f);



    drive *=.25;

    sample = lowShelf.processSample(sample, channel);
    sample = highShelf.processSample(sample, channel);

    sample = cubicDist(sample, drive);

    return sample;
}

float Saturation::cubicDist(float sample, float drive) {
    return (sample - drive * std::pow( sample, 3 ));
}

void Saturation::setFs(float Fs) {
    highPass.setFs(Fs);
    highShelf.setFs(Fs);
    lowShelf.setFs(Fs);
    lowPass.setFs(Fs);
}
