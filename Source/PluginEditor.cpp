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
	inputVolumeSlider.setBounds(25, 75, 125, 125);
	inputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
	inputVolumeSlider.setValue(0.f);
	inputVolumeSlider.setLookAndFeel(&largeKnobLookAndFeel);
	inputVolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"INPUTVOLUME",inputVolumeSlider);
	addAndMakeVisible(inputVolumeSlider);
	
	saturationKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	saturationKnob.setBounds(175, 75, 125, 125);
	saturationKnob.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
	saturationKnob.setValue(0.f);
	saturationKnob.setLookAndFeel(&largeKnobLookAndFeel);
	saturationAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"SATURATION",saturationKnob);
	addAndMakeVisible(saturationKnob);

	subKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	subKnob.setBounds(330, 75, 50, 50);
	subKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	subKnob.setValue(0.f);
	subKnob.setLookAndFeel(&smallKnobLookAndFeel);
	subAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"SUBBAND",subKnob);
	addAndMakeVisible(subKnob);

	lowKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	lowKnob.setBounds(385, 75, 50, 50);
	lowKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	lowKnob.setValue(0.f);
	lowKnob.setLookAndFeel(&smallKnobLookAndFeel);
	lowAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"LOWBAND",lowKnob);
	addAndMakeVisible(lowKnob);
	
	midKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	midKnob.setBounds(440, 75, 50, 50);
	midKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	midKnob.setValue(0.f);
	midKnob.setLookAndFeel(&smallKnobLookAndFeel);
	midAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"MIDBAND",midKnob);
	addAndMakeVisible(midKnob);
	
	highKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	highKnob.setBounds(440, 75, 50, 50);
	highKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	highKnob.setValue(0.f);
	highKnob.setLookAndFeel(&smallKnobLookAndFeel);
	highAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"HIGHBAND",highKnob);
	addAndMakeVisible(highKnob);
	
	airKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	airKnob.setBounds(440, 75, 50, 50);
	airKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	airKnob.setValue(0.f);
	airKnob.setLookAndFeel(&smallKnobLookAndFeel);
	airAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"AIRBAND",airKnob);
	addAndMakeVisible(airKnob);
	
	
	
	
	
	
	
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
