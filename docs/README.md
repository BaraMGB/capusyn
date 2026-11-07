# Technische Dokumentation

Diese Dokumentation beschreibt Aufbau, Schnittstellen und Entwicklung von Capusyn.
Sie richtet sich an Entwickler und Maintainer, nicht an Endanwender.

**Status:** Grundstruktur. Die Bereichsübersichten definieren die geplanten Inhalte;
die eigentlichen Fachkapitel werden schrittweise ausgearbeitet.

## Bereiche

| Verzeichnis | Inhalt |
| --- | --- |
| [architecture/](architecture/README.md) | Systemübersicht, Module, Datenfluss, Threads und Lebenszyklen |
| [audio-engine/](audio-engine/README.md) | Synthese, Stimmen, Modulation, Filter, Effekte und Echtzeitverarbeitung |
| [user-interface/](user-interface/README.md) | Komponenten, Layout, Interaktion, Darstellung und Themes |
| [interfaces/](interfaces/README.md) | VST3, Host-Anbindung, Parameter, MIDI/MPE und Kommandozeile |
| [data-formats/](data-formats/README.md) | Presets, Plugin-Zustand, Samples, Wavetables und Konfiguration |
| [build-and-release/](build-and-release/README.md) | Abhängigkeiten, CMake, Artefakte, Installation und Lizenzen |
| [testing/](testing/README.md) | Automatisierte Tests, Host-/GUI-Prüfungen, Performance und CI |
| [decisions/](decisions/README.md) | Technische Entscheidungsprotokolle (ADRs) |
| [assets/](assets/README.md) | Diagramme und weitere Abbildungen für die Dokumentation |

## Konventionen

- Dokumentation auf Deutsch; Codebezeichner und Schnittstellennamen unverändert übernehmen.
- Dateinamen auf Englisch in `kebab-case`; Markdown als Grundformat verwenden.
- Implementierten Ist-Zustand, geplante Änderungen und offene Fragen ausdrücklich trennen.
- Aussagen mit relativen Links auf relevante Quelldateien und Tests belegen.
- Schnittstellen und Datenformate zusammen mit dem betreffenden Code aktualisieren.
- Diagramme möglichst als versionierbare Textquelle pflegen, beispielsweise Mermaid.
- Generierte Build-Dateien und Kopien der JUCE-Dokumentation nicht hier ablegen.

Prioritäten und Umsetzungsschritte stehen in der [Roadmap](../ROADMAP.md).
Die technische Dokumentation erläutert das System; sie ersetzt nicht die Aufgabenplanung.
