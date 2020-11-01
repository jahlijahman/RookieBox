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
    setSize (1200, 816);

    addAndMakeVisible (nodeSelektor1);
    addAndMakeVisible (nodeSelektor2);
    addAndMakeVisible (nodeSelektor3);

    nodeSelektor1.addItem("Empty", 1);
    nodeSelektor1.addItem("Gain", 2);
    nodeSelektor1.addItem("Flanger", 3);
    nodeSelektor1.addItem("Delay", 4);
    nodeSelektor1.onChange = [this] { moduleBoxComponent.editorsChanged(); };

    nodeSelektor2.addItem("Empty", 1);
    nodeSelektor2.addItem("Gain", 2);
    nodeSelektor2.addItem("Flanger", 3);
    nodeSelektor2.addItem("Delay", 4);
    nodeSelektor2.onChange = [this] { moduleBoxComponent.editorsChanged(); };

    nodeSelektor3.addItem("Empty", 1);
    nodeSelektor3.addItem("Gain", 2);
    nodeSelektor3.addItem("Flanger", 3);
    nodeSelektor3.addItem("Delay", 4);
    nodeSelektor3.onChange = [this] { moduleBoxComponent.editorsChanged(); };

    nodeAttachment1 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "SLOT1" , nodeSelektor1);
    nodeAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "SLOT2" , nodeSelektor2);
    nodeAttachment3 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "SLOT3" , nodeSelektor3);

    //==========================================================================
    addAndMakeVisible(moduleBoxComponent);

    gainEditor = audioProcessor.getEditor(audioProcessor.gainNode);
    addAndMakeVisible(*gainEditor);
    gainEditor->setBounds(1100, 700,100,100);
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
  nodeSelektor1.setBounds(20, 700, 100, 20);
  nodeSelektor2.setBounds(420, 700, 100, 20);
  nodeSelektor3.setBounds(840, 700, 100, 20);

  moduleBoxComponent.setBounds(10, 10, 1100, 600);
}
