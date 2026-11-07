# Capusyn

Capusyn is a GPLv3 spectral warping wavetable synthesizer.

This repository is a fork of Vital and ships a full product rename for independent redistribution.

## Building on Linux

Requires CMake 3.22+, Ninja, a C++17 compiler, and the Linux dependencies listed in
[`third_party/JUCE/docs/Linux Dependencies.md`](third_party/JUCE/docs/Linux%20Dependencies.md).
JUCE 9 requires EGL and XInput development files (`libglvnd` and `libxi` on Arch Linux).
FFTW is also required at runtime on Linux.

```sh
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --parallel 12
build-release/tests/CapusynTests_artefacts/Release/CapusynTests --non-graphical
```

Use a fresh build directory if an existing CMake cache references another checkout or generator.

## JUCE dependency

JUCE **9.0.5** is vendored in `third_party/JUCE` without local patches.
Upstream tag: [`9.0.5`](https://github.com/juce-framework/JUCE/releases/tag/9.0.5),
commit `d60b7a78030661574a615b586d9325ba7a7fa7dd`.

## Technical documentation

Start at [docs/README.md](docs/README.md) for the documentation structure and planned technical chapters.

## Roadmap

See [ROADMAP.md](ROADMAP.md) for priorities, planned improvements, and acceptance criteria.

## Issues

Report build, runtime, and packaging issues in this repository.

## Licensing

Capusyn's own source code is available under the GPLv3. JUCE is separately licensed
under the AGPLv3 or a commercial JUCE licence; see
[`third_party/JUCE/LICENSE.md`](third_party/JUCE/LICENSE.md). Distribution of combined
binaries must comply with the applicable licences of all included components.
