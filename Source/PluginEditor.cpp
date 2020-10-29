/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RookieBoxAudioProcessorEditor::RookieBoxAudioProcessorEditor (RookieBoxAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    gainEditor = audioProcessor.getEditor(audioProcessor.gainNode);
    addAndMakeVisible(*gainEditor);
}

RookieBoxAudioProcessorEditor::~RookieBoxAudioProcessorEditor()
{
}

//==============================================================================
void RookieBoxAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void RookieBoxAudioProcessorEditor::resized()
{
  //auto& editor = *gainEditor;
  //gainEditor->setBounds(0,0,100,100);
}
