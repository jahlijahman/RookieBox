/*
  ==============================================================================

    GainProcessor.cpp
    Created: 29 Oct 2020 12:22:08pm
    Author:  eye

  ==============================================================================
*/

#include "GainProcessor.h"
#include "GainEditor.h"

GainProcessor::GainProcessor() : parameters (*this, nullptr, "Parameters", createParameters())
{
    gain.setGainDecibels (-6.0f);
}

void GainProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)

{
    juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    gain.prepare (spec);
}

void GainProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    auto gainParam = parameters.getRawParameterValue("GAIN");
    gain.setGainDecibels( linearToDecibel( gainParam->load()));
    gain.process (context);
}

void GainProcessor::reset()
{
    gain.reset();
}

bool GainProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* GainProcessor::createEditor()
{
    return new GainEditor (*this);
}

const juce::String GainProcessor::getName() const  { return "Gain"; }


juce::AudioProcessorValueTreeState::ParameterLayout GainProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

  params.push_back(std::make_unique<juce::AudioParameterFloat> ("GAIN", "Gain", 0.0f, 1.0f, 0.1f));

  return {params.begin(), params.end()};
}

float GainProcessor::linearToDecibel(float linear)
{
   float db;

   if (linear != 0.0f)
     db = 20.0f * log10(linear);
   else
     db = -144.0f;  // effectively minus infinity

   return db;
}
