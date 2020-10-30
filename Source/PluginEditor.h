/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class RookieBoxAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RookieBoxAudioProcessorEditor (RookieBoxAudioProcessor&);
    ~RookieBoxAudioProcessorEditor() override;

    //==========================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==========================================================================

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RookieBoxAudioProcessor& audioProcessor;

    //==========================================================================
    std::unique_ptr<juce::AudioProcessorEditor> gainEditor;

    //==========================================================================
    juce::ComboBox nodeSelektor1;
    juce::ComboBox nodeSelektor2;
    juce::ComboBox nodeSelektor3;

    //==========================================================================
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> nodeAttachment1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> nodeAttachment2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> nodeAttachment3;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RookieBoxAudioProcessorEditor)
};
