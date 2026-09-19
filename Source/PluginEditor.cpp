#include "PluginEditor.h"
#include "Params/ParameterIDs.h"

PPGWaveCloneAudioProcessorEditor::PPGWaveCloneAudioProcessorEditor (PPGWaveCloneAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    titleLabel.setText ("PPG WAVE CLONE — Fase 1", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setFont (juce::Font (20.0f, juce::Font::bold));
    addAndMakeVisible (titleLabel);

    masterVolumeSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    masterVolumeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible (masterVolumeSlider);

    masterVolumeLabel.setText ("Master Volume", juce::dontSendNotification);
    masterVolumeLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (masterVolumeLabel);

    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        processorRef.apvts, ParamIDs::masterVolume, masterVolumeSlider);

    setSize (420, 260);
}

void PPGWaveCloneAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff1a1a1f));
}

void PPGWaveCloneAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (16);
    titleLabel.setBounds (area.removeFromTop (32));
    area.removeFromTop (16);

    auto knobArea = area.removeFromTop (140);
    masterVolumeSlider.setBounds (knobArea.withSizeKeepingCentre (120, 120));
    masterVolumeLabel.setBounds (area.removeFromTop (24));
}
