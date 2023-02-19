/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQChainAudioProcessor::EQChainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treestate(*this, nullptr, "PARMETERS", createParameterLayout()), leftchain(), rightchain()
#endif
{
    treestate.addParameterListener("input gain", this);

    treestate.addParameterListener("first filter type", this);
    treestate.addParameterListener("first bypass", this);
    treestate.addParameterListener("first freq", this);
    treestate.addParameterListener("first gain", this);
    treestate.addParameterListener("first q", this);

    treestate.addParameterListener("second filter type", this);
    treestate.addParameterListener("second bypass", this);
    treestate.addParameterListener("second freq", this);
    treestate.addParameterListener("second gain", this);
    treestate.addParameterListener("second q", this);

    treestate.addParameterListener("third filter type", this);
    treestate.addParameterListener("third bypass", this);
    treestate.addParameterListener("third freq", this);
    treestate.addParameterListener("third gain", this);
    treestate.addParameterListener("third q", this);

    treestate.addParameterListener("fourth filter type", this);
    treestate.addParameterListener("fourth bypass", this);
    treestate.addParameterListener("fourth freq", this);
    treestate.addParameterListener("fourth gain", this);
    treestate.addParameterListener("fourth q", this);

    treestate.addParameterListener("fifth filter type", this);
    treestate.addParameterListener("fifth bypass", this);
    treestate.addParameterListener("fifth freq", this);
    treestate.addParameterListener("fifth gain", this);
    treestate.addParameterListener("fifth q", this);

    treestate.addParameterListener("sixth filter type", this);
    treestate.addParameterListener("sixth bypass", this);
    treestate.addParameterListener("sixth freq", this);
    treestate.addParameterListener("sixth gain", this);
    treestate.addParameterListener("sixth q", this);

    treestate.addParameterListener("seventh filter type", this);
    treestate.addParameterListener("seventh bypass", this);
    treestate.addParameterListener("seventh freq", this);
    treestate.addParameterListener("seventh gain", this);
    treestate.addParameterListener("seventh q", this);

    treestate.addParameterListener("eighth filter type", this);
    treestate.addParameterListener("eighth bypass", this);
    treestate.addParameterListener("eighth freq", this);
    treestate.addParameterListener("eighth gain", this);
    treestate.addParameterListener("eighth q", this);

    treestate.addParameterListener("output gain", this);
}

