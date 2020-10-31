/*
  ==============================================================================

    FlangerProcessor.h
    Created: 31 Oct 2020 5:26:27pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include "ProcessorBase.h"

class FlangerProcessor  : public ProcessorBase
{
public:
    FlangerProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;

    void processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;

    void reset() override;

    bool hasEditor() const override;

    juce::AudioProcessorEditor* createEditor() override;

    const juce::String getName() const override;

    juce::AudioProcessorValueTreeState parameters;

private:
  
    //==========================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    float linearToDecibel(float linear);

};
