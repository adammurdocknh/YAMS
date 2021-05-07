/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YAMSAudioProcessor::YAMSAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
						apvts(*this, nullptr, "Params", createParams())

#endif

{
	inputVolumeParameter = apvts.getRawParameterValue("INPUTVOLUME");
	saturationParameter = apvts.getRawParameterValue("SATURATION");
	subParameter = apvts.getRawParameterValue("SUBBAND");
	lowParameter = apvts.getRawParameterValue("LOWBAND");
	midParameter = apvts.getRawParameterValue("MIDBAND");
	highParameter = apvts.getRawParameterValue("HIGHBAND");
	airParameter = apvts.getRawParameterValue("AIRBAND");
	keyParameter = apvts.getRawParameterValue("KEY");

	threshParameter = apvts.getRawParameterValue("THRESHOLD");
	ratioParameter = apvts.getRawParameterValue("RATIO");
	limiterParameter = apvts.getRawParameterValue("LIMIT");
	
	atkParameter = apvts.getRawParameterValue("ATK");
	atkParameter = apvts.getRawParameterValue("RLS");

}

YAMSAudioProcessor::~YAMSAudioProcessor()
{
}

//==============================================================================
const juce::String YAMSAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool YAMSAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool YAMSAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool YAMSAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double YAMSAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int YAMSAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int YAMSAudioProcessor::getCurrentProgram()
{
    return 0;
}

void YAMSAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String YAMSAudioProcessor::getProgramName (int index)
{
    return {};
}

void YAMSAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void YAMSAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void YAMSAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool YAMSAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void YAMSAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	auto inputVolume = apvts.getRawParameterValue("INPUTVOLUME")->load();
	auto saturation = apvts.getRawParameterValue("SATURATION")->load();
	
	auto subGain = apvts.getRawParameterValue("SUBBAND")->load();
	auto lowGain = apvts.getRawParameterValue("LOWBAND")->load();
	auto midGain = apvts.getRawParameterValue("MIDBAND")->load();
	auto highGain = apvts.getRawParameterValue("HIGHBAND")->load();
	auto airGain = apvts.getRawParameterValue("AIRBAND")->load();
	
	auto keySelected = apvts.getRawParameterValue("KEY")->load();
	
	// Controls for compressor
	auto threshold = apvts.getRawParameterValue("THRESHOLD")->load();
	auto ratio = apvts.getRawParameterValue("RATIO")->load();
	
	auto limitThreshold = apvts.getRawParameterValue("LIMIT")->load();

	// Test values for EQ
	
//	eq.setSubFreq(60.f);
//	eq.setLowFreq(200.f);
//	eq.setMidFreq(1000.f);
//	eq.setHighFreq(5000.f);
//	eq.setAirFreq(10000.f);
	
	playHead = this->getPlayHead();
	playHead->getCurrentPosition (currentPositionInfo);
	
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
		for(int n = 0; n < buffer.getNumSamples(); n++) {
			 
			eq.setKey(keySelected);

			currentBPM = currentPositionInfo.bpm;

			float input = buffer.getReadPointer(channel)[n];
			
			input *= Decibels::decibelsToGain(inputVolume);
			input = preEQSaturationStage.processSample(input, saturation * .25, channel);
			input = eq.processSample(input, channel, subGain, lowGain, midGain, highGain, airGain);
			input = postEQSaturationStage.processSample(input, saturation * .25, channel);
			
			if(previousBPM != currentBPM) {
				currentBPM = (previousBPM*currentBPM) / 2;
			};
			
			previousBPM = currentBPM;
			
			buffer.getWritePointer(channel)[n] = input;
		}
    }
}

//==============================================================================
bool YAMSAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* YAMSAudioProcessor::createEditor()
{
    return new YAMSAudioProcessorEditor (*this);
}

//==============================================================================
void YAMSAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	auto state = apvts.copyState();
	std::unique_ptr<XmlElement> xml (state.createXml());
	copyXmlToBinary(*xml, destData);
}

void YAMSAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName (apvts.state.getType()))
			apvts.replaceState(ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new YAMSAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout YAMSAudioProcessor::createParams() {
	std::vector<std::unique_ptr<RangedAudioParameter>> params;
	
	// Adding input slider to params vector
	params.push_back(std::make_unique<AudioParameterFloat>("INPUTVOLUME", "Input Volume",-12.f,12.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("SATURATION", "Saturation",0.f,3.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("SUBBAND", "Sub Band",-6.f,6.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("LOWBAND", "Low Band",-6.f,6.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("MIDBAND", "Mid Band",-6.f,6.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("HIGHBAND", "High Band",-6.f,6.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("AIRBAND", "Air Band",-6.f,6.f,0.f));
	
	params.push_back(std::make_unique<AudioParameterChoice>("KEY","Key Select",StringArray("C","C#","D","Eb","E","F","F#","G","Ab","A","Bb","B"),0));
	
	params.push_back(std::make_unique<AudioParameterFloat>("THRESHOLD", "Threshold",-20.f,6.f,6.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("RATIO","Ratio",1.f,20.f,0.f));

	params.push_back(std::make_unique<AudioParameterFloat>("LIMIT","Limit",-6.f,-.1f,0.f));
	
	params.push_back(std::make_unique<AudioParameterChoice>("ATK","Attack",StringArray ("S","M","F"), 1));
	
	params.push_back(std::make_unique<AudioParameterChoice>("RLS","Release",StringArray ("S","M","F"), 1));
	
	
	return { params.begin(), params.end() };
}
