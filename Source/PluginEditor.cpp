/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQChainAudioProcessorEditor::EQChainAudioProcessorEditor(EQChainAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), f1gSlider(), f1Toggle(), f1typeMenu(), f1fKnob(), f1qKnob(),
    f1gSliderAttachment(audioProcessor.treestate, "first gain", f1gSlider),
    f1ToggleAttachment(audioProcessor.treestate, "first bypass", f1Toggle),
    f1fKnobAttachment(audioProcessor.treestate, "first freq", f1fKnob),
    f1qKnobAttachment(audioProcessor.treestate, "first q", f1qKnob),
    f2gSliderAttachment(audioProcessor.treestate, "second gain", f2gSlider),
    f2ToggleAttachment(audioProcessor.treestate, "second bypass", f2Toggle),
    f2fKnobAttachment(audioProcessor.treestate, "second freq", f2fKnob),
    f2qKnobAttachment(audioProcessor.treestate, "second q", f2qKnob),
    f3gSliderAttachment(audioProcessor.treestate, "third gain", f3gSlider),
    f3ToggleAttachment(audioProcessor.treestate, "third bypass", f3Toggle),
    f3fKnobAttachment(audioProcessor.treestate, "third freq", f3fKnob),
    f3qKnobAttachment(audioProcessor.treestate, "third q", f3qKnob),
    f4gSliderAttachment(audioProcessor.treestate, "fourth gain", f4gSlider),
    f4ToggleAttachment(audioProcessor.treestate, "fourth bypass", f4Toggle),
    f4fKnobAttachment(audioProcessor.treestate, "fourth freq", f4fKnob),
    f4qKnobAttachment(audioProcessor.treestate, "fourth q", f4qKnob),
    f5gSliderAttachment(audioProcessor.treestate, "fifth gain", f5gSlider),
    f5ToggleAttachment(audioProcessor.treestate, "fifth bypass", f5Toggle),
    f5fKnobAttachment(audioProcessor.treestate, "fifth freq", f5fKnob),
    f5qKnobAttachment(audioProcessor.treestate, "fifth q", f5qKnob),
    f6gSliderAttachment(audioProcessor.treestate, "sixth gain", f6gSlider),
    f6ToggleAttachment(audioProcessor.treestate, "sixth bypass", f6Toggle),
    f6fKnobAttachment(audioProcessor.treestate, "sixth freq", f6fKnob),
    f6qKnobAttachment(audioProcessor.treestate, "sixth q", f6qKnob),
    f7gSliderAttachment(audioProcessor.treestate, "seventh gain", f7gSlider),
    f7ToggleAttachment(audioProcessor.treestate, "seventh bypass", f7Toggle),
    f7fKnobAttachment(audioProcessor.treestate, "seventh freq", f7fKnob),
    f7qKnobAttachment(audioProcessor.treestate, "seventh q", f7qKnob),
    f8gSliderAttachment(audioProcessor.treestate, "eighth gain", f8gSlider),
    f8ToggleAttachment(audioProcessor.treestate, "eighth bypass", f8Toggle),
    f8fKnobAttachment(audioProcessor.treestate, "eighth freq", f8fKnob),
    f8qKnobAttachment(audioProcessor.treestate, "eighth q", f8qKnob),
    outgainKnobAttachment(audioProcessor.treestate, "output gain", outgainKnob)
    
