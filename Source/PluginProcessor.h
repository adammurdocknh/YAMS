/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "components/Saturation.h"
#include "components/Compressor.h"
#include "components/ToneSection.h"

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
    
    float release = 1000.f;
        
    float limitRelease = 7.8125f;
    
	Saturation preEQSaturationStage;
	Saturation postEQSaturationStage;
	ToneSection toneSection;
	
	AudioProcessorValueTreeState apvts;
	
private:
	
	std::atomic<float>* inputVolumeParameter = nullptr;
	std::atomic<float>* saturationParameter = nullptr;
	std::atomic<float>* toneParameter = nullptr;

	
	std::atomic<float>* threshParameter = nullptr;
	std::atomic<float>* limiterParameter = nullptr;
	std::atomic<float>* outputVolumeParameter = nullptr;
    
    dsp::Compressor<float> Compressor;
    dsp::Limiter<float> limiter;
    dsp::ProcessSpec spec;
    
    class Compressor comp;
    
	AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    float bpm = 120.f;
	
	AudioProcessorValueTreeState::ParameterLayout createParams();

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YAMSAudioProcessor)
};
