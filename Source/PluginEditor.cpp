/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YAMSAudioProcessorEditor::YAMSAudioProcessorEditor (YAMSAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	
	// SLIDERS:
	
	inputVolumeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	inputVolumeSlider.setBounds(25, 25, 125, 125);
	inputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
	inputVolumeSlider.setValue(0.f);
	inputVolumeSlider.setLookAndFeel(&largeKnobLookAndFeel);
	inputVolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"INPUTVOLUME",inputVolumeSlider);
	addAndMakeVisible(inputVolumeSlider);
	
	
	saturationKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	saturationKnob.setBounds(175, 25, 125, 125);
	saturationKnob.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
	saturationKnob.setValue(0.f);
	saturationKnob.setLookAndFeel(&largeKnobLookAndFeel);
	saturationAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"SATURATION",saturationKnob);
	addAndMakeVisible(saturationKnob);
	
	toneKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	toneKnob.setBounds(325, 25, 125, 125);
	toneKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	toneKnob.setValue(0.f);
	toneKnob.setLookAndFeel(&largeKnobLookAndFeel);
	toneAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"TONE",toneKnob);
	addAndMakeVisible(toneKnob);
	
	
	threshKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	threshKnob.setBounds(25, 225, 125, 125);
	threshKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	threshKnob.setValue(6.f);
	threshKnob.setLookAndFeel(&largeKnobLookAndFeel);
	threshAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"THRESHOLD",threshKnob);
	addAndMakeVisible(threshKnob);
	
	limiterKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	limiterKnob.setBounds(175, 225, 125, 125);
	limiterKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	limiterKnob.setValue(0.f);
	limiterKnob.setLookAndFeel(&largeKnobLookAndFeel);
	limiterAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"LIMIT",limiterKnob);
	addAndMakeVisible(limiterKnob);

	outputKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	outputKnob.setBounds(325, 225, 125, 125);
	outputKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	outputKnob.setValue(0.f);
	outputKnob.setLookAndFeel(&largeKnobLookAndFeel);
	outputAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"OUTPUTVOLUME",outputKnob);
	addAndMakeVisible(outputKnob);
	
	setSize (725, 400);
	
}

YAMSAudioProcessorEditor::~YAMSAudioProcessorEditor()
{
}

//==============================================================================
void YAMSAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	auto background = juce::ImageCache::getFromMemory(BinaryData::YAMS_GUI_png, BinaryData::YAMS_GUI_pngSize);
	g.drawImageAt(background, 0, 0);
}

void YAMSAudioProcessorEditor::resized()
{
	// LookAndFeel
}
