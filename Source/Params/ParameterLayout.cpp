#include "ParameterLayout.h"
#include "ParameterIDs.h"

juce::AudioProcessorValueTreeState::ParameterLayout ParameterLayout::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // --- Master (Fase 1) ----------------------------------------------
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { ParamIDs::masterVolume, 1 },
        "Master Volume",
        juce::NormalisableRange<float> { -60.0f, 6.0f, 0.01f },
        -6.0f,
        juce::AudioParameterFloatAttributes()
            .withLabel("dB")
            .withStringFromValueFunction([](float v, int) { return juce::String(v, 1) + " dB"; })
    ));

    // --- Fases futuras --------------------------------------------------
    // Fase 2: Oscillator 1 / Oscillator 2 (wavetable, wave position, tune...)
    // Fase 3: Filter, Envelope 1 (amp), Envelope 2 (filter/mod)
    // Fase 4: LFO 1/2, Modulation Matrix
    // Fase 5: Chorus, Delay, Reverb, Drive
    // Fase 8: Vintage Character (bit depth, drift, aliasing...)

    return { params.begin(), params.end() };
}
