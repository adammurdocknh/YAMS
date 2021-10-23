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
    highShelf.setAmpdB(toneInput * .25);
    // You'll have a negative input so you need to flip the sign.
    toneInput *= -1;
    lowShelf.setAmpdB(toneInput);

    float lowFreq = 2.5 * toneInput;
    lowFilter.setFreq(lowFreq);
    lowShelf.setFreq(lowFreq);

    sample = lowFilter.processSample(sample, channel);
    sample = highShelf.processSample(sample, channel);
    sample = lowShelf.processSample(sample, channel);

    return sample;
  };

  // Bright section
  if (toneInput > 0) {
    float lowFreq = 5 * toneInput;
    lowFilter.setFreq(lowFreq);
    lowShelf.setFreq(lowFreq);
    highShelf.setAmpdB(toneInput * .25);

    lowShelf.setAmpdB(toneInput * -.5);

    sample = lowFilter.processSample(sample, channel);
    sample = highShelf.processSample(sample, channel);
    sample = lowShelf.processSample(sample, channel);

    return sample;
  } else {
    //		return lowFilter.processSample(sample,channel);
    return sample;
  }
}

void ToneSection::setFs(float Fs) {
  lowFilter.setFs(Fs);
  lowShelf.setFs(Fs);
  highShelf.setFs(Fs);
}
