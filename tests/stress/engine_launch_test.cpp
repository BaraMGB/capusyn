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

#include "engine_launch_test.h"
#include "sound_engine.h"

namespace {
  constexpr int kNumRuns = 10;
}

void EngineLaunchTest::launchTest() {
  beginTest("Launch Test");
  capusyn::SoundEngine engines[kNumRuns];

  for (int i = 0; i < kNumRuns; ++i) {
    capusyn::SoundEngine& engine = engines[i];
    engine.allNotesOff(0);
    expect(capusyn::utils::isFinite(engine.output()->buffer[0]));

    engine.noteOn(60, 1.0f, 0, 0);
    engine.process(capusyn::kMaxBufferSize);
    engine.noteOn(62, 1.0f, 0, 0);
    engine.process(capusyn::kMaxBufferSize);
    engine.noteOn(64, 1.0f, 0, 0);
    expect(capusyn::utils::isFinite(engine.output()->buffer[0]));

    engine.noteOn(65, 1.0f, 0, 0);
    engine.process(capusyn::kMaxBufferSize);
    engine.process(capusyn::kMaxBufferSize);
    expect(capusyn::utils::isFinite(engine.output()->buffer[0]));

    engine.noteOff(64, 1.0f, 0, 0);
    engine.noteOff(65, 1.0f, 0, 0);
    engine.noteOff(62, 1.0f, 0, 0);
    engine.noteOff(60, 1.0f, 0, 0);
    engine.process(capusyn::kMaxBufferSize);
    expect(capusyn::utils::isFinite(engine.output()->buffer[0]));

    engine.process(capusyn::kMaxBufferSize);
    engine.process(capusyn::kMaxBufferSize);
    engine.process(capusyn::kMaxBufferSize);
    engine.process(capusyn::kMaxBufferSize);
    engine.process(capusyn::kMaxBufferSize);
    expect(capusyn::utils::isFinite(engine.output()->buffer[0]));
  }
}

void EngineLaunchTest::runTest() {
  launchTest();
}

static EngineLaunchTest engine_launch_test;
