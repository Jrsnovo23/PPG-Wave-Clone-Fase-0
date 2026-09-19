#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Params/ParameterLayout.h"
#include "Params/ParameterIDs.h"

namespace
{
    constexpr int numVoicesPhase1 = 8; // la polifonía configurable real llega en Fase 3/10
}

PPGWaveCloneAudioProcessor::PPGWaveCloneAudioProcessor()
    : AudioProcessor (BusesProperties()
                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMETERS", ParameterLayout::createParameterLayout())
{
    for (int i = 0; i < numVoicesPhase1; ++i)
        synth.addVoice (new PlaceholderSineVoice());

    synth.addSound (new SynthSound());
}

void PPGWaveCloneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    juce::ignoreUnused (samplesPerBlock);
}

bool PPGWaveCloneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void PPGWaveCloneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                                juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());

    // Ganancia maestra (Fase 1). El smoothing por bloque completo es aceptable
    // aquí porque es un único parámetro global de salida; los parámetros por
    // voz (Fases 2+) usarán juce::SmoothedValue por muestra dentro del DSP.
    const float volumeDb = apvts.getRawParameterValue (ParamIDs::masterVolume)->load();
    buffer.applyGain (juce::Decibels::decibelsToGain (volumeDb));
}

juce::AudioProcessorEditor* PPGWaveCloneAudioProcessor::createEditor()
{
    return new PPGWaveCloneAudioProcessorEditor (*this);
}

void PPGWaveCloneAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void PPGWaveCloneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

// Este método lo requiere JUCE para instanciar el plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PPGWaveCloneAudioProcessor();
}
