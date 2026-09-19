# PPG Wave Clone — Fase 1: Arquitectura

Implementación original de un instrumento virtual VST3 de síntesis wavetable
inspirado conceptualmente en el PPG Wave 3.3. No contiene ROMs, muestras,
gráficos ni código propietario de terceros.

## Estado de esta entrega

Esta es **únicamente la Fase 1** del plan (ver sección "Fases" abajo).
Objetivo cumplido: un VST3 que compila, carga en Ableton Live, recibe MIDI y
produce audio (un seno simple por voz, con una rampa anti-click), con un solo
parámetro real (Master Volume) expuesto vía `AudioProcessorValueTreeState` y
automatizable desde el host.

**Lo que NO incluye todavía** (llega en fases siguientes, no está fingido):
osciladores wavetable, filtro, envolventes ADSR reales, LFO, matriz de
modulación, efectos, gestión de presets, carácter "vintage" y la interfaz
gráfica definitiva.

## Compilación sin instalar nada (recomendado si no usas Terminal/Xcode)

Este proyecto incluye `.github/workflows/build.yml`, que compila el VST3 en
un Mac con Xcode ya instalado, en la nube, gratis, vía GitHub Actions. Ver
la conversación / instrucciones paso a paso para subir el proyecto a GitHub
y descargar el `.vst3` ya compilado desde la pestaña "Actions".

## Compilación local (requiere Xcode + CMake)

Requiere CMake ≥ 3.22 y un compilador C++20 (Visual Studio 2022 en Windows).

1. Clona JUCE dentro de esta carpeta:
   ```
   git clone --depth 1 --branch 7.0.12 https://github.com/juce-framework/JUCE.git
   ```
   Debe quedar como `PPGWaveClone/JUCE/`.

2. Configura y compila (desde la carpeta `PPGWaveClone/`):
   ```
   cmake -B build -G "Visual Studio 17 2022"
   cmake --build build --config Release
   ```

3. El VST3 resultante queda en:
   ```
   build/PPGWaveClone_artefacts/Release/VST3/PPG Wave Clone.vst3
   ```
   Cópialo a:
   ```
   C:\Program Files\Common Files\VST3\
   ```
   y vuelve a escanear plugins en Ableton Live (Preferencias → Plug-ins).

> Nota: no pude compilar ni probar este proyecto en este entorno (sandbox sin
> acceso a red para descargar JUCE), así que la verificación real en Ableton
> Live la tienes que hacer tú siguiendo estos pasos. Si algo no compila,
> pégame el error exacto y lo corregimos.

## Estructura

```
PPGWaveClone/
  CMakeLists.txt
  Source/
    PluginProcessor.h/.cpp   — AudioProcessor, APVTS, Synthesiser
    PluginEditor.h/.cpp      — GUI mínima (Fase 1)
    Params/
      ParameterIDs.h          — IDs estables de parámetros
      ParameterLayout.h/.cpp  — creación del árbol de parámetros
    Synth/
      SynthSound.h            — sonido comodín para juce::Synthesiser
      PlaceholderSineVoice.h/.cpp — voz temporal (seno), sustituida en Fase 2-3
```

## Próxima fase (Fase 2 — Oscilador Wavetable)

- `Source/DSP/Wavetable.h/.cpp`: motor de tablas de onda + interpolación.
- `Source/DSP/Oscillator.h/.cpp`: oscilador con selección de tabla, posición,
  tune, y modulación de posición.
- `Source/Synth/SynthVoice.h/.cpp`: sustituye a `PlaceholderSineVoice`,
  combinando OSC1 + OSC2.
- Ampliar `ParameterIDs.h` / `ParameterLayout.cpp` con los parámetros de
  ambos osciladores.

Dime cuándo avanzamos a la Fase 2 y seguimos desde aquí.
