/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
//Neue Änderung
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainPanPluginAudioProcessorEditor::GainPanPluginAudioProcessorEditor (GainPanPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(&gainSlider);
    gainSlider.setSliderStyle(Slider::LinearVertical);
    sliderAttachments.add(new APVTS::SliderAttachment (p.getTree(), GainPanPluginAudioProcessor::GainId, gainSlider));
    
    addAndMakeVisible(&panKnob);
    panKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderAttachments.add(new APVTS::SliderAttachment (p.getTree(), GainPanPluginAudioProcessor::PanId, panKnob));
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

GainPanPluginAudioProcessorEditor::~GainPanPluginAudioProcessorEditor()
{
}

//==============================================================================
void GainPanPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void GainPanPluginAudioProcessorEditor::resized()
{
    auto area (getLocalBounds());
    
    const auto sliderWidth {180};
    const auto textBoxHeight { 25 };
    
    const auto gainSliderArea {area.removeFromLeft(sliderWidth)};
    gainSlider.setBounds(gainSliderArea);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderWidth, textBoxHeight);
    
    const auto panKnobSize { 380 };
    Rectangle<int> panKnobArea (panKnobSize, panKnobSize);
    panKnobArea.setCentre (area.getCentre());
    panKnob.setBounds(panKnobArea);
    panKnob.setTextBoxStyle(Slider::TextBoxBelow, false, panKnobSize, textBoxHeight);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
