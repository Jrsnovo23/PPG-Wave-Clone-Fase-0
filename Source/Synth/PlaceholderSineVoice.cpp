#include "PlaceholderSineVoice.h"

void PlaceholderSineVoice::startNote (int midiNoteNumber, float velocity,
                                       juce::SynthesiserSound*, int /*pitchWheel*/)
{
    level = velocity;
    const double freq = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    const double cyclesPerSample = freq / getSampleRate();
    angleDelta = cyclesPerSample * juce::MathConstants<double>::twoPi;
    currentAngle = 0.0;

    gain = 0.0f;
    gainTarget = level;
    isReleasing = false;
    gainStep = gainTarget / (float) (rampSeconds * getSampleRate());
}

void PlaceholderSineVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        isReleasing = true;
        gainTarget = 0.0f;
        gainStep = gain / (float) (rampSeconds * getSampleRate());
    }
    else
    {
        clearCurrentNote();
        angleDelta = 0.0;
        gain = 0.0f;
    }
}

void PlaceholderSineVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                                             int startSample, int numSamples)
{
    if (angleDelta == 0.0)
        return;

    while (--numSamples >= 0)
    {
        // Rampa de ganancia (anti-click, no es la Envelope final del diseño)
        if (gain < gainTarget)      gain = juce::jmin (gainTarget, gain + gainStep);
        else if (gain > gainTarget) gain = juce::jmax (gainTarget, gain - gainStep);

        const float sample = (float) std::sin (currentAngle) * gain;

        for (int ch = 0; ch < outputBuffer.getNumChannels(); ++ch)
            outputBuffer.addSample (ch, startSample, sample);

        currentAngle += angleDelta;
        ++startSample;

        if (isReleasing && gain <= 0.0001f)
        {
            clearCurrentNote();
            angleDelta = 0.0;
            gain = 0.0f;
            break;
        }
    }
}
