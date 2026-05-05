#pragma once

#if defined(LINUX) || defined(__linux__)
 #define JUCE_DSP_USE_SHARED_FFTW 1
#endif

#ifndef _ENABLE_EXTENDED_ALIGNED_STORAGE
 #define _ENABLE_EXTENDED_ALIGNED_STORAGE
#endif

#ifndef JUCE_DISPLAY_SPLASH_SCREEN
 #define JUCE_DISPLAY_SPLASH_SCREEN 0
#endif

#define JUCE_USE_DARK_SPLASH_SCREEN 1

#define JUCE_MODULE_AVAILABLE_juce_audio_basics 1
#define JUCE_MODULE_AVAILABLE_juce_audio_devices 1
#define JUCE_MODULE_AVAILABLE_juce_audio_formats 1
#define JUCE_MODULE_AVAILABLE_juce_audio_processors 1
#define JUCE_MODULE_AVAILABLE_juce_audio_utils 1
#define JUCE_MODULE_AVAILABLE_juce_core 1
#define JUCE_MODULE_AVAILABLE_juce_data_structures 1
#define JUCE_MODULE_AVAILABLE_juce_dsp 1
#define JUCE_MODULE_AVAILABLE_juce_events 1
#define JUCE_MODULE_AVAILABLE_juce_graphics 1
#define JUCE_MODULE_AVAILABLE_juce_gui_basics 1
#define JUCE_MODULE_AVAILABLE_juce_gui_extra 1
#define JUCE_MODULE_AVAILABLE_juce_opengl 1

#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED 1

#ifndef JUCE_USE_CURL
 #define JUCE_USE_CURL 1
#endif

#ifndef JUCE_STANDALONE_APPLICATION
 #define JUCE_STANDALONE_APPLICATION 0
#endif
