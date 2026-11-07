# Build und Veröffentlichung

**Status:** Gliederung; Fachkapitel noch auszuarbeiten.

## Geplante Kapitel

- `requirements.md`: Toolchain, unterstützte und tatsächlich geprüfte Plattformen sowie Systemabhängigkeiten.
- `cmake-targets.md`: Target-Abhängigkeiten, Build-Varianten, Unity-Builds und Compilerdefinitionen.
- `packaging-and-installation.md`: Artefaktpfade, VST3-Bundles, Standalone-Installation und Paketierung.
- `dependencies-and-licenses.md`: JUCE-Version, weitere eingebettete Bibliotheken, Updates und Lizenzhinweise.
- `release-checklist.md`: Reproduzierbarer Build, Tests, Host-Prüfung, Versionierung und Veröffentlichung.

Aktuelle CMake-Wege und ältere Projucer-/Makefile-Wege getrennt behandeln;
vorhandene Projektdateien allein belegen keine erfolgreich geprüfte Plattform.

## Einstieg in den Code

- [Build-Kurzanleitung](../../README.md#building-on-linux) und [CMake-Einstieg](../../CMakeLists.txt)
- Target-Konfigurationen: [Plugin](../../plugin/CMakeLists.txt), [Standalone](../../standalone/CMakeLists.txt), [Headless](../../headless/CMakeLists.txt)
- [JUCE-Kompatibilitätsschicht](../../cmake/juce_compat/), [älteres Makefile](../../Makefile) und [Debian-Paketierung](../../debian/)

[Zur Dokumentationsübersicht](../README.md)
