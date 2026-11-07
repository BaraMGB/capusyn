# Capusyn – Roadmap

## Ausgangspunkt

- JUCE 9.0.5 ist integriert; der Release-Build wurde mit 12 parallelen Jobs geprüft.
- 182 nichtgrafische Teiltests bestanden beim JUCE-Update.
- Das aktualisierte VST3 wurde im Host praktisch bestätigt; das ersetzt keine umfassenden GUI-/Host-Regressionstests.
- Die folgenden Aufgaben stammen aus der Codeprüfung und sind noch offen.

## Prioritäten und Reihenfolge

**P1:** Korrektheit, Echtzeitsicherheit und robuste Datenverarbeitung.
**P2:** Kürzere Build-Zeiten und bessere Automatisierung.

Zuerst die bestehenden Tests an CTest anbinden. Anschließend Echtzeitpfade und
Host-Parameter korrigieren, danach Import und Zustandsspeicherung absichern.
Build-Optimierungen folgen separat. Der Renderer-Umbau bleibt ein eigenes Vorhaben.

## 1. Echtzeitpfade absichern — P1

Betroffen: `src/common/midi_manager.cpp`, `src/common/synth_base.cpp`.

- [ ] Speichern der MIDI-Learn-Konfiguration aus dem Audio-Thread auslagern.
- [ ] Änderungen über eine begrenzte, vorab angelegte Queue oder einen geeigneten Snapshot an einen Hintergrunddienst übergeben.
- [ ] Dynamische Nachrichtenallokationen bei Host-Parameter-, MIDI- und Pitchbend-Änderungen vermeiden; GUI-Aktualisierungen bündeln.
- [ ] Verhalten bei voller Queue, geschlossenem Editor und Plugin-Abbau festlegen und testen.

**Abnahme:** In den überarbeiteten Audio-Callback-Pfaden finden keine Dateizugriffe,
Heap-Allokationen oder blockierenden Warteoperationen statt. Automation und MIDI-Learn
funktionieren auch unter Last und bei geschlossenem Editor.

## 2. Host-Parameter korrekt konvertieren — P1

Betroffen: `src/plugin/value_bridge.h`.

- [ ] `getValueForText()` auf normalisierte Werte zwischen 0 und 1 korrigieren.
- [ ] Anzeige-Offset, Skalierungsfaktor und sämtliche nichtlinearen Skalierungen korrekt invertieren.
- [ ] Benannte Auswahlwerte, diskrete Parameter und ungültige Eingaben behandeln.
- [ ] Roundtrip-Tests für `getText()` und `getValueForText()` ergänzen, einschließlich Transpose, Pan, Volume und exponentieller Parameter.
- [ ] Bestehende Parameterreihenfolge und Host-Identitäten unverändert lassen.

**Abnahme:** Beispielsweise wird „Sample Transpose: 12“ korrekt zu `0,625` normalisiert.
Roundtrips berücksichtigen die Genauigkeit des Anzeigetextes und die Quantisierung.
Ungültige Eingaben erzeugen keine NaN-, Infinity- oder außerhalb von 0 bis 1 liegenden Werte.

## 3. Preset- und Sample-Import validieren — P1

Betroffen: `src/synthesis/producers/sample_source.cpp`,
`src/common/wavetable/wave_source.cpp`, `src/common/wavetable/file_source.cpp`,
`src/common/load_save.cpp`.

- [ ] Sample-Länge und Samplerate vor Speicherallokationen auf gültige Werte und dokumentierte Obergrenzen prüfen.
- [ ] Base64-Dekodierung auf Erfolg und exakte erwartete Datenlänge prüfen, einschließlich Stereo-Daten.
- [ ] Größenberechnungen gegen Überläufe absichern und nichtendliche Audiodaten zurückweisen.
- [ ] Fehlerhafte Daten vor Übernahme in den aktiven Zustand ablehnen.
- [ ] Tests für leere, abgeschnittene, übergroße und widersprüchliche Daten ergänzen; Importpfade zusätzlich mit Sanitizern prüfen.

**Abnahme:** Beschädigte Presets werden mit nachvollziehbarem Fehler abgewiesen,
ohne Absturz, unkontrollierte Speicheranforderung oder Verlust des zuvor gültigen Zustands.

