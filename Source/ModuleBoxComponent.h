/*
  ==============================================================================

    ModuleBoxComponent.h
    Created: 31 Oct 2020 12:40:38pm
    Author:  eye

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ModuleBoxComponent  : public juce::Component
{
public:
    ModuleBoxComponent(RookieBoxAudioProcessor&);
    ~ModuleBoxComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //==========================================================================
    void editorsChanged();

private:
    RookieBoxAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleBoxComponent)
};
