cmake_minimum_required(VERSION 3.15)
project(VitalPlugin LANGUAGES CXX)

# Plugin-specific unity-build source.
set(VITAL_PLUGIN_CPP
    ${CMAKE_SOURCE_DIR}/src/unity_build/plugin.cpp
)
juce_add_plugin(Vital
    VERSION "1.0.6"
    BUNDLE_ID "audio.vital.synth"
    COMPANY_NAME "Vital Audio"
    PLUGIN_VERSION "1.0.6"
    PLUGIN_MANUFACTURER_CODE Open
    PLUGIN_CODE Vial
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    VST3_CATEGORIES Instrument Synth
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    AAX_IDENTIFIER "audio.vial.synth"
    AAX_CATEGORY SWGenerators
    COMPANY_WEBSITE "vital.audio"
    COMPANY_EMAIL "matthewtytel@gmail.com"
    COPYRIGHT "Matt Tytel"
    IS_MIDI_EFFECT FALSE
    # Linux: only VST3 and Standalone are enabled.
    BUILD_AUV3 FALSE
    ENABLE_IAA FALSE
    FORMATS VST3 Standalone
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(Vital)

target_sources(Vital PRIVATE
    ${VITAL_PLUGIN_CPP}
    $<TARGET_OBJECTS:VitalCore>
    $<TARGET_OBJECTS:VitalGui>
)

add_custom_command(TARGET Vital_VST3 PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Vital_VST3>"
)

target_include_directories(Vital PRIVATE
    BEFORE
    ${CMAKE_SOURCE_DIR}/src/plugin
)

target_include_directories(Vital PRIVATE
    ${VITAL_COMMON_INCLUDE_DIRS}
)

target_compile_definitions(Vital PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1
    NO_AUTH=1
)

target_link_libraries(Vital
    PUBLIC
        VitalData
        ${VITAL_JUCE_SHARED_MODULES}
        CURL::libcurl
        juce::juce_audio_plugin_client
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
