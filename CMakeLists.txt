cmake_minimum_required(VERSION 3.15)
project(Vital VERSION 1.0.6 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

# JUCE is expected under third_party/JUCE.
add_subdirectory(third_party/JUCE)

# Shared include directories for the local targets.
set(VITAL_COMMON_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/third_party
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/src/common/wavetable
    ${CMAKE_SOURCE_DIR}/src/interface
    ${CMAKE_SOURCE_DIR}/src/interface/editor_components
    ${CMAKE_SOURCE_DIR}/src/interface/editor_sections
    ${CMAKE_SOURCE_DIR}/src/interface/look_and_feel
    ${CMAKE_SOURCE_DIR}/src/interface/wavetable
    ${CMAKE_SOURCE_DIR}/src/interface/wavetable/editors
    ${CMAKE_SOURCE_DIR}/src/interface/wavetable/overlays
    ${CMAKE_SOURCE_DIR}/src/plugin
    ${CMAKE_SOURCE_DIR}/src/standalone
    ${CMAKE_SOURCE_DIR}/src/synthesis
    ${CMAKE_SOURCE_DIR}/src/synthesis/effects
    ${CMAKE_SOURCE_DIR}/src/synthesis/filters
    ${CMAKE_SOURCE_DIR}/src/synthesis/framework
    ${CMAKE_SOURCE_DIR}/src/synthesis/lookups
    ${CMAKE_SOURCE_DIR}/src/synthesis/modulators
    ${CMAKE_SOURCE_DIR}/src/synthesis/modules
    ${CMAKE_SOURCE_DIR}/src/synthesis/producers
    ${CMAKE_SOURCE_DIR}/src/synthesis/synth_engine
    ${CMAKE_SOURCE_DIR}/src/synthesis/utilities
)

set(VITAL_SHARED_ASSETS
    ${CMAKE_SOURCE_DIR}/tunings/*.scl
    ${CMAKE_SOURCE_DIR}/tunings/*.sclx
    ${CMAKE_SOURCE_DIR}/default.vitalskin
    ${CMAKE_SOURCE_DIR}/fonts/*.*
    ${CMAKE_SOURCE_DIR}/icons/*.svg
    ${CMAKE_SOURCE_DIR}/icons/*.png
)

file(GLOB VITAL_SHARED_ASSET_FILES ${VITAL_SHARED_ASSETS})
juce_add_binary_data(VitalData SOURCES ${VITAL_SHARED_ASSET_FILES})

set(VITAL_JUCE_SHARED_MODULES
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_opengl
)

# Core sources as unity-build translation units.
set(VITAL_CORE_CPP
    ${CMAKE_SOURCE_DIR}/cmake/juce_compat/vital_core.cpp
    ${CMAKE_SOURCE_DIR}/src/unity_build/synthesis.cpp
)

add_library(VitalCore OBJECT ${VITAL_CORE_CPP})
target_include_directories(VitalCore PRIVATE ${VITAL_COMMON_INCLUDE_DIRS})
target_include_directories(VitalCore PRIVATE
    ${CMAKE_SOURCE_DIR}/cmake/juce_compat
    ${CMAKE_SOURCE_DIR}/third_party/JUCE/modules
)
target_link_libraries(VitalCore PRIVATE
    VitalData
)
# Headless/tests do not need WebView support.
target_compile_definitions(VitalCore PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_DSP_USE_SHARED_FFTW=1
    JUCE_USE_XRANDR=0
    JUCE_OPENGL3=1
    JUCE_MODAL_LOOPS_PERMITTED=1
    NO_AUTH=1
)

add_library(VitalCoreHeadless OBJECT ${VITAL_CORE_CPP})
target_include_directories(VitalCoreHeadless PRIVATE ${VITAL_COMMON_INCLUDE_DIRS})
target_include_directories(VitalCoreHeadless PRIVATE
    ${CMAKE_SOURCE_DIR}/cmake/juce_compat
    ${CMAKE_SOURCE_DIR}/third_party/JUCE/modules
)
target_link_libraries(VitalCoreHeadless PRIVATE
    VitalData
)
target_compile_definitions(VitalCoreHeadless PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_DSP_USE_SHARED_FFTW=1
    JUCE_USE_XRANDR=0
    JUCE_OPENGL3=1
    JUCE_MODAL_LOOPS_PERMITTED=1
    HEADLESS=1
    NO_AUTH=1
)

# GUI sources as unity-build translation units.
set(VITAL_GUI_CPP
    ${CMAKE_SOURCE_DIR}/src/common/border_bounds_constrainer.cpp
    ${CMAKE_SOURCE_DIR}/src/unity_build/interface_look_and_feel.cpp
    ${CMAKE_SOURCE_DIR}/src/unity_build/interface_editor_components.cpp
    ${CMAKE_SOURCE_DIR}/src/unity_build/interface_editor_sections.cpp
    ${CMAKE_SOURCE_DIR}/src/unity_build/interface_editor_sections2.cpp
    ${CMAKE_SOURCE_DIR}/src/unity_build/interface_wavetable.cpp
)

add_library(VitalGui OBJECT ${VITAL_GUI_CPP})
target_include_directories(VitalGui PRIVATE ${VITAL_COMMON_INCLUDE_DIRS})
target_include_directories(VitalGui PRIVATE
    ${CMAKE_SOURCE_DIR}/cmake/juce_compat
    ${CMAKE_SOURCE_DIR}/third_party/JUCE/modules
)
target_link_libraries(VitalGui
    PRIVATE
        VitalData
)
target_compile_definitions(VitalGui PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_DSP_USE_SHARED_FFTW=1
    JUCE_USE_XRANDR=0
    JUCE_OPENGL3=1
    JUCE_MODAL_LOOPS_PERMITTED=1
    NO_AUTH=1
)

# Subtargets
add_subdirectory(plugin)
add_subdirectory(standalone)
add_subdirectory(headless)
add_subdirectory(tests)
