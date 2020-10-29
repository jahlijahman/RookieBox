/*
  ==============================================================================

    GainEditor.h
    Created: 28 Oct 2020 9:12:18pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GainProcessor.h"

//==============================================================================
/*
*/
class GainEditor  : public juce::AudioProcessorEditor
{
public:
    GainEditor(GainProcessor&);
    ~GainEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GainProcessor& gainProcessor;
    
    //==========================================================================
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainEditor)
};
