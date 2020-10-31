/*
  ==============================================================================

    FlangerProcessor.cpp
    Created: 31 Oct 2020 5:26:27pm
    Author:  eye

  ==============================================================================
*/

#include "FlangerProcessor.h"
#include "FlangerEditor.h"

FlangerProcessor::FlangerProcessor() : parameters (*this, nullptr, "Parameters", createParameters())
{

}

void FlangerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)

{

}

void FlangerProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    //Curious to see your maths ;)
    
}

void FlangerProcessor::reset()
{

}

bool FlangerProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FlangerProcessor::createEditor()
{
    return new FlangerEditor (*this);
}

const juce::String FlangerProcessor::getName() const  { return "Flanger"; }


juce::AudioProcessorValueTreeState::ParameterLayout FlangerProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
  //Add parameters here
  params.push_back(std::make_unique<juce::AudioParameterFloat> ("FEEDBACK", "Feedback", 0.0f, 1.0f, 0.1f));

  return {params.begin(), params.end()};
}
