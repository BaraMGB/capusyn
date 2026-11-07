# Architektur

**Status:** Gliederung; Fachkapitel noch auszuarbeiten.

## Geplante Kapitel

- `system-overview.md`: Produktvarianten VST3, Standalone und Headless sowie deren gemeinsame Basis.
- `modules-and-dependencies.md`: Verantwortlichkeiten, Abhängigkeiten und Grenzen der Quellcodebereiche.
- `signal-and-data-flow.md`: Audio-, MIDI-, Parameter- und Zustandsfluss zwischen den Modulen.
- `threading-and-lifecycle.md`: Audio-, Message- und Rendering-Threads, Ownership, Synchronisation und Plugin-Abbau.

## Einstieg in den Code

- [Gemeinsame Synthesizer-Basis](../../src/common/synth_base.h)
- [Audio-Engine](../../src/synthesis/synth_engine/)
- [Plugin](../../src/plugin/), [Standalone](../../src/standalone/), [Headless](../../src/headless/)
- [Target-Struktur](../../CMakeLists.txt) und [Unity-Build-Einheiten](../../src/unity_build/)

[Zur Dokumentationsübersicht](../README.md)
