#pragma once

#include "AppConfig.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_opengl/juce_opengl.h>

#if __has_include("BinaryData.h")
#include "BinaryData.h"
#endif

#if ! DONT_SET_USING_JUCE_NAMESPACE
using namespace juce;
#endif

using namespace juce::gl;

#if ! JUCE_DONT_DECLARE_PROJECTINFO
namespace ProjectInfo {
const char* const projectName = "Vital";
const char* const companyName = "Vital Audio";
const char* const versionString = "1.0.6";
const int versionNumber = 0x10006;
}
#endif
