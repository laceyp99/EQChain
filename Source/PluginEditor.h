/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    {
    }
};

struct CustomVerticalSlider : juce::Slider
{
    CustomVerticalSlider() : juce::Slider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    {
    }
};

//==============================================================================
/**
*/
class EQChainAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EQChainAudioProcessorEditor (EQChainAudioProcessor&);
    ~EQChainAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void comboboxfix();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQChainAudioProcessor& audioProcessor;

    //vertical fader
    CustomVerticalSlider f1gSlider, f2gSlider, f3gSlider, f4gSlider, f5gSlider, f6gSlider, f7gSlider, f8gSlider;

    //rotary knob
    CustomRotarySlider f1fKnob, f2fKnob, f3fKnob, f4fKnob, f5fKnob, f6fKnob, f7fKnob, f8fKnob,
        f1qKnob, f2qKnob, f3qKnob, f4qKnob, f5qKnob, f6qKnob, f7qKnob, f8qKnob,
        outgainKnob;

    // drop down menus
    juce::ComboBox f1typeMenu, f2typeMenu, f3typeMenu, f4typeMenu, f5typeMenu, f6typeMenu, f7typeMenu, f8typeMenu;

    //bypass buttons
    juce::ToggleButton f1Toggle, f2Toggle, f3Toggle, f4Toggle, f5Toggle, f6Toggle, f7Toggle, f8Toggle;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    using ToggleAttachment = APVTS::ButtonAttachment;
    using MenuAttachment = APVTS::ComboBoxAttachment;
    using Border = juce::GroupComponent;

    // building attachments to audio processor
    Attachment f1gSliderAttachment, f1fKnobAttachment, f1qKnobAttachment, f2gSliderAttachment, f2fKnobAttachment, f2qKnobAttachment, 
        f3gSliderAttachment, f3fKnobAttachment, f3qKnobAttachment, f4gSliderAttachment, f4fKnobAttachment, f4qKnobAttachment,
        f5gSliderAttachment, f5fKnobAttachment, f5qKnobAttachment, f6gSliderAttachment, f6fKnobAttachment, f6qKnobAttachment, 
        f7gSliderAttachment, f7fKnobAttachment, f7qKnobAttachment, f8gSliderAttachment, f8fKnobAttachment, f8qKnobAttachment,
        outgainKnobAttachment;
    ToggleAttachment f1ToggleAttachment, f2ToggleAttachment, f3ToggleAttachment, f4ToggleAttachment, 
        f5ToggleAttachment, f6ToggleAttachment, f7ToggleAttachment, f8ToggleAttachment;
    
    Border gainBorder, freqBorder, qBorder, outgainBorder;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> f1MenuAttachment, f2MenuAttachment, f3MenuAttachment, f4MenuAttachment, 
        f5MenuAttachment, f6MenuAttachment, f7MenuAttachment, f8MenuAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQChainAudioProcessorEditor)
};
