/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class EQChainAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    EQChainAudioProcessor();
    ~EQChainAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void updateChain();

    // juce::Decibels::dBtoGain wasnt working so I created my own math equation for it
    float dBtoGainFactor(float dB);

    //==============================================================================
    // Value Trees
    juce::AudioProcessorValueTreeState treestate;

private:

    //since ProcessorChain only takes four elements, I created a filterchain and incorporated
    //that inside the main processor chain

    using Filter = juce::dsp::IIR::Filter<float>;
    enum
    {
        f1,
        f2,
        f3,
        f4
    };
    using FilterChain = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
    using Gain = juce::dsp::Gain<float>;
    enum
    {
        ingainIndex,
        f1Index,
        f2Index,
        outgainIndex
    };
    using Monochain = juce::dsp::ProcessorChain<Gain, FilterChain, FilterChain, Gain>;
    Monochain leftchain, rightchain;
    // left and right chain for stereo ability

    //Parameters
    float ingain = 0.0;
    float firstbypass = 1;
    float firstfiltertype = 0.0;
    float firstf = 20.0;
    float firstg = 0.0;
    float firstq = 0.5;
    float secondbypass = 1;
    float secondfiltertype = 0.0;
    float secondf = 20.0;
    float secondg = 0.0;
    float secondq = 0.5;
    float thirdbypass = 0;
    float thirdfiltertype = 0.0;
    float thirdf = 20.0;
    float thirdg = 0.0;
    float thirdq = 0.5;
    float fourthbypass = 0;
    float fourthfiltertype = 0.0;
    float fourthf = 20.0;
    float fourthg = 0.0;
    float fourthq = 0.5;
    float fifthbypass = 0;
    float fifthfiltertype = 0.0;
    float fifthf = 20.0;
    float fifthg = 0.0;
    float fifthq = 0.5;
    float sixthbypass = 0;
    float sixthfiltertype = 0.0;
    float sixthf = 20.0;
    float sixthg = 0.0;
    float sixthq = 0.5;
    float seventhbypass = 1;
    float seventhfiltertype = 0.0;
    float seventhf = 20.0;
    float seventhg = 0.0;
    float seventhq = 0.5;
    float eighthbypass = 1;
    float eighthfiltertype = 0.0;
    float eighthf = 20.0;
    float eighthg = 0.0;
    float eighthq = 0.5;
    float outgain = 0.0;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQChainAudioProcessor)
};
