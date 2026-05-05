cmake_minimum_required(VERSION 3.15)
project(VitalHeadless LANGUAGES CXX)

# Headless-specific sources only.
file(GLOB_RECURSE VITAL_HEADLESS_ONLY_CPP
    ${CMAKE_SOURCE_DIR}/src/headless/*.cpp
)

juce_add_console_app(VitalHeadless
    BUNDLE_ID "audio.vital.headless"
    VERSION "99999.9.9"
    COMPANY_NAME "Matt Tytel"
    COMPANY_WEBSITE "vital.audio"
    COMPANY_EMAIL "matthewtytel@gmail.com"
    COMPANY_COPYRIGHT "Matt Tytel"
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(VitalHeadless)

target_sources(VitalHeadless PRIVATE
    ${VITAL_HEADLESS_ONLY_CPP}
    $<TARGET_OBJECTS:VitalCoreHeadless>
)

target_include_directories(VitalHeadless PRIVATE
    ${VITAL_COMMON_INCLUDE_DIRS}
)

target_compile_definitions(VitalHeadless PRIVATE
    JUCE_WEB_BROWSER=0
    HEADLESS=1
    NO_AUTH=1
)

target_link_libraries(VitalHeadless
    PUBLIC
        VitalData
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_dsp
        juce::juce_graphics
        CURL::libcurl
        Threads::Threads
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
