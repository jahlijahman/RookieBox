/*
  ==============================================================================

    DistortionProcessor.h
    Created: 2 Nov 2020 3:28:19pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include "ProcessorBase.h"

class DistortionProcessor  : public ProcessorBase
{
public:
    DistortionProcessor();

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

    //==============================================================================
    enum
    {
      waveshaperIndex                // [2]
    };

    juce::dsp::ProcessorChain<juce::dsp::WaveShaper<float>> processorChain; // [1] 

};
