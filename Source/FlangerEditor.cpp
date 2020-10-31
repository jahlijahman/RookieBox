/*
  ==============================================================================

    FlangerEditor.cpp
    Created: 31 Oct 2020 5:39:12pm
    Author:  eye

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FlangerEditor.h"

//==============================================================================
FlangerEditor::FlangerEditor(FlangerProcessor& p) : AudioProcessorEditor (&p), flangerProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    feedbackSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(feedbackSlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (flangerProcessor.parameters, "FEEDBACK", feedbackSlider);


}

FlangerEditor::~FlangerEditor()
{
}

void FlangerEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component


}

void FlangerEditor::resized()
{
  feedbackSlider.setBounds(18, 18, 80, 80);

}
