/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "components/Saturation.h"
#include "components/Equalizer.h"

//==============================================================================
/**
*/
class YAMSAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    YAMSAudioProcessor();
    ~YAMSAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	Saturation preEQSaturationStage;
	Saturation postEQSaturationStage;
	Equalizer eq;
	
	AudioProcessorValueTreeState apvts;
	
private:
	
	std::atomic<float>* inputVolumeParameter = nullptr;
	std::atomic<float>* saturationParameter = nullptr;
	std::atomic<float>* subParameter = nullptr;
	std::atomic<float>* lowParameter = nullptr;
	std::atomic<float>* midParameter = nullptr;
	std::atomic<float>* highParameter = nullptr;
	std::atomic<float>* airParameter = nullptr;
	std::atomic<float>* keyParameter = nullptr;
	
	std::atomic<float>* threshParameter = nullptr;
	std::atomic<float>* ratioParameter = nullptr;
	std::atomic<float>* limiterParameter = nullptr;
	
	std::atomic<float>* atkParameter = nullptr;
	std::atomic<float>* rlsParameter = nullptr;
	
	float thresholdDSPValue;

	AudioProcessorValueTreeState::ParameterLayout createParams();

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YAMSAudioProcessor)
};
