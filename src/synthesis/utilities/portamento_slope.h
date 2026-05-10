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

#pragma once

#include "processor.h"

namespace capusyn {

  class PortamentoSlope : public Processor {
    public:
      static constexpr float kMinPortamentoTime = 0.001f;

      enum {
        kTarget,
        kSource,
        kPortamentoForce,
        kPortamentoScale,
        kRunSeconds,
        kSlopePower,
        kReset,
        kNumNotesPressed,
        kNumInputs
      };

      PortamentoSlope();
      virtual ~PortamentoSlope() { }

      virtual Processor* clone() const override {
        return new PortamentoSlope(*this);
      }

      void processBypass(int start);
      virtual void process(int num_samples) override;

    private:
      poly_float position_;

      JUCE_LEAK_DETECTOR(PortamentoSlope)
  };
} // namespace capusyn

