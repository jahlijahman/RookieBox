/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GainProcessor.h"

//==============================================================================
/**
*/

using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;

class RookieBoxAudioProcessor  : public juce::AudioProcessor,
                                 private juce::AudioProcessorValueTreeState::Listener
{
public:
    //==========================================================================
    RookieBoxAudioProcessor();
    ~RookieBoxAudioProcessor() override;

    //==========================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==========================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==========================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==========================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==========================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==========================================================================
    void initialiseGraph();
    void updateGraph();
    void connectAudioNodes();

    //==========================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    //==========================================================================
    std::unique_ptr<juce::AudioProcessorEditor> getEditor (Node::Ptr node);

    Node::Ptr gainNode;

    Node::Ptr slot1Node;
    Node::Ptr slot2Node;
    Node::Ptr slot3Node;

private:
    void parameterChanged(const juce::String &parameterID, float newValue);

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;

    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;

    juce::StringArray processorChoices { "Empty", "Gain"};

public:
    juce::AudioProcessorValueTreeState parameters;

private:

    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RookieBoxAudioProcessor)
};