EQChainAudioProcessor::~EQChainAudioProcessor()
{
    treestate.removeParameterListener("input gain", this);

    treestate.removeParameterListener("first filter type", this);
    treestate.removeParameterListener("first bypass", this);
    treestate.removeParameterListener("first freq", this);
    treestate.removeParameterListener("first gain", this);
    treestate.removeParameterListener("first q", this);

    treestate.removeParameterListener("second filter type", this);
    treestate.removeParameterListener("second bypass", this);
    treestate.removeParameterListener("second freq", this);
    treestate.removeParameterListener("second gain", this);
    treestate.removeParameterListener("second q", this);

    treestate.removeParameterListener("third filter type", this);
    treestate.removeParameterListener("third bypass", this);
    treestate.removeParameterListener("third freq", this);
    treestate.removeParameterListener("third gain", this);
    treestate.removeParameterListener("third q", this);

    treestate.removeParameterListener("fourth filter type", this);
    treestate.removeParameterListener("fourth bypass", this);
    treestate.removeParameterListener("fourth freq", this);
    treestate.removeParameterListener("fourth gain", this);
    treestate.removeParameterListener("fourth q", this);

    treestate.removeParameterListener("fifth filter type", this);
    treestate.removeParameterListener("fifth bypass", this);
    treestate.removeParameterListener("fifth freq", this);
    treestate.removeParameterListener("fifth gain", this);
    treestate.removeParameterListener("fifth q", this);

    treestate.removeParameterListener("sixth filter type", this);
    treestate.removeParameterListener("sixth bypass", this);
    treestate.removeParameterListener("sixth freq", this);
    treestate.removeParameterListener("sixth gain", this);
    treestate.removeParameterListener("sixth q", this);

    treestate.removeParameterListener("seventh filter type", this);
    treestate.removeParameterListener("seventh bypass", this);
    treestate.removeParameterListener("seventh freq", this);
    treestate.removeParameterListener("seventh gain", this);
    treestate.removeParameterListener("seventh q", this);

    treestate.removeParameterListener("eighth filter type", this);
    treestate.removeParameterListener("eighth bypass", this);
    treestate.removeParameterListener("eighth freq", this);
    treestate.removeParameterListener("eighth gain", this);
    treestate.removeParameterListener("eighth q", this);

    treestate.removeParameterListener("output gain", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout EQChainAudioProcessor::createParameterLayout()
{
    std::vector < std::unique_ptr<juce::RangedAudioParameter >> params;

    juce::StringArray filter1choice = { "Low Cut", "Low Shelf", "Peak" };
    juce::StringArray filter2choice = { "Low Cut", "Low Shelf", "Peak" };
    juce::StringArray filter3choice = { "Peak", "Low Shelf", "High Shelf", "Low Cut", "High Cut" };
    juce::StringArray filter4choice = { "Peak", "Low Shelf", "High Shelf", "Low Cut", "High Cut" };

    juce::StringArray filter5choice = { "Peak", "High Shelf", "Low Shelf", "High Cut", "Low Cut" };
    juce::StringArray filter6choice = { "Peak", "High Shelf", "Low Shelf", "High Cut", "Low Cut" };
    juce::StringArray filter7choice = { "High Cut", "High Shelf", "Peak" };
    juce::StringArray filter8choice = { "High Cut", "High Shelf", "Peak" };

    auto pInputGain = std::make_unique<juce::AudioParameterFloat>("input gain", "Input Gain", -36.0, 6.0, 0.0);

    auto pFirstBypass = std::make_unique<juce::AudioParameterBool>("first bypass", "First Bypass", 1);
    auto pFirstFilter = std::make_unique<juce::AudioParameterChoice>("first filter type", "First Filter Type", filter1choice, 0.0);
    auto pFirstFreq = std::make_unique<juce::AudioParameterFloat>("first freq", "First Freq", 20.0, 60.0, 20.0);
    auto pFirstGain = std::make_unique<juce::AudioParameterFloat>("first gain", "First Gain", -48.0, 12.0, 0.0);
    auto pFirstQ = std::make_unique<juce::AudioParameterFloat>("first q", "First Q", 0.5, 10.0, 0.5);

    auto pSecondBypass = std::make_unique<juce::AudioParameterBool>("second bypass", "Second Bypass", 1);
    auto pSecondFilter = std::make_unique<juce::AudioParameterChoice>("second filter type", "Second Filter Type", filter2choice, 0.0);
    auto pSecondFreq = std::make_unique<juce::AudioParameterFloat>("second freq", "Second Freq", 60.0, 300.0, 60.0);
    auto pSecondGain = std::make_unique<juce::AudioParameterFloat>("second gain", "Second Gain", -48.0, 12.0, 0.0);
    auto pSecondQ = std::make_unique<juce::AudioParameterFloat>("second q", "Second Q", 0.5, 10.0, 0.5);

    auto pThirdBypass = std::make_unique<juce::AudioParameterBool>("third bypass", "Third Bypass", 0);
    auto pThirdFilter = std::make_unique<juce::AudioParameterChoice>("third filter type", "Third Filter Type", filter3choice, 0.0);
    auto pThirdFreq = std::make_unique<juce::AudioParameterFloat>("third freq", "Third Freq", 300.0, 1100.0, 300.0);
    auto pThirdGain = std::make_unique<juce::AudioParameterFloat>("third gain", "Third Gain", -48.0, 12.0, 0.0);
    auto pThirdQ = std::make_unique<juce::AudioParameterFloat>("third q", "Third Q", 0.5, 10.0, 0.5);

    auto pFourthBypass = std::make_unique<juce::AudioParameterBool>("fourth bypass", "Fourth Bypass", 0);
    auto pFourthFilter = std::make_unique<juce::AudioParameterChoice>("fourth filter type", "Fourth Filter Type", filter4choice, 0.0);
    auto pFourthFreq = std::make_unique<juce::AudioParameterFloat>("fourth freq", "Fourth Freq", 1100.0, 2000.0, 1100.0);
    auto pFourthGain = std::make_unique<juce::AudioParameterFloat>("fourth gain", "Fourth Gain", -48.0, 12.0, 0.0);
    auto pFourthQ = std::make_unique<juce::AudioParameterFloat>("fourth q", "Fourth Q", 0.5, 10.0, 0.5);

    auto pFifthBypass = std::make_unique<juce::AudioParameterBool>("fifth bypass", "Fifth Bypass", 0);
    auto pFifthFilter = std::make_unique<juce::AudioParameterChoice>("fifth filter type", "Fifth Filter Type", filter5choice, 0.0);
    auto pFifthFreq = std::make_unique<juce::AudioParameterFloat>("fifth freq", "Fifth Freq", 2000.0, 4000.0, 2000.0);
    auto pFifthGain = std::make_unique<juce::AudioParameterFloat>("fifth gain", "Fifth Gain", -48.0, 12.0, 0.0);
    auto pFifthQ = std::make_unique<juce::AudioParameterFloat>("fifth q", "Fifth Q", 0.5, 10.0, 0.5);

    auto pSixthBypass = std::make_unique<juce::AudioParameterBool>("sixth bypass", "Sixth Bypass", 0);
    auto pSixthFilter = std::make_unique<juce::AudioParameterChoice>("sixth filter type", "Sixth Filter Type", filter6choice, 0.0);
    auto pSixthFreq = std::make_unique<juce::AudioParameterFloat>("sixth freq", "Sixth Freq", 4000.0, 6000.0, 4000.0);
    auto pSixthGain = std::make_unique<juce::AudioParameterFloat>("sixth gain", "Sixth Gain", -48.0, 12.0, 0.0);
    auto pSixthQ = std::make_unique<juce::AudioParameterFloat>("sixth q", "Sixth Q", 0.5, 10.0, 0.5);

    auto pSeventhBypass = std::make_unique<juce::AudioParameterBool>("seventh bypass", "Seventh Bypass", 1);
    auto pSeventhFilter = std::make_unique<juce::AudioParameterChoice>("seventh filter type", "Seventh Filter Type", filter7choice, 0.0);
    auto pSeventhFreq = std::make_unique<juce::AudioParameterFloat>("seventh freq", "Seventh Freq", 6000.0, 10000.0, 6000.0);
    auto pSeventhGain = std::make_unique<juce::AudioParameterFloat>("seventh gain", "Seventh Gain", -48.0, 12.0, 0.0);
    auto pSeventhQ = std::make_unique<juce::AudioParameterFloat>("seventh q", "Seventh Q", 0.5, 10.0, 0.5);

    auto pEighthBypass = std::make_unique<juce::AudioParameterBool>("eighth bypass", "Eighth Bypass", 1);
    auto pEighthFilter = std::make_unique<juce::AudioParameterChoice>("eighth filter type", "Eighth Filter Type", filter8choice, 0.0);
    auto pEighthFreq = std::make_unique<juce::AudioParameterFloat>("eighth freq", "Eighth Freq", 10000.0, 20000.0, 10000.0);
    auto pEighthGain = std::make_unique<juce::AudioParameterFloat>("eighth gain", "Eighth Gain", -48.0, 12.0, 0.0);
    auto pEighthQ = std::make_unique<juce::AudioParameterFloat>("eighth q", "Eighth Q", 0.5, 10.0, 0.5);

    auto pOutputGain = std::make_unique<juce::AudioParameterFloat>("output gain", "Output Gain", -36.0, 6.0, 0.0);

    params.push_back(std::move(pInputGain));

    params.push_back(std::move(pFirstBypass));
    params.push_back(std::move(pFirstFilter));
    params.push_back(std::move(pFirstFreq));
    params.push_back(std::move(pFirstGain));
    params.push_back(std::move(pFirstQ));

    params.push_back(std::move(pSecondBypass));
    params.push_back(std::move(pSecondFilter));
    params.push_back(std::move(pSecondFreq));
    params.push_back(std::move(pSecondGain));
    params.push_back(std::move(pSecondQ));

    params.push_back(std::move(pThirdBypass));
    params.push_back(std::move(pThirdFilter));
    params.push_back(std::move(pThirdFreq));
    params.push_back(std::move(pThirdGain));
    params.push_back(std::move(pThirdQ));

    params.push_back(std::move(pFourthBypass));
    params.push_back(std::move(pFourthFilter));
    params.push_back(std::move(pFourthFreq));
    params.push_back(std::move(pFourthGain));
    params.push_back(std::move(pFourthQ));

    params.push_back(std::move(pFifthBypass));
    params.push_back(std::move(pFifthFilter));
    params.push_back(std::move(pFifthFreq));
    params.push_back(std::move(pFifthGain));
    params.push_back(std::move(pFifthQ));

    params.push_back(std::move(pSixthBypass));
    params.push_back(std::move(pSixthFilter));
    params.push_back(std::move(pSixthFreq));
    params.push_back(std::move(pSixthGain));
    params.push_back(std::move(pSixthQ));

    params.push_back(std::move(pSeventhBypass));
    params.push_back(std::move(pSeventhFilter));
    params.push_back(std::move(pSeventhFreq));
    params.push_back(std::move(pSeventhGain));
    params.push_back(std::move(pSeventhQ));

    params.push_back(std::move(pEighthBypass));
    params.push_back(std::move(pEighthFilter));
    params.push_back(std::move(pEighthFreq));
    params.push_back(std::move(pEighthGain));
    params.push_back(std::move(pEighthQ));

    params.push_back(std::move(pOutputGain));

    return { params.begin(), params.end() };
}

void EQChainAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "input gain")
    {
        ingain = (newValue);
    }
    if (parameterID == "first bypass")
    {
        firstbypass = newValue;
    }
    if (parameterID == "first filter type")
    {
        firstfiltertype = newValue;
    }
    if (parameterID == "first freq")
    {
        firstf = newValue;
    }
    if (parameterID == "first gain")
    {
        firstg = newValue;
    }
    if (parameterID == "first q")
    {
        firstq = newValue;
    }
    if (parameterID == "second bypass")
    {
        secondbypass = newValue;
    }
    if (parameterID == "second filter type")
    {
        secondfiltertype = newValue;
    }
    if (parameterID == "second freq")
    {
        secondf = newValue;
    }
    if (parameterID == "second gain")
    {
        secondg = newValue;
    }
    if (parameterID == "second q")
    {
        secondq = newValue;
    }
    if (parameterID == "third bypass")
    {
        thirdbypass = newValue;
    }
    if (parameterID == "third filter type")
    {
        thirdfiltertype = newValue;
    }
    if (parameterID == "third freq")
    {
        thirdf = newValue;
    }
    if (parameterID == "third gain")
    {
        thirdg = newValue;
    }
    if (parameterID == "third q")
    {
        thirdq = newValue;
    }
    if (parameterID == "fourth bypass")
    {
        fourthbypass = newValue;
    }
    if (parameterID == "fourth filter type")
    {
        fourthfiltertype = newValue;
    }
    if (parameterID == "fourth freq")
    {
        fourthf = newValue;
    }
    if (parameterID == "fourth gain")
    {
        fourthg = newValue;
    }
    if (parameterID == "fourth q")
    {
        fourthq = newValue;
    }
    if (parameterID == "fifth bypass")
    {
        fifthbypass = newValue;
    }
    if (parameterID == "fifth filter type")
    {
        fifthfiltertype = newValue;
    }
    if (parameterID == "fifth freq")
    {
        fifthf = newValue;
    }
    if (parameterID == "fifth gain")
    {
        fifthg = newValue;
    }
    if (parameterID == "fifth q")
    {
        fifthq = newValue;
    }
    if (parameterID == "sixth bypass")
    {
        sixthbypass = newValue;
    }
    if (parameterID == "sixth filter type")
    {
        sixthfiltertype = newValue;
    }
    if (parameterID == "sixth freq")
    {
        sixthf = newValue;
    }
    if (parameterID == "sixth gain")
    {
        sixthg = newValue;
    }
    if (parameterID == "sixth q")
    {
        sixthq = newValue;
    }
    if (parameterID == "seventh bypass")
    {
        seventhbypass = newValue;
    }
    if (parameterID == "seventh filter type")
    {
        thirdfiltertype = newValue;
    }
    if (parameterID == "seventh freq")
    {
        seventhf = newValue;
    }
    if (parameterID == "seventh gain")
    {
        seventhg = newValue;
    }
    if (parameterID == "seventh q")
    {
        seventhq = newValue;
    }
    if (parameterID == "eighth bypass")
    {
        eighthbypass = newValue;
    }
    if (parameterID == "eighth filter type")
    {
        eighthfiltertype = newValue;
    }
    if (parameterID == "eighth freq")
    {
        eighthf = newValue;
    }
    if (parameterID == "eighth gain")
    {
        eighthg = newValue;
    }
    if (parameterID == "eighth q")
    {
        eighthq = newValue;
    }
    if (parameterID == "output gain")
    {
        outgain = (newValue);
    }
}

