# Datenformate und Persistenz

**Status:** Gliederung; Fachkapitel noch auszuarbeiten.

## Geplante Kapitel

- `presets-and-plugin-state.md`: JSON-Struktur, Metadaten, Parameter und gespeicherter Plugin-Zustand.
- `samples-and-wavetables.md`: Eingebettete Audiodaten, Base64, Datenlängen und Wavetable-Strukturen.
- `skins-and-tunings.md`: Skin-Dateien, Farb-/Layoutwerte und Stimmungsdateien.
- `configuration-and-migration.md`: Benutzerdaten, MIDI-Zuordnungen, Versionsprüfung und Migration älterer Daten.

Für jedes Format sind Felder, Datentypen, Einheiten, Standardwerte, Grenzen,
Fehlerbehandlung und Kompatibilitätsregeln zu dokumentieren. Beispiele verwenden
synthetische Daten, keine persönlichen Presets oder lokale Benutzerkonfigurationen.

## Einstieg in den Code

- [Laden, Speichern und Migration](../../src/common/load_save.cpp)
- [Samples](../../src/synthesis/producers/sample_source.cpp) und [Wavetables](../../src/common/wavetable/)
- [Skins](../../src/interface/look_and_feel/skin.cpp) und [Standard-Skin](../../default.capuskin)
- [Tuning-Verarbeitung](../../src/common/tuning.cpp) und [mitgelieferte Tunings](../../tunings/)

[Zur Dokumentationsübersicht](../README.md)
