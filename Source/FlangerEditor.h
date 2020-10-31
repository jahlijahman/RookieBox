/*
  ==============================================================================

    FlangerEditor.h
    Created: 31 Oct 2020 5:39:12pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FlangerProcessor.h"
//==============================================================================
/*
*/
class FlangerEditor  : public juce::AudioProcessorEditor
{
public:
    FlangerEditor(FlangerProcessor&);
    ~FlangerEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    FlangerProcessor& flangerProcessor;

    juce::Slider feedbackSlider;

    //==========================================================================
    //Declare Sliders before the attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerEditor)
};
