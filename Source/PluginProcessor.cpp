/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainPanPluginAudioProcessor::GainPanPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "PARAMETERS",
    {
        std::make_unique<AudioParameterFloat>(GainId, "Gain", NormalisableRange<float>(-80.0f, 6.0f), -12.0f),
        std::make_unique<AudioParameterFloat>(PanId, "Pan", NormalisableRange<float>(-1.f, 1.0f), 0.0f)
    } )
#endif
{
    tree.addParameterListener(GainId, this);
    tree.addParameterListener(PanId, this);
}

GainPanPluginAudioProcessor::~GainPanPluginAudioProcessor()
{
    
}

void GainPanPluginAudioProcessor::parameterChanged(const String &parameterID, float newValue)
{
    if (parameterID == GainId)
    {
        for (int ch = 0; ch < 2; ch++)
            gainValue[ch].setTargetValue(Decibels::decibelsToGain(newValue));
    }
    else if (parameterID == PanId)
    {
        panValue[0].setTargetValue (jmap(newValue, -1.f, 1.f, 1.f, 0.f));
        panValue[1].setTargetValue (jmap(newValue, -1.f, 0.f, 0.f, 1.f));

    }
}

//==============================================================================
const String GainPanPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainPanPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainPanPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainPanPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainPanPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainPanPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainPanPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainPanPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String GainPanPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainPanPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainPanPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int ch = 0; ch < 2; ch++)
    {
        gainValue[ch].reset (sampleRate, 1.0);
        panValue[ch].reset (sampleRate, 1.0);

    }
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainPanPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainPanPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void GainPanPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int ch {0}; ch < totalNumOutputChannels; ch++)
    {
        auto writePointer{ buffer.getWritePointer(ch)};  // mit writepointer kann ich über die Samples iterieren
        
        for (int samp { 0 }; samp < buffer.getNumSamples(); samp++)
        {
            writePointer [samp] *= gainValue [ch].getNextValue();
            writePointer [samp] *= gainValue [ch].getNextValue();
        }
    }
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool GainPanPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainPanPluginAudioProcessor::createEditor()
{
    return new GainPanPluginAudioProcessorEditor (*this);
}

//==============================================================================
void GainPanPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainPanPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainPanPluginAudioProcessor();
}
