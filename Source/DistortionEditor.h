/*
  ==============================================================================

    DistortionEditor.h
    Created: 2 Nov 2020 3:28:50pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DistortionProcessor.h"

//==============================================================================
/*
*/
class DistortionEditor  : public juce::AudioProcessorEditor
{
public:
    DistortionEditor(DistortionProcessor&);
    ~DistortionEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
  DistortionProcessor& distortionProcessor;

  //============================================================================
  juce::Slider gainSlider;

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionEditor)
};
