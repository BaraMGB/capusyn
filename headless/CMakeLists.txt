cmake_minimum_required(VERSION 3.15)
project(CapusynHeadless LANGUAGES CXX)

# Headless-specific sources only.
file(GLOB_RECURSE CAPUSYN_HEADLESS_ONLY_CPP
    ${CMAKE_SOURCE_DIR}/src/headless/*.cpp
)

juce_add_console_app(CapusynHeadless
    BUNDLE_ID "io.github.BaraMGB.capusyn.headless"
    VERSION "99999.9.9"
    COMPANY_NAME "Capusyn Project"
    COMPANY_WEBSITE "https://github.com/BaraMGB/capusyn"
    COMPANY_EMAIL "opensource@capusyn.invalid"
    COMPANY_COPYRIGHT "Capusyn Project"
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(CapusynHeadless)

target_sources(CapusynHeadless PRIVATE
    ${CAPUSYN_HEADLESS_ONLY_CPP}
    $<TARGET_OBJECTS:CapusynCoreHeadless>
)

target_include_directories(CapusynHeadless PRIVATE
    ${CAPUSYN_COMMON_INCLUDE_DIRS}
)

target_compile_definitions(CapusynHeadless PRIVATE
    JUCE_WEB_BROWSER=0
    HEADLESS=1
    NO_AUTH=1
)

target_link_libraries(CapusynHeadless
    PUBLIC
        CapusynData
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
