/*
  ==============================================================================

    DelayEditor.cpp
    Created: 1 Nov 2020 1:13:02pm
    Author:  eye

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayEditor.h"

//==============================================================================
DelayEditor::DelayEditor(DelayProcessor& p): AudioProcessorEditor (&p), delayProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    feedbackSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(feedbackSlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (delayProcessor.parameters, "FEEDBACK", feedbackSlider);


}

DelayEditor::~DelayEditor()
{
}

void DelayEditor::paint (juce::Graphics& g)
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

void DelayEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    feedbackSlider.setBounds(18, 18, 80, 80);

}
