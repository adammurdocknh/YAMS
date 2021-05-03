/*
  ==============================================================================

    BlueKnobClass.cpp
    Created: 25 Apr 2021 11:25:21pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "MediumKnob.h"

void MediumKnob::drawRotarySlider (Graphics& g,
                                      int x,
                                      int y,
                                      int width,
                                      int height,
                                      float sliderPos,
                                      const float rotaryStartAngle,
                                      const float rotaryEndAngle,
                                      Slider& slider)
{
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    AffineTransform rotator;
    g.drawImageTransformed(sprite, rotator.rotated(angle, (float)(sprite.getWidth()/2), (float)(sprite.getHeight()/2)));
}