float EQChainAudioProcessor::dBtoGainFactor(float dB)
{
     return std::pow(10, dB / 20);
}
//==============================================================================
const juce::String EQChainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQChainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQChainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQChainAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQChainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQChainAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EQChainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQChainAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EQChainAudioProcessor::getProgramName (int index)
{
    return {};
}

void EQChainAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EQChainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1; // one channel per chain
    spec.sampleRate = sampleRate;

    leftchain.reset();
    rightchain.reset();
    leftchain.prepare(spec);
    rightchain.prepare(spec);

    updateChain();
}

void EQChainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQChainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EQChainAudioProcessor::updateChain()
{
    //input gain connection
    leftchain.get<ingainIndex>().setGainDecibels(*treestate.getRawParameterValue("input gain"));
    rightchain.get<ingainIndex>().setGainDecibels(*treestate.getRawParameterValue("input gain"));
    leftchain.get<ingainIndex>().setRampDurationSeconds(0.25);
    rightchain.get<ingainIndex>().setRampDurationSeconds(0.25);

    //filter parameter connection
    firstf = *treestate.getRawParameterValue("first freq");
    firstq = *treestate.getRawParameterValue("first q");
    firstg = *treestate.getRawParameterValue("first gain");
    secondf = *treestate.getRawParameterValue("second freq");
    secondq = *treestate.getRawParameterValue("second q");
    secondg = *treestate.getRawParameterValue("second gain");

    thirdf = *treestate.getRawParameterValue("third freq");
    thirdq = *treestate.getRawParameterValue("third q");
    thirdg = *treestate.getRawParameterValue("third gain");
    fourthf = *treestate.getRawParameterValue("fourth freq");
    fourthq = *treestate.getRawParameterValue("fourth q");
    fourthg = *treestate.getRawParameterValue("fourth gain");

    fifthf = *treestate.getRawParameterValue("fifth freq");
    fifthq = *treestate.getRawParameterValue("fifth q");
    fifthg = *treestate.getRawParameterValue("fifth gain");
    sixthf = *treestate.getRawParameterValue("sixth freq");
    sixthq = *treestate.getRawParameterValue("sixth q");
    sixthg = *treestate.getRawParameterValue("sixth gain");

    seventhf = *treestate.getRawParameterValue("seventh freq");
    seventhq = *treestate.getRawParameterValue("seventh q");
    seventhg = *treestate.getRawParameterValue("seventh gain");
    eighthf = *treestate.getRawParameterValue("eighth freq");
    eighthq = *treestate.getRawParameterValue("eighth q");
    eighthg = *treestate.getRawParameterValue("eighth gain");

    //builds filters based off the filter type choices and taking from parameters above
    if (*treestate.getRawParameterValue("first bypass") == 1.0)
    {
        leftchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("first filter type") == 0.0)
        {
            leftchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), firstf, firstq);
            rightchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), firstf, firstq);
        }
        if (*treestate.getRawParameterValue("first filter type") == 1.0)
        {
            leftchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), firstf, firstq, dBtoGainFactor(firstg));
            rightchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), firstf, firstq, dBtoGainFactor(firstg));
        }
        if (*treestate.getRawParameterValue("first filter type") == 2.0)
        {
            leftchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), firstf, firstq, dBtoGainFactor(firstg));
            rightchain.get<f1Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), firstf, firstq, dBtoGainFactor(firstg));
        }
    }
    
    if (*treestate.getRawParameterValue("second bypass") == 1.0)
    {
        leftchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("second filter type") == 0.0)
        {
                leftchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), secondf, secondq);
                rightchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), secondf, secondq);
        }
        if (*treestate.getRawParameterValue("second filter type") == 1.0)
        {
                leftchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), secondf, secondq, dBtoGainFactor(secondg));
                rightchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), secondf, secondq, dBtoGainFactor(secondg));
        }
        if (*treestate.getRawParameterValue("second filter type") == 2.0)
        {
                leftchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), secondf, secondq, dBtoGainFactor(secondg));
                rightchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), secondf, secondq, dBtoGainFactor(secondg));
        }
    }
    
    if (*treestate.getRawParameterValue("third bypass") == 1.0)
    {
        leftchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("third filter type") == 0.0)
        {
            leftchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), thirdf, thirdq, dBtoGainFactor(thirdg));
            rightchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), thirdf, thirdq, dBtoGainFactor(thirdg));
        }
        if (*treestate.getRawParameterValue("third filter type") == 1.0)
        {
            leftchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), thirdf, thirdq, dBtoGainFactor(thirdg));
            rightchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), thirdf, thirdq, dBtoGainFactor(thirdg));
        }
        if (*treestate.getRawParameterValue("third filter type") == 2.0)
        {
            leftchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), thirdf, thirdq, dBtoGainFactor(thirdg));
            rightchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), thirdf, thirdq, dBtoGainFactor(thirdg));
        }
        if (*treestate.getRawParameterValue("third filter type") == 3.0)
        {
            leftchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), thirdf, thirdq);
            rightchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), thirdf, thirdq);
        }
        if (*treestate.getRawParameterValue("third filter type") == 4.0)
        {
            leftchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), thirdf, thirdq);
            rightchain.get<f1Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), thirdf, thirdq);
        }
        
        
        
        
    }

    if (*treestate.getRawParameterValue("fourth bypass") == 1.0)
    {
        leftchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("fourth filter type") == 0.0)
        {
            leftchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), fourthf, fourthq, dBtoGainFactor(fourthg));
            rightchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), fourthf, fourthq, dBtoGainFactor(fourthg));
        }
        if (*treestate.getRawParameterValue("fourth filter type") == 1.0)
        {
            leftchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), fourthf, thirdq, dBtoGainFactor(fourthg));
            rightchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), fourthf, thirdq, dBtoGainFactor(fourthg));
        }
        if (*treestate.getRawParameterValue("fourth filter type") == 2.0)
        {
            leftchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), fourthf, fourthq, dBtoGainFactor(fourthg));
            rightchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), fourthf, fourthq, dBtoGainFactor(fourthg));
        }
        if (*treestate.getRawParameterValue("fourth filter type") == 3.0)
        {
            leftchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), fourthf, fourthq);
            rightchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), fourthf, fourthq);
        }
        if (*treestate.getRawParameterValue("fourth filter type") == 4.0)
        {
            leftchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), fourthf, fourthq);
            rightchain.get<f1Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), fourthf, fourthq);
        }
    }

    if (*treestate.getRawParameterValue("fifth bypass") == 1.0)
    {
        leftchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("fifth filter type") == 0.0)
        {
            leftchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), fifthf, fifthq, dBtoGainFactor(fifthg));
            rightchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), fifthf, fifthq, dBtoGainFactor(fifthg));
        }
        if (*treestate.getRawParameterValue("fifth filter type") == 1.0)
        {
            leftchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), fifthf, fifthq, dBtoGainFactor(fifthg));
            rightchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), fifthf, fifthq, dBtoGainFactor(fifthg));
        }
        if (*treestate.getRawParameterValue("fifth filter type") == 2.0)
        {
            leftchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), fifthf, fifthq, dBtoGainFactor(fifthg));
            rightchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), fifthf, fifthq, dBtoGainFactor(fifthg));
        }
        if (*treestate.getRawParameterValue("fifth filter type") == 3.0)
        {
            leftchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), fifthf, fifthq);
            rightchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), fifthf, fifthq);
        }
        if (*treestate.getRawParameterValue("fifth filter type") == 4.0)
        {
            leftchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), fifthf, fifthq);
            rightchain.get<f2Index>().get<f1>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), fifthf, fifthq);
        }
    }

    if (*treestate.getRawParameterValue("sixth bypass") == 1.0)
    {
        leftchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f1Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("sixth filter type") == 4.0)
        {
            leftchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), sixthf, sixthq);
            rightchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), sixthf, sixthq);
        }
        if (*treestate.getRawParameterValue("sixth filter type") == 3.0)
        {
            leftchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), sixthf, sixthq);
            rightchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), sixthf, sixthq);
        }
        if (*treestate.getRawParameterValue("sixth filter type") == 2.0)
        {
            leftchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), sixthf, sixthq, dBtoGainFactor(sixthg));
            rightchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), sixthf, sixthq, dBtoGainFactor(sixthg));
        }
        if (*treestate.getRawParameterValue("sixth filter type") == 1.0)
        {
            leftchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), sixthf, sixthq, dBtoGainFactor(sixthg));
            rightchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), sixthf, sixthq, dBtoGainFactor(sixthg));
        }
        if (*treestate.getRawParameterValue("sixth filter type") == 0.0)
        {
            leftchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), sixthf, sixthq, dBtoGainFactor(sixthg));
            rightchain.get<f2Index>().get<f2>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), sixthf, sixthq, dBtoGainFactor(sixthg));
        }
    }

    if (*treestate.getRawParameterValue("seventh bypass") == 1.0)
    {
        leftchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("seventh filter type") == 0.0)
        {
            leftchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), seventhf, seventhq);
            rightchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), seventhf, seventhq);
        }
        if (*treestate.getRawParameterValue("seventh filter type") == 1.0)
        {
            leftchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), seventhf, seventhq, dBtoGainFactor(seventhg));
            rightchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), seventhf, seventhq, dBtoGainFactor(seventhg));
        }
        if (*treestate.getRawParameterValue("seventh filter type") == 2.0)
        {
            leftchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), seventhf, seventhq, dBtoGainFactor(seventhg));
            rightchain.get<f2Index>().get<f3>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), seventhf, seventhq, dBtoGainFactor(seventhg));
        }
    }

    if (*treestate.getRawParameterValue("eighth bypass") == 1.0)
    {
        leftchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
        rightchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(getSampleRate(), 20000.0);
    }
    else
    {
        if (*treestate.getRawParameterValue("eighth filter type") == 0.0)
        {
            leftchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), eighthf, eighthq);
            rightchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), eighthf, eighthq);
        }
        if (*treestate.getRawParameterValue("eighth filter type") == 1.0)
        {
            leftchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), eighthf, eighthq, dBtoGainFactor(eighthg));
            rightchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), eighthf, eighthq, dBtoGainFactor(eighthg));
        }
        if (*treestate.getRawParameterValue("eighth filter type") == 2.0)
        {
            leftchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), eighthf, eighthq, dBtoGainFactor(eighthg));
            rightchain.get<f2Index>().get<f4>().coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), eighthf, eighthq, dBtoGainFactor(eighthg));
        }
    }

    //output gain connected
    leftchain.get<outgainIndex>().setGainDecibels(*treestate.getRawParameterValue("output gain"));
    rightchain.get<outgainIndex>().setGainDecibels(*treestate.getRawParameterValue("output gain"));
    leftchain.get<outgainIndex>().setRampDurationSeconds(0.25);
    rightchain.get<outgainIndex>().setRampDurationSeconds(0.25);
}
void EQChainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // audio block
    juce::dsp::AudioBlock<float> block(buffer);

    updateChain();
    
    //splitting block into left and right
    auto leftblock = block.getSingleChannelBlock(0);
    auto rightblock = block.getSingleChannelBlock(1);

    //wrapping blocks into context
    juce::dsp::ProcessContextReplacing<float> leftContext(leftblock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightblock);

    //process the context
    leftchain.process(leftContext);
    rightchain.process(rightContext);
}

