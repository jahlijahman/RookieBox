/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RookieBoxAudioProcessor::RookieBoxAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      mainProcessor (new juce::AudioProcessorGraph()),
      parameters (*this, nullptr, "Parameters", createParameters())
{
  parameters.addParameterListener("SLOT1", this);
  parameters.addParameterListener("SLOT2", this);
  parameters.addParameterListener("SLOT3", this);
}

RookieBoxAudioProcessor::~RookieBoxAudioProcessor()
{
}

//==============================================================================
const juce::String RookieBoxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RookieBoxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RookieBoxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RookieBoxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RookieBoxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RookieBoxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RookieBoxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RookieBoxAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RookieBoxAudioProcessor::getProgramName (int index)
{
    return {};
}

void RookieBoxAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RookieBoxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  mainProcessor->setPlayConfigDetails (getMainBusNumInputChannels(),
                                       getMainBusNumOutputChannels(),
                                       sampleRate, samplesPerBlock);

  mainProcessor->prepareToPlay (sampleRate, samplesPerBlock);

  initialiseGraph();
}

void RookieBoxAudioProcessor::releaseResources()
{
  mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RookieBoxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  if (layouts.getMainInputChannelSet()  == juce::AudioChannelSet::disabled()
    || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
    && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

  return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

void RookieBoxAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    mainProcessor->processBlock(buffer, midiMessages);
}

void RookieBoxAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
  updateGraph();
}

//==============================================================================
bool RookieBoxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RookieBoxAudioProcessor::createEditor()
{
    return new RookieBoxAudioProcessorEditor (*this);
}

//==============================================================================
void RookieBoxAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RookieBoxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void RookieBoxAudioProcessor::initialiseGraph()
{
  mainProcessor->clear();
  audioInputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
  audioOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
  gainNode = mainProcessor->addNode(std::make_unique<GainProcessor>());

  gainNode->getProcessor()->setPlayConfigDetails (getMainBusNumInputChannels(), getMainBusNumOutputChannels(),
                                                  getSampleRate(), getBlockSize());

  connectAudioNodes();
}

void RookieBoxAudioProcessor::connectAudioNodes()
{
  for (int channel = 0; channel < 2; ++channel)
  {
    //gainNode always connected
    mainProcessor->addConnection ({ { audioInputNode->nodeID,  channel }, { gainNode->nodeID, channel } });
    mainProcessor->addConnection ({ { gainNode->nodeID,  channel }, { audioOutputNode->nodeID, channel } });
  }
}

void RookieBoxAudioProcessor::updateGraph()
{

  bool hasChanged = false;

  juce::Array<std::atomic<float>*> choices {parameters.getRawParameterValue("SLOT1"),
                                            parameters.getRawParameterValue("SLOT2"),
                                            parameters.getRawParameterValue("SLOT3") };

  juce::Array<juce::RangedAudioParameter*> bypasses {parameters.getParameter("BYPASS1"),
                                                     parameters.getParameter("BYPASS2"),
                                                     parameters.getParameter("BYPASS3")};

  slots.add (slot1Node);
  slots.add (slot2Node);
  slots.add (slot3Node);

 for (int i = 0; i < 3; ++i)
 {
     auto choice = choices[i]->load();
     auto  slot   = slots  .getUnchecked (i);

     if (choice == 1)            // [1]
     {
         if (slot != nullptr)
         {
             mainProcessor->removeNode (slot.get());
             slots.set (i, nullptr);
             hasChanged = true;
         }

     }
     else if (choice == 2)       // [2]
     {
         if (slot != nullptr)
         {
             if (slot->getProcessor()->getName() == "Gain")
             {
               continue;
             }


             mainProcessor->removeNode (slot.get());
         }

         slots.set (i, mainProcessor->addNode (std::make_unique<GainProcessor>()));
         hasChanged = true;
     }
 }
//! [updateGraph loop]

//! [updateGraph connect]
 if (hasChanged)
 {
     for (auto connection : mainProcessor->getConnections())     // [5]
         mainProcessor->removeConnection (connection);

     juce::ReferenceCountedArray<Node> activeSlots;
     int j = 0;
     for (auto slot : slots)
     {
         if (slot != nullptr)
         {
            activeSlots.add (slot);                             // [6]

            slot->getProcessor()->setPlayConfigDetails (getMainBusNumInputChannels(),
                                                        getMainBusNumOutputChannels(),
                                                        getSampleRate(), getBlockSize());
            if(j==0)
                editor1 = std::unique_ptr<juce::AudioProcessorEditor>(slot->getProcessor()->createEditor());
            if(j==1)
                editor2 = std::unique_ptr<juce::AudioProcessorEditor>(slot->getProcessor()->createEditor());
            if(j==2)
                editor3 = std::unique_ptr<juce::AudioProcessorEditor>(slot->getProcessor()->createEditor());

         }
         else
         {
           if(j==0)
             editor1.reset(nullptr);
           if(j==1)
             editor2.reset(nullptr);
           if(j==2)
             editor3.reset(nullptr);

         }
           ++j;
     }

     if (activeSlots.isEmpty())                                  // [7]
     {
         connectAudioNodes();
     }

     else
     {
         for (int i = 0; i < activeSlots.size() - 1; ++i)        // [8]
         {

             for (int channel = 0; channel < 2; ++channel)
                 mainProcessor->addConnection ({ { activeSlots.getUnchecked (i)->nodeID,      channel },
                                                 { activeSlots.getUnchecked (i + 1)->nodeID,  channel } });
         }

         for (int channel = 0; channel < 2; ++channel)           // [9]
         {
             mainProcessor->addConnection ({ { audioInputNode->nodeID,         channel },
                                             { activeSlots.getFirst()->nodeID, channel } });
             mainProcessor->addConnection ({ { activeSlots.getLast()->nodeID,  channel },
                                             { gainNode->nodeID,        channel } });
             mainProcessor->addConnection ({ { gainNode->nodeID,  channel },
                                             { audioOutputNode->nodeID,        channel } });
         }
     }


     for (auto node : mainProcessor->getNodes())                 // [10]
         node->getProcessor()->enableAllBuses();
 }

}

std::unique_ptr<juce::AudioProcessorEditor> RookieBoxAudioProcessor::getEditor (Node::Ptr node)
{
    return std::unique_ptr<juce::AudioProcessorEditor>( node->getProcessor()->createEditor() );
}

juce::AudioProcessorValueTreeState::ParameterLayout RookieBoxAudioProcessor::createParameters()
{
  std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

  params.push_back(std::make_unique<juce::AudioParameterInt> ("SLOT1", "Slot 1", 1, 2, 1));
  params.push_back(std::make_unique<juce::AudioParameterInt> ("SLOT2", "Slot 2", 1, 2, 1));
  params.push_back(std::make_unique<juce::AudioParameterInt> ("SLOT3", "Slot 3", 1, 2, 1));

  params.push_back(std::make_unique<juce::AudioParameterBool> ("BYPASS1", "Bypass 1", false));
  params.push_back(std::make_unique<juce::AudioParameterBool> ("BYPASS2", "Bypass 1", false));
  params.push_back(std::make_unique<juce::AudioParameterBool> ("BYPASS3", "Bypass 1", false));

  return {params.begin(), params.end()};
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RookieBoxAudioProcessor();
}
