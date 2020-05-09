/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GainPanPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GainPanPluginAudioProcessorEditor (GainPanPluginAudioProcessor&);
    ~GainPanPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    Slider gainSlider;
    Slider panKnob;
    
    OwnedArray<APVTS::SliderAttachment> sliderAttachments;
    
    
    GainPanPluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPanPluginAudioProcessorEditor)
};