{
    //gain fader
    addAndMakeVisible(f1gSlider);
    f1gSlider.setTextValueSuffix(" dB");

    //bypass button
    addAndMakeVisible(f1Toggle);
    f1Toggle.changeWidthToFitText();
    f1Toggle.setButtonText("Bypass");

    //filter type menu
    addAndMakeVisible(f1typeMenu);
    f1typeMenu.addItem("Low Cut", 1);
    f1typeMenu.addItem("Low Shelf", 2);
    f1typeMenu.addItem("Peak", 3);
    f1typeMenu.setSelectedId(1);
    f1MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "first filter type", f1typeMenu);

    //freq and q knobs
    addAndMakeVisible(f1fKnob);
    f1fKnob.setTextValueSuffix(" Hz");
    // range inherited from attachment
    addAndMakeVisible(f1qKnob);
    // no suffix needed its a Q value, also range inherited from attachment

    // repeated 2-8 
    addAndMakeVisible(f2gSlider);
    f2gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f2Toggle);
    f2Toggle.changeWidthToFitText();
    f2Toggle.setButtonText("Bypass");
    addAndMakeVisible(f2typeMenu);
    f2typeMenu.addItem("Low Cut", 1);
    f2typeMenu.addItem("Low Shelf", 2);
    f2typeMenu.addItem("Peak", 3);
    f2typeMenu.setSelectedId(1);
    f2MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "second filter type", f2typeMenu);
    addAndMakeVisible(f2fKnob);
    f2fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f2qKnob);

    addAndMakeVisible(f3gSlider);
    f3gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f3Toggle);
    f3Toggle.changeWidthToFitText();
    f3Toggle.setButtonText("Bypass");
    addAndMakeVisible(f3typeMenu);
    f3typeMenu.addItem("Peak", 1);
    f3typeMenu.addItem("Low Shelf", 2);
    f3typeMenu.addItem("High Shelf", 3);
    f3typeMenu.addItem("Low Cut", 4);
    f3typeMenu.addItem("High Cut", 5);
    f3typeMenu.setSelectedId(1);
    f3MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "third filter type", f3typeMenu);
    addAndMakeVisible(f3fKnob);
    f3fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f3qKnob);

    addAndMakeVisible(f4gSlider);
    f4gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f4Toggle);
    f4Toggle.changeWidthToFitText();
    f4Toggle.setButtonText("Bypass");
    addAndMakeVisible(f4typeMenu);
    f4typeMenu.addItem("Peak", 1);
    f4typeMenu.addItem("Low Shelf", 2);
    f4typeMenu.addItem("High Shelf", 3);
    f4typeMenu.addItem("Low Cut", 4);
    f4typeMenu.addItem("High Cut", 5);
    f4typeMenu.setSelectedId(1);
    f4MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "fourth filter type", f4typeMenu);
    addAndMakeVisible(f4fKnob);
    f4fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f4qKnob);
    
    addAndMakeVisible(f5gSlider);
    f5gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f5Toggle);
    f5Toggle.changeWidthToFitText();
    f5Toggle.setButtonText("Bypass");
    addAndMakeVisible(f5typeMenu);
    f5typeMenu.addItem("Peak", 1);
    f5typeMenu.addItem("High Shelf", 2);
    f5typeMenu.addItem("Low Shelf", 3);
    f5typeMenu.addItem("High Cut", 4);
    f5typeMenu.addItem("Low Cut", 5);
    f5typeMenu.setSelectedId(1);
    f5MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "fifth filter type", f5typeMenu);
    addAndMakeVisible(f5fKnob);
    f5fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f5qKnob);

    addAndMakeVisible(f6gSlider);
    f6gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f6Toggle);
    f6Toggle.changeWidthToFitText();
    f6Toggle.setButtonText("Bypass");
    addAndMakeVisible(f6typeMenu);
    f6typeMenu.addItem("Peak", 1);
    f6typeMenu.addItem("High Shelf", 2);
    f6typeMenu.addItem("Low Shelf", 3);
    f6typeMenu.addItem("High Cut", 4);
    f6typeMenu.addItem("Low Cut", 5);
    f6typeMenu.setSelectedId(1);
    f6MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "sixth filter type", f6typeMenu);
    addAndMakeVisible(f6fKnob);
    f6fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f6qKnob);

    addAndMakeVisible(f7gSlider);
    f7gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f7Toggle);
    f7Toggle.changeWidthToFitText();
    f7Toggle.setButtonText("Bypass");
    addAndMakeVisible(f7typeMenu);
    f7typeMenu.addItem("High Cut", 1);
    f7typeMenu.addItem("High Shelf", 2); 
    f7typeMenu.addItem("Peak", 3);
    f7typeMenu.setSelectedId(1);
    f7MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "seventh filter type", f7typeMenu);
    addAndMakeVisible(f7fKnob);
    f7fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f7qKnob); 
    
    addAndMakeVisible(f8gSlider);
    f8gSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(f8Toggle);
    f8Toggle.changeWidthToFitText();
    f8Toggle.setButtonText("Bypass");
    addAndMakeVisible(f8typeMenu);
    f8typeMenu.addItem("High Cut", 1);
    f8typeMenu.addItem("High Shelf", 2);
    f8typeMenu.addItem("Peak", 3);
    f8typeMenu.setSelectedId(1);
    f8MenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treestate, "eighth filter type", f8typeMenu);
    addAndMakeVisible(f8fKnob);
    f8fKnob.setTextValueSuffix(" Hz");
    addAndMakeVisible(f8qKnob);

    //out gain knob
    addAndMakeVisible(outgainKnob);
    outgainKnob.setTextValueSuffix(" dB");

    //borders
    addAndMakeVisible(gainBorder);
    gainBorder.setText("Gain");
    addAndMakeVisible(freqBorder);
    freqBorder.setText("Frequency");
    addAndMakeVisible(qBorder);
    qBorder.setText("Quality");
    addAndMakeVisible(outgainBorder);
    outgainBorder.setText("Output Gain");

    // resizing
    setResizable(true, true);
    setResizeLimits(500, 375, 1200, 900);
    getConstrainer()->setFixedAspectRatio(2.0);
    setSize (800, 600);
}

