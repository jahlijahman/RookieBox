/*
  ==============================================================================

    DelayEditor.h
    Created: 1 Nov 2020 1:13:02pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DelayProcessor.h"
//==============================================================================
/*
*/
class DelayEditor  : public juce::AudioProcessorEditor
{
public:
    DelayEditor(DelayProcessor&);
    ~DelayEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
  DelayProcessor& delayProcessor;

  juce::Slider feedbackSlider;

  //==========================================================================
  //Declare Sliders before the attachments
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayEditor)
};
