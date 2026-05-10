cmake_minimum_required(VERSION 3.15)
project(CapusynPlugin LANGUAGES CXX)

# Plugin-specific unity-build source.
set(CAPUSYN_PLUGIN_CPP
    ${CMAKE_SOURCE_DIR}/src/unity_build/plugin.cpp
)
juce_add_plugin(Capusyn
    VERSION "1.0.6"
    BUNDLE_ID "io.github.BaraMGB.capusyn.synth"
    COMPANY_NAME "Capusyn Project"
    PLUGIN_VERSION "1.0.6"
    PLUGIN_MANUFACTURER_CODE CPSN
    PLUGIN_CODE CPSY
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    VST3_CATEGORIES Instrument Synth
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    AAX_IDENTIFIER "io.github.BaraMGB.capusyn.synth"
    AAX_CATEGORY SWGenerators
    COMPANY_WEBSITE "https://github.com/BaraMGB/capusyn"
    COMPANY_EMAIL "opensource@capusyn.invalid"
    COPYRIGHT "Capusyn Project"
    IS_MIDI_EFFECT FALSE
    # Linux: only VST3 and Standalone are enabled.
    BUILD_AUV3 FALSE
    ENABLE_IAA FALSE
    FORMATS VST3 Standalone
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(Capusyn)

target_sources(Capusyn PRIVATE
    ${CAPUSYN_PLUGIN_CPP}
    $<TARGET_OBJECTS:CapusynCore>
    $<TARGET_OBJECTS:CapusynGui>
)

add_custom_command(TARGET Capusyn_VST3 PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Capusyn_VST3>"
)

target_include_directories(Capusyn PRIVATE
    BEFORE
    ${CMAKE_SOURCE_DIR}/src/plugin
)

target_include_directories(Capusyn PRIVATE
    ${CAPUSYN_COMMON_INCLUDE_DIRS}
)

target_compile_definitions(Capusyn PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1
    NO_AUTH=1
)

target_link_libraries(Capusyn
    PUBLIC
        CapusynData
        ${CAPUSYN_JUCE_SHARED_MODULES}
        CURL::libcurl
        juce::juce_audio_plugin_client
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
