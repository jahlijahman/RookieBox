/*
  ==============================================================================

    ModuleBoxComponent.cpp
    Created: 31 Oct 2020 12:40:38pm
    Author:  eye

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModuleBoxComponent.h"

//==============================================================================
ModuleBoxComponent::ModuleBoxComponent(RookieBoxAudioProcessor& p) : audioProcessor (p)
{


}

ModuleBoxComponent::~ModuleBoxComponent()
{
}

void ModuleBoxComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void ModuleBoxComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ModuleBoxComponent::editorsChanged()
{
  removeAllChildren();
  if(audioProcessor.editor1 != nullptr)
  {
    addAndMakeVisible(*audioProcessor.editor1);
    audioProcessor.editor1->setBounds(20, 100, 100, 100);

  }

  if(audioProcessor.editor2 != nullptr)
  {
    addAndMakeVisible(*audioProcessor.editor2);
    audioProcessor.editor2->setBounds(420, 100, 100, 100);
  }

  if(audioProcessor.editor3 != nullptr)
  {
    addAndMakeVisible(*audioProcessor.editor3);
    audioProcessor.editor3->setBounds(840, 100, 100, 100);
  }

}
