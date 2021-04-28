/*
  ==============================================================================

    BlueKnobClass.h
    Created: 25 Apr 2021 11:25:21pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class LargeKnob : public LookAndFeel_V4
{
public:
	Image sprite = ImageCache::getFromMemory(BinaryData::LargeKnob_png, BinaryData::LargeKnob_pngSize);
	 void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);
};
