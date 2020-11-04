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
    const int numInputChannles = getTotalNumInputChannels();
    const int delayBufferSize = 2 * (sampleRate + samplesPerBlock);
    mSampleRate = sampleRate;
    
    mDelayBuffer.setSize(numInputChannles, delayBufferSize);

}

void DelayProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    //Not sure if I actually need this code. If it's still here then it's probably for a good reason. This includes the following code from here>>
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());
    //to here<<
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();
    
    for(int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);
        
        fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
    }
    
    mWritePosition += bufferLength;
    mWritePosition %= delayBufferLength;
}

void DelayProcessor::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    //copy the data from mainBuffer to delayBuffer
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, 0.8, 0.8);
    }
    else {
        const int bufferRemaining = delayBufferLength - mWritePosition;
    
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, 0.8, 0.8);
        mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, 0.8, 0.8);
    }
}

void DelayProcessor::getFromDelayBuffer (juce::AudioSampleBuffer& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    int delayTime = 500;
    const int readPosition = static_cast<int> (delayBufferLength + mWritePosition - (mSampleRate * delayTime /1000)) % delayBufferLength;
    
    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferLength);
    }
    else {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
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
