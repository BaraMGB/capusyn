/* Copyright 2013-2019 Capusyn Project
 *
 * capusyn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * capusyn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with capusyn.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "synth_oscillator_test.h"
#include "synth_oscillator.h"
#include "wavetable.h"

void SynthOscillatorTest::runTest() {
  capusyn::Wavetable wavetable(capusyn::kNumOscillatorWaveFrames);

  std::unique_ptr<capusyn::SynthOscillator> osc = std::make_unique<capusyn::SynthOscillator>(&wavetable);
  // runInputBoundsTest(osc.get());
}

static SynthOscillatorTest synth_oscillator_test;