EQChainAudioProcessorEditor::~EQChainAudioProcessorEditor()
{
}

//==============================================================================
void EQChainAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
   // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EQChainAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();
    auto knobArea = bounds.removeFromBottom(bounds.getHeight() * 0.5);

    int eqlanewidth = bounds.getWidth() * 0.1;

    f1gSlider.setBounds(bounds.getX() + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f1Toggle.setBounds(f1gSlider.getWidth() * 0.25, bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f1typeMenu.setBounds(knobArea.getX(), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f1fKnob.setBounds(knobArea.getX() + (eqlanewidth * 0.05), knobArea.getY() + f1typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f1qKnob.setBounds(knobArea.getX() + (eqlanewidth * 0.05), f1fKnob.getY() + f1fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);

    f2gSlider.setBounds(eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f2Toggle.setBounds((f2gSlider.getWidth() * 0.25) + eqlanewidth, bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f2typeMenu.setBounds(knobArea.getX() + eqlanewidth, knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f2fKnob.setBounds(knobArea.getX() + eqlanewidth + (eqlanewidth * 0.05), knobArea.getY() + f2typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8 , knobArea.getHeight() * 0.35);
    f2qKnob.setBounds(knobArea.getX() + eqlanewidth + (eqlanewidth * 0.05), f2fKnob.getY() + f2fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);

    f3gSlider.setBounds(2 * eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f3Toggle.setBounds((f3gSlider.getWidth() * 0.25) + (2*eqlanewidth), bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f3typeMenu.setBounds(knobArea.getX() + (2 * eqlanewidth), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f3fKnob.setBounds(knobArea.getX() + (2 * eqlanewidth) + (eqlanewidth * 0.05), knobArea.getY() + f3typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f3qKnob.setBounds(knobArea.getX() + (2 * eqlanewidth) + (eqlanewidth * 0.05), f3fKnob.getY() + f3fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    
    f4gSlider.setBounds(3 * eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f4Toggle.setBounds((f4gSlider.getWidth() * 0.25) + (3 * eqlanewidth), bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f4typeMenu.setBounds(knobArea.getX() + (3 * eqlanewidth), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f4fKnob.setBounds(knobArea.getX() + (3 * eqlanewidth) + (eqlanewidth * 0.05), knobArea.getY() + f4typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f4qKnob.setBounds(knobArea.getX() + (3 * eqlanewidth) + (eqlanewidth * 0.05), f4fKnob.getY() + f4fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    
    f5gSlider.setBounds(4 * eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f5Toggle.setBounds(f5gSlider.getWidth() * 0.25 + (4 * eqlanewidth), bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f5typeMenu.setBounds(knobArea.getX() + (4 * eqlanewidth), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f5fKnob.setBounds(knobArea.getX() + (4 * eqlanewidth) + (eqlanewidth * 0.05), knobArea.getY() + f5typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f5qKnob.setBounds(knobArea.getX() + (4 * eqlanewidth) + (eqlanewidth * 0.05), f5fKnob.getY() + f5fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);

    f6gSlider.setBounds(5 * eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f6Toggle.setBounds((f6gSlider.getWidth() * 0.25) + (5* eqlanewidth), bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f6typeMenu.setBounds(knobArea.getX() + (5 * eqlanewidth), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f6fKnob.setBounds(knobArea.getX() + (5 * eqlanewidth) + (eqlanewidth * 0.05), knobArea.getY() + f6typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f6qKnob.setBounds(knobArea.getX() + (5 * eqlanewidth) + (eqlanewidth * 0.05), f6fKnob.getY() + f6fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);

    f7gSlider.setBounds(6 * eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f7Toggle.setBounds((f7gSlider.getWidth() * 0.25) + (6*eqlanewidth), bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f7typeMenu.setBounds(knobArea.getX() + (6 * eqlanewidth), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f7fKnob.setBounds(knobArea.getX() + (6 * eqlanewidth) + (eqlanewidth * 0.05), knobArea.getY() + f7typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f7qKnob.setBounds(knobArea.getX() + (6 * eqlanewidth) + (eqlanewidth * 0.05), f7fKnob.getY() + f7fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    
    f8gSlider.setBounds(7 * eqlanewidth + (eqlanewidth * 0.1), bounds.getY() + (bounds.getHeight() * 0.05), eqlanewidth * 0.8, bounds.getHeight() * 0.8);
    f8Toggle.setBounds((f8gSlider.getWidth() * 0.25) + (7 * eqlanewidth), bounds.getHeight() * 0.9, eqlanewidth, bounds.getHeight() * 0.1);
    f8typeMenu.setBounds(knobArea.getX() + (7 * eqlanewidth), knobArea.getY(), eqlanewidth, knobArea.getHeight() * 0.1);
    f8fKnob.setBounds(knobArea.getX() + (7 * eqlanewidth) + (eqlanewidth * 0.05), knobArea.getY() + f8typeMenu.getHeight() + (knobArea.getHeight() * 0.05), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);
    f8qKnob.setBounds(knobArea.getX() + (7 * eqlanewidth) + (eqlanewidth * 0.05), f8fKnob.getY() + f8fKnob.getHeight() + (knobArea.getHeight() * 0.1), eqlanewidth * 0.8, knobArea.getHeight() * 0.35);

    outgainKnob.setBounds(8 * eqlanewidth, knobArea.getY() + (knobArea.getHeight() * 0.05), eqlanewidth * 2, knobArea.getHeight() * 0.9);

    gainBorder.setBounds(bounds.getX(), bounds.getY(), 8*eqlanewidth, bounds.getHeight() * 0.9);
    freqBorder.setBounds(knobArea.getX(), knobArea.getY() + (knobArea.getHeight() * 0.1), 8 * eqlanewidth, knobArea.getHeight() * 0.45);
    qBorder.setBounds(knobArea.getX(), freqBorder.getY() + freqBorder.getHeight(), 8 * eqlanewidth, knobArea.getHeight() * 0.45);
    outgainBorder.setBounds(eqlanewidth * 8, knobArea.getY(), 2 * eqlanewidth, knobArea.getHeight());
}

