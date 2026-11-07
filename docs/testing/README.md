# Tests und Qualitätssicherung

**Status:** Gliederung; Fachkapitel noch auszuarbeiten.

## Geplante Kapitel

- `test-strategy.md`: Testebenen, Abdeckung, bekannte Lücken und Anforderungen an Regressionstests.
- `automated-tests.md`: Testprogramm, Kategorien, nichtgrafische Läufe, Seeds, Fehlerstatus und Zeitlimits.
- `host-and-gui-tests.md`: VST3-Hosts, Editor-Lebenszyklus, Automation, State-Roundtrips und manuelle Prüfungen.
- `performance-and-sanitizers.md`: Echtzeitsicherheit, CPU-/Speichermessungen, Profiling und Sanitizer.
- `ci.md`: Geplante CTest-/CI-Anbindung und später deren tatsächlich umgesetzte Konfiguration.

Testergebnisse immer einem Commit und einer Umgebung zuordnen.
Nichtgrafische Tests, GUI-Tests und manuelle Host-Tests getrennt ausweisen.

## Einstieg in den Code

- [Test-Einstieg](../../tests/main.cpp) und [Test-Target](../../tests/CMakeLists.txt)
- [Synthesetests](../../tests/synthesis/), [Stresstests](../../tests/stress/) und [GUI-Tests](../../tests/interface/)
- [JUCE-/SVG-Kompatibilitätstests](../../tests/juce_compatibility_tests.cpp)
- [Geplante Qualitätsverbesserungen](../../ROADMAP.md)

[Zur Dokumentationsübersicht](../README.md)
