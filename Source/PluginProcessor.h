/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
typedef AudioProcessorValueTreeState APVTS;

class GainPanPluginAudioProcessor  : public AudioProcessor, public APVTS::Listener
{
public:
    //==============================================================================
    GainPanPluginAudioProcessor();
    ~GainPanPluginAudioProcessor();

    void parameterChanged(const String &parameterID, float newValue) override;
    
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static inline const String GainId { "gain" }; //statische Variablen müssen "inline" sein
    static inline const String PanId { "pan" };
    APVTS& getTree () {return tree; }
    
private:
    APVTS tree; //ist der Parameter-Halter in der DAW
    
 //   Atomic <float> gainValue [2];  //Zwischen-Variable, um zwischen Audio-Thread und anderen zu kommunizieren
 //   Atomic <float> panValue [2];
    
    LinearSmoothedValue<float> gainValue [2];
    LinearSmoothedValue<float> panValue [2];

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPanPluginAudioProcessor)
};