//==============================================================================
bool EQChainAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EQChainAudioProcessor::createEditor()
{
    return new EQChainAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void EQChainAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream stream(destData, false);
    treestate.state.writeToStream(stream);
}

void EQChainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));

    if (tree.isValid())
    {
        treestate.state = tree;
        ingain = *treestate.getRawParameterValue("input gain");
        firstbypass = *treestate.getRawParameterValue("first bypass");
        firstfiltertype = *treestate.getRawParameterValue("first filter type");
        firstf = *treestate.getRawParameterValue("first freq");
        firstg = *treestate.getRawParameterValue("first gain");
        firstq = *treestate.getRawParameterValue("first q");
        secondbypass = *treestate.getRawParameterValue("second bypass");
        secondfiltertype = *treestate.getRawParameterValue("second filter type");
        secondf = *treestate.getRawParameterValue("second freq");
        secondg = *treestate.getRawParameterValue("second gain");
        secondq = *treestate.getRawParameterValue("second q");
        thirdbypass = *treestate.getRawParameterValue("third bypass");
        thirdfiltertype = *treestate.getRawParameterValue("third filter type");
        thirdf = *treestate.getRawParameterValue("third freq");
        thirdg = *treestate.getRawParameterValue("third gain");
        thirdq = *treestate.getRawParameterValue("third q");
        fourthbypass = *treestate.getRawParameterValue("fourth bypass");
        fourthfiltertype = *treestate.getRawParameterValue("fourth filter type");
        fourthf = *treestate.getRawParameterValue("fourth freq");
        fourthg = *treestate.getRawParameterValue("fourth gain");
        fourthq = *treestate.getRawParameterValue("fourth q");

        fifthbypass = *treestate.getRawParameterValue("fifth bypass");
        fifthfiltertype = *treestate.getRawParameterValue("fifth filter type");
        fifthf = *treestate.getRawParameterValue("fifth freq");
        fifthg = *treestate.getRawParameterValue("fifth gain");
        fifthq = *treestate.getRawParameterValue("fifth q");
        sixthbypass = *treestate.getRawParameterValue("sixth bypass");
        sixthfiltertype = *treestate.getRawParameterValue("sixth filter type");
        sixthf = *treestate.getRawParameterValue("sixth freq");
        sixthg = *treestate.getRawParameterValue("sixth gain");
        sixthq = *treestate.getRawParameterValue("sixth q");
        seventhbypass = *treestate.getRawParameterValue("seventh bypass");
        seventhfiltertype = *treestate.getRawParameterValue("seventh filter type");
        seventhf = *treestate.getRawParameterValue("seventh freq");
        seventhg = *treestate.getRawParameterValue("seventh gain");
        seventhq = *treestate.getRawParameterValue("seventh q");
        eighthbypass = *treestate.getRawParameterValue("eighth bypass");
        eighthfiltertype = *treestate.getRawParameterValue("eighth filter type");
        eighthf = *treestate.getRawParameterValue("eighth freq");
        eighthg = *treestate.getRawParameterValue("eighth gain");
        eighthq = *treestate.getRawParameterValue("eighth q");
        outgain = *treestate.getRawParameterValue("output gain");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQChainAudioProcessor();
}
