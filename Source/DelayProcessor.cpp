/*
  ==============================================================================

    DelayProcessor.cpp
    Created: 1 Nov 2020 1:12:31pm
    Author:  eye

  ==============================================================================
*/

#include "DelayProcessor.h"
#include "DelayEditor.h"

DelayProcessor::DelayProcessor() : parameters (*this, nullptr, "Parameters", createParameters())
{

}

void DelayProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)

{

}

void DelayProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    //Curious to see your maths ;)

}

void DelayProcessor::reset()
{

}

bool DelayProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* DelayProcessor::createEditor()
{
    return new DelayEditor (*this);
}

const juce::String DelayProcessor::getName() const  { return "Delay"; }


juce::AudioProcessorValueTreeState::ParameterLayout DelayProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
  //Add parameters here
  params.push_back(std::make_unique<juce::AudioParameterFloat> ("FEEDBACK", "Feedback", 0.0f, 1.0f, 0.1f));

  return {params.begin(), params.end()};
}
