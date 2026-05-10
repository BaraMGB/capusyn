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

#include "JuceHeader.h"

#include "common.h"

class OpenGlMultiQuad;
class SynthSlider;
namespace capusyn {
  struct Output;
}

class ModulationMeter : public Component {
  public:
    ModulationMeter(const capusyn::Output* mono_total, const capusyn::Output* poly_total,
                    const SynthSlider* slider, OpenGlMultiQuad* quads, int index);
    virtual ~ModulationMeter();

    void resized() override;
    void setActive(bool active);

    void updateDrawing(bool use_poly);
    void setModulationAmountQuad(OpenGlQuad& quad, float amount, bool bipolar);
    void setAmountQuadVertices(OpenGlQuad& quad);

    bool isModulated() const { return modulated_; }
    bool isRotary() const { return rotary_; }
    void setModulated(bool modulated) { modulated_ = modulated; }
    capusyn::poly_float getModPercent() { return mod_percent_; }

    const SynthSlider* destination() { return destination_; }

  private:
    ModulationMeter() = delete;

    Rectangle<float> getMeterBounds();
    void setVertices();
    void collapseVertices();

    const capusyn::Output* mono_total_;
    const capusyn::Output* poly_total_;
    const SynthSlider* destination_;

    OpenGlMultiQuad* quads_;
    int index_;

    capusyn::poly_float current_value_;
    capusyn::poly_float mod_percent_;

    bool modulated_;
    bool rotary_;

    float left_, right_, top_, bottom_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulationMeter)
};

