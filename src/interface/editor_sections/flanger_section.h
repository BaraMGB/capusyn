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
#include "synth_section.h"
#include "open_gl_line_renderer.h"
#include "comb_filter.h"
#include "synth_module.h"

class SynthButton;
class TempoSelector;
class SynthSlider;
class SynthGuiInterface;

class FlangerResponse : public OpenGlLineRenderer {
  public:
    static constexpr int kResolution = 512;
    static constexpr int kDefaultVisualSampleRate = 200000;
    static constexpr int kCombAlternatePeriod = 2;

    FlangerResponse(const capusyn::output_map& mono_modulations);
    virtual ~FlangerResponse();

    void init(OpenGlWrapper& open_gl) override;
    void render(OpenGlWrapper& open_gl, bool animate) override;
    void destroy(OpenGlWrapper& open_gl) override;

    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;

    void setCenterSlider(SynthSlider* slider) { center_slider_ = slider; }
    void setFeedbackSlider(SynthSlider* slider) { feedback_slider_ = slider; }
    void setMixSlider(SynthSlider* slider) { mix_slider_ = slider; }

    void setActive(bool active) { active_ = active; }

  private:
    struct FilterResponseShader {
      static constexpr int kMaxStages = 4;
      OpenGLShaderProgram* shader;
      std::unique_ptr<OpenGLShaderProgram::Attribute> position;

      std::unique_ptr<OpenGLShaderProgram::Uniform> mix;
      std::unique_ptr<OpenGLShaderProgram::Uniform> drive;
      std::unique_ptr<OpenGLShaderProgram::Uniform> midi_cutoff;
      std::unique_ptr<OpenGLShaderProgram::Uniform> resonance;
      std::unique_ptr<OpenGLShaderProgram::Uniform> stages[kMaxStages];
    };

    void drawFilterResponse(OpenGlWrapper& open_gl, bool animate);
    capusyn::poly_float getOutputTotal(capusyn::Output* output, capusyn::poly_float default_value);

    void setupFilterState();
    void loadShader(int index);
    void bind(OpenGLContext& open_gl_context);
    void unbind(OpenGLContext& open_gl_context);
    void renderLineResponse(OpenGlWrapper& open_gl, int index);

    SynthGuiInterface* parent_;
    bool active_;
    Point<int> last_mouse_position_;

    capusyn::CombFilter comb_filter_;
    capusyn::SynthFilter::FilterState filter_state_;
    capusyn::poly_float mix_;

    SynthSlider* center_slider_;
    SynthSlider* feedback_slider_;
    SynthSlider* mix_slider_;

    const capusyn::StatusOutput* flanger_frequency_;
    capusyn::Output* feedback_output_;
    capusyn::Output* mix_output_;

    FilterResponseShader response_shader_;
    std::unique_ptr<float[]> line_data_;
    GLuint vertex_array_object_;
    GLuint line_buffer_;
    GLuint response_buffer_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlangerResponse)
};

class FlangerSection : public SynthSection {
  public:
    FlangerSection(String name, const capusyn::output_map& mono_modulations);
    virtual ~FlangerSection();

    void paintBackground(Graphics& g) override;
    void paintBackgroundShadow(Graphics& g) override { if (isActive()) paintTabShadow(g); }
    void resized() override;
    void setActive(bool active) override;

  private:
    std::unique_ptr<SynthButton> on_;
    std::unique_ptr<SynthSlider> frequency_;
    std::unique_ptr<SynthSlider> tempo_;
    std::unique_ptr<TempoSelector> sync_;
    std::unique_ptr<SynthSlider> feedback_;
    std::unique_ptr<SynthSlider> mod_depth_;
    std::unique_ptr<SynthSlider> center_;
    std::unique_ptr<SynthSlider> phase_offset_;
    std::unique_ptr<SynthSlider> dry_wet_;

    std::unique_ptr<FlangerResponse> flanger_response_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlangerSection)
};
