#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

/**
    ------------------------------------------------------------------------
    PLACEHOLDER — Fase 1 únicamente.
    ------------------------------------------------------------------------
    Esta voz existe solo para verificar, de punta a punta, que el plugin
    carga en Ableton Live, recibe MIDI y produce audio: un seno simple con
    una envolvente de amplitud lineal (attack/release cortos para evitar
    clicks). NO es el motor de síntesis final.

    En la Fase 2 esta clase se sustituye por Synth/SynthVoice, que contendrá
    los dos osciladores wavetable, y en la Fase 3 se le añaden filtro y las
    envolventes ADSR reales descritas en el diseño. Se deja aquí, comentado,
    para que quien retome el proyecto entienda por qué el archivo es
    deliberadamente mínimo.
*/
class PlaceholderSineVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound*) override { return true; }

    void startNote (int midiNoteNumber, float velocity,
                     juce::SynthesiserSound*, int /*pitchWheel*/) override;

    void stopNote (float /*velocity*/, bool allowTailOff) override;

    void pitchWheelMoved (int) override {}
    void controllerMoved (int, int) override {}

    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                           int startSample, int numSamples) override;

private:
    double currentAngle = 0.0;
    double angleDelta   = 0.0;
    float  level        = 0.0f;

    // Envolvente lineal simple, solo para evitar clicks (no es Envelope real)
    float  gain          = 0.0f;
    float  gainTarget     = 0.0f;
    float  gainStep       = 0.0f;
    bool   isReleasing    = false;

    static constexpr float rampSeconds = 0.01f;
};
