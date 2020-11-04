/*
  ==============================================================================

    DelayProcessor.h
    Created: 1 Nov 2020 1:12:31pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include "ProcessorBase.h"

class DelayProcessor  : public ProcessorBase
{
public:
    DelayProcessor();

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

};
