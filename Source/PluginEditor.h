/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "assets/LargeKnob.h"

//==============================================================================
/**
*/
class YAMSAudioProcessorEditor  :	public juce::AudioProcessorEditor
{
public:
    YAMSAudioProcessorEditor (YAMSAudioProcessor&);
    ~YAMSAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;



private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	
	Slider inputVolumeSlider;
	Slider saturationKnob;
	Slider toneKnob;
	
	Slider threshKnob;
	Slider limiterKnob;
	Slider outputKnob;
	
	
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> inputVolumeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> saturationAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> toneAttachment;
	
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> threshAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> limiterAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputAttachment;


	LargeKnob largeKnobLookAndFeel;
    YAMSAudioProcessor& audioProcessor;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YAMSAudioProcessorEditor)
};
