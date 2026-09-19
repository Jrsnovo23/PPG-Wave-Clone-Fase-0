#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

/**
    Editor mínimo de Fase 1: solo confirma que el plugin abre correctamente
    su interfaz dentro del host y expone el único parámetro existente
    (Master Volume). La interfaz visual definitiva, inspirada en el estilo
    del hardware original con recursos gráficos propios, se construye en la
    Fase 7 sobre esta misma clase.
*/
class PPGWaveCloneAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PPGWaveCloneAudioProcessorEditor (PPGWaveCloneAudioProcessor&);
    ~PPGWaveCloneAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PPGWaveCloneAudioProcessor& processorRef;

    juce::Label titleLabel;
    juce::Slider masterVolumeSlider;
    juce::Label  masterVolumeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PPGWaveCloneAudioProcessorEditor)
};
