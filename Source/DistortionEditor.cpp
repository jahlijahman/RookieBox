/*
  ==============================================================================

    DistortionEditor.cpp
    Created: 2 Nov 2020 3:28:50pm
    Author:  eye

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionEditor.h"

//==============================================================================
DistortionEditor::DistortionEditor(DistortionProcessor& p) : AudioProcessorEditor (&p), distortionProcessor (p)
{
  gainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  gainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
  addAndMakeVisible(gainSlider);
  gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (distortionProcessor.parameters, "GAIN", gainSlider);
}

DistortionEditor::~DistortionEditor()
{
}

void DistortionEditor::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component


}

void DistortionEditor::resized()
{
    gainSlider.setBounds(18,18,80,80);

}
