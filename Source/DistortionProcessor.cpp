/*
  ==============================================================================

    DistortionProcessor.cpp
    Created: 2 Nov 2020 3:28:19pm
    Author:  eye

  ==============================================================================
*/

#include "DistortionProcessor.h"

#include "DistortionProcessor.h"
#include "DistortionEditor.h"


DistortionProcessor::DistortionProcessor() : parameters (*this, nullptr, "Parameters", createParameters())
{
  auto& waveshaper = processorChain.template get<waveshaperIndex>();         // [5]
  waveshaper.functionToUse = [] (float x)
                           {
                               return juce::jlimit (float (-0.1), float (0.1), x); // [6]
                           };
}

void DistortionProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)

{
  juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
  processorChain.prepare (spec);
}

void DistortionProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
  juce::dsp::AudioBlock<float> block (buffer);
  juce::dsp::ProcessContextReplacing<float> context (block);

  processorChain.process(context);

}

void DistortionProcessor::reset()
{
  processorChain.reset();
}

bool DistortionProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* DistortionProcessor::createEditor()
{
    return new DistortionEditor (*this);
}

const juce::String DistortionProcessor::getName() const  { return "Distortion"; }


juce::AudioProcessorValueTreeState::ParameterLayout DistortionProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
  //Add parameters here
  params.push_back(std::make_unique<juce::AudioParameterFloat> ("GAIN", "Gain", 0.0f, 1.0f, 0.1f));

  return {params.begin(), params.end()};
}
