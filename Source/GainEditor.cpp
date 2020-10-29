/*
  ==============================================================================

    GainEditor.cpp
    Created: 28 Oct 2020 9:12:18pm
    Author:  eye

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainEditor.h"

//==============================================================================
GainEditor::GainEditor(GainProcessor& p) : AudioProcessorEditor (&p), gainProcessor (p)
{
    setSize (100, 100);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(gainSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (gainProcessor.parameters, "GAIN", gainSlider);

}

GainEditor::~GainEditor()
{
}

void GainEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void GainEditor::resized()
{
        gainSlider.setBounds(18, 18, 80, 80);
}
