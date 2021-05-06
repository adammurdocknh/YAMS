/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "assets/LargeKnob.h"
#include "assets/MediumKnob.h"
#include "assets/SmallKnob.h"

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
	
	Slider subKnob;
	Slider lowKnob;
	Slider midKnob;
	Slider highKnob;
	Slider airKnob;
	ComboBox keySelectBox;
	
	Slider threshKnob;
	Slider ratioKnob;
	Slider limiterKnob;
	Slider slottedKnob;
	
	ComboBox atkBox;
	ComboBox rlsBox;
	
//	CustomLookAndFeel customLookAndFeel;
	
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> inputVolumeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> saturationAttachment;
	
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> airAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> keySelectAttachment;
	
	
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> threshAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ratioAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> limiterAttachment;
	
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> atkAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> rlsAttachment;
	

	LargeKnob largeKnobLookAndFeel;
	MediumKnob mediumKnobLookAndFeel;
	SmallKnob smallKnobLookAndFeel;
    YAMSAudioProcessor& audioProcessor;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YAMSAudioProcessorEditor)
};
