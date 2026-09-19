#pragma once

#include <juce_core/juce_core.h>

/**
    IDs de parámetros del plugin.

    IMPORTANTE: una vez publicado un preset o proyecto de Ableton Live que use
    un ID, ese ID no debe cambiar de nombre — Ableton Live guarda automatizaciones
    y estado del plugin referenciando estos strings. Nuevos parámetros de fases
    futuras se agregan aquí, nunca se renombran los existentes.

    Fase 1: únicamente el volumen maestro. El resto de los parámetros descritos
    en el documento de diseño (osciladores, filtro, envolventes, LFO, matriz de
    modulación, efectos, vintage character...) se añadirán en las fases 2-8,
    cada uno en su propio bloque dentro de este archivo.
*/
namespace ParamIDs
{
    static const juce::String masterVolume { "masterVolume" };
}