## 4. Plugin-Zustand zuverlässig speichern — P1

Betroffen: `src/plugin/synth_plugin.cpp`.

- [ ] In `getStateInformation()` den Zielpuffer ersetzen statt neue Daten anzuhängen.
- [ ] Wiederholtes Speichern in denselben `MemoryBlock` testen.
- [ ] Save-/Restore-Roundtrips für Parameter, Modulationen, Makronamen, Tuning, Samples und Wavetables ergänzen.
- [ ] Wiederherstellung bei geschlossenem Editor und beschädigten Zustandsdaten testen.

**Abnahme:** Jeder Aufruf liefert genau einen vollständigen Zustand. Ein erneut
verwendeter Zielpuffer enthält keine angehängten Altzustände; bestehende gültige
Projektzustände bleiben ladbar.

## 5. Build-System verschlanken — P2

Betroffen: `plugin/CMakeLists.txt`, `CMakeLists.txt` und die übrigen Target-Konfigurationen.

- [ ] JUCE-Modulquellen nicht mehr unnötig über öffentliche Abhängigkeiten an sämtliche Plugin-Wrapper weiterreichen.
- [ ] Gemeinsamen Code pro kompatibler Konfiguration wiederverwenden; notwendige Unterschiede zwischen GUI-, Headless- und Wrapper-Zielen erhalten.
- [ ] Serielle LTO-Verarbeitung untersuchen und Parallelität kontrolliert konfigurieren, ohne CPU und RAM zu überbuchen.
- [ ] Saubere Builds und inkrementelle Builds vor und nach der Änderung unter gleichen Bedingungen messen.

**Abnahme:** JUCE-GUI-Modulquellen werden für die Plugin-Ziele nicht mehr dreifach
kompiliert. Alle bisherigen Targets bauen weiterhin; Tests und VST3-Host-Prüfung
bestehen. Die gemessenen Build-Zeiten werden dokumentiert.

## 6. Tests und CI automatisieren — P2, Testanbindung vorziehen

Betroffen: `CMakeLists.txt`, `tests/CMakeLists.txt`, `tests/main.cpp`, neue GitHub-Workflows.

- [ ] Das vorhandene nichtgrafische Testprogramm bei CTest registrieren.
- [ ] Sicherstellen, dass fehlgeschlagene Tests einen Fehlerstatus liefern; Zeitlimits festlegen.
- [ ] Linux-CI für Konfiguration, Release-Build und nichtgrafische Tests bei Pushes und Pull Requests einrichten.
- [ ] Regressionstests aus den Punkten 1 bis 4 in den automatisierten Lauf aufnehmen.
- [ ] GUI-/Host-Tests getrennt dokumentieren und nicht durch einen erfolgreichen nichtgrafischen Lauf als abgedeckt behandeln.

**Abnahme:** `ctest --test-dir <build-dir> --output-on-failure` findet und startet die
Tests. Fehler lassen die CI fehlschlagen; erfolgreiche Läufe sind einem Commit zugeordnet.

## Eigenständiges Folgevorhaben: Renderer-Umbau

Nach den Stabilitätsverbesserungen, ohne Zusage eines Veröffentlichungstermins:

- [ ] Layout, Parameterbindungen und Audio-Engine beibehalten.
- [ ] OpenGL-Bedienelemente schrittweise auf JUCE `paint(Graphics&)` umstellen.
- [ ] Shaderbasierte Kurven, Spektren und Wavetable-Vorschauen durch CPU-Berechnung und JUCE-Pfade ersetzen.
- [ ] Statische Hintergründe zwischenspeichern und Animationen gezielt aktualisieren.
- [ ] Darstellung, Bedienung und CPU-Last mit mehreren offenen Plugin-Instanzen vergleichen.

**Abnahme:** Die migrierte Oberfläche benötigt keinen OpenGL-Kontext und bleibt
vollständig bedienbar. Darstellungsqualität und CPU-Last werden separat geprüft.

**Abgrenzung:** Der normale JUCE-Renderer allein bringt keine native
Wayland-Unterstützung. JUCE 9.0.5 nutzt unter Linux weiterhin X11/XWayland.
