/*
  ==============================================================================

    GainProcessor.h
    Created: 28 Oct 2020 3:20:39pm
    Author:  eye

  ==============================================================================
*/

#pragma once
#include "ProcessorBase.h"

class GainProcessor  : public ProcessorBase
{
public:
    GainProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;

    void processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;

    void reset() override;

    bool hasEditor() const override;

    juce::AudioProcessorEditor* createEditor() override;

    const juce::String getName() const override;

    juce::AudioProcessorValueTreeState parameters;

private:
    juce::dsp::Gain<float> gain;


    //==========================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    float linearToDecibel(float linear);

};
