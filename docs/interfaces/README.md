# Schnittstellen

**Status:** Gliederung; Fachkapitel noch auszuarbeiten.

## Geplante Kapitel

- `vst3-and-hosts.md`: Plugin-Identität, Buslayouts, Host-Lebenszyklus, Transport und Editor-Anbindung.
- `parameters-and-automation.md`: Parameterdefinitionen, Normalisierung, Anzeigeformate und Automationsgesten.
- `midi-and-mpe.md`: MIDI-Ereignisse, MIDI-Learn, Geräteverwaltung und MPE.
- `standalone-and-cli.md`: Standalone-Start, Audiogeräte und Headless-Rendering mit Kommandozeilenargumenten.

Das Speicherformat des Plugin-Zustands gehört zu [Datenformaten](../data-formats/README.md);
das Verhalten der Host-Callbacks wird hier beschrieben.

## Einstieg in den Code

- [Plugin-Prozessor](../../src/plugin/synth_plugin.h) und [Parameterbrücke](../../src/plugin/value_bridge.h)
- [Parameterdefinitionen](../../src/common/synth_parameters.h)
- [MIDI-Verarbeitung](../../src/common/midi_manager.h)
- [Standalone-Einstieg](../../src/standalone/main.cpp) und [Headless-Einstieg](../../src/headless/main.cpp)

[Zur Dokumentationsübersicht](../README.md)
