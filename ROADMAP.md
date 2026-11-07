# Capusyn – Roadmap

## Baseline

- JUCE 9.0.5 is integrated; the release build was verified with 12 parallel jobs.
- 182 non-graphical subtests passed during the JUCE update.
- The updated VST3 was confirmed working in a host; this does not replace comprehensive GUI/host regression tests.
- The following tasks were identified during code review and remain open.

## Priorities and implementation order

**P1:** Correctness, real-time safety, and robust data handling.
**P2:** Shorter build times and better automation.

First, register the existing tests with CTest. Then address real-time paths and
host parameter conversion, followed by import validation and state persistence.
Build optimizations follow separately.

## 1. Make real-time paths safe — P1

Affected: `src/common/midi_manager.cpp`, `src/common/synth_base.cpp`.

- [ ] Move MIDI-learn configuration persistence off the audio thread.
- [ ] Pass changes to a background worker using a bounded, preallocated queue or an appropriate snapshot.
- [ ] Avoid dynamic message allocations for host parameter, MIDI, and pitch-bend changes; coalesce GUI updates.
- [ ] Define and test behavior when the queue is full, the editor is closed, or the plugin is being destroyed.

**Acceptance criteria:** The updated audio callback paths perform no file I/O,
heap allocations, or blocking waits. Automation and MIDI learn work under load
and with the editor closed.

## 2. Convert host parameters correctly — P1

Affected: `src/plugin/value_bridge.h`.

- [ ] Make `getValueForText()` return normalized values between 0 and 1.
- [ ] Correctly invert display offsets, scale factors, and all nonlinear scaling functions.
- [ ] Handle named choices, discrete parameters, and invalid input.
- [ ] Add round-trip tests for `getText()` and `getValueForText()`, including transpose, pan, volume, and exponential parameters.
- [ ] Preserve the existing parameter order and host identities.

**Acceptance criteria:** For example, "Sample Transpose: 12" is correctly normalized to `0.625`.
Round trips account for display-text precision and quantization.
Invalid input produces no NaN, infinity, or values outside the range from 0 to 1.

## 3. Validate preset and sample imports — P1

Affected: `src/synthesis/producers/sample_source.cpp`,
`src/common/wavetable/wave_source.cpp`, `src/common/wavetable/file_source.cpp`,
`src/common/load_save.cpp`.

- [ ] Validate sample lengths and sample rates against valid ranges and documented upper limits before allocating memory.
- [ ] Check Base64 decoding success and the exact expected data length, including stereo data.
- [ ] Protect size calculations against overflow and reject non-finite audio data.
- [ ] Reject invalid data before applying it to the active state.
- [ ] Add tests for empty, truncated, oversized, and inconsistent data; also check import paths with sanitizers.

**Acceptance criteria:** Corrupted presets are rejected with a meaningful error,
without crashes, uncontrolled memory requests, or loss of the previously valid state.

## 4. Save plugin state reliably — P1

Affected: `src/plugin/synth_plugin.cpp`.

- [ ] Replace the destination buffer in `getStateInformation()` instead of appending new data.
- [ ] Test repeated saves to the same `MemoryBlock`.
- [ ] Add save/restore round trips for parameters, modulations, macro names, tuning, samples, and wavetables.
- [ ] Test restoration with the editor closed and with corrupted state data.

**Acceptance criteria:** Each call returns exactly one complete state. A reused
destination buffer contains no appended old states; existing valid project states
remain loadable.

## 5. Streamline the build system — P2

Affected: `plugin/CMakeLists.txt`, `CMakeLists.txt`, and the other target configurations.

- [ ] Stop unnecessarily propagating JUCE module sources to every plugin wrapper through public dependencies.
- [ ] Reuse shared code within compatible configurations while preserving necessary differences between GUI, headless, and wrapper targets.
- [ ] Investigate serial LTO processing and configure parallelism without oversubscribing CPU or RAM.
- [ ] Measure clean and incremental builds before and after the changes under identical conditions.

**Acceptance criteria:** JUCE GUI module sources are no longer compiled three times
for the plugin targets. All existing targets still build; tests and VST3 host checks
pass. Measured build times are documented.

## 6. Automate tests and CI — P2, prioritize test registration

Affected: `CMakeLists.txt`, `tests/CMakeLists.txt`, `tests/main.cpp`, and new GitHub workflows.

- [ ] Register the existing non-graphical test executable with CTest.
- [ ] Ensure failed tests return a failure exit status; define timeouts.
- [ ] Set up Linux CI for configuration, release builds, and non-graphical tests on pushes and pull requests.
- [ ] Include regression tests from items 1 through 4 in the automated runs.
- [ ] Document GUI/host tests separately; a successful non-graphical run must not imply GUI/host coverage.

**Acceptance criteria:** `ctest --test-dir <build-dir> --output-on-failure` discovers
and runs the tests. Test failures fail CI; successful runs are associated with a commit.
