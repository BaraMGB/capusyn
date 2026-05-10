cmake_minimum_required(VERSION 3.15)
project(CapusynStandaloneApp LANGUAGES CXX)

# Standalone-specific unity-build source.
set(CAPUSYN_STANDALONE_CPP
    ${CMAKE_SOURCE_DIR}/src/unity_build/standalone.cpp
)

juce_add_gui_app(CapusynStandalone
    BUNDLE_ID "io.github.BaraMGB.capusyn.standalone"
    VERSION "1.0.6"
    COMPANY_NAME "Capusyn Project"
    COMPANY_WEBSITE "https://github.com/BaraMGB/capusyn"
    COMPANY_EMAIL "opensource@capusyn.invalid"
    COMPANY_COPYRIGHT "Capusyn Project"
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(CapusynStandalone)

target_sources(CapusynStandalone PRIVATE
    ${CAPUSYN_STANDALONE_CPP}
    $<TARGET_OBJECTS:CapusynCore>
    $<TARGET_OBJECTS:CapusynGui>
)

target_include_directories(CapusynStandalone PRIVATE
    BEFORE
    ${CMAKE_SOURCE_DIR}/src/standalone
)

target_include_directories(CapusynStandalone PRIVATE
    ${CAPUSYN_COMMON_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/third_party/JUCE/modules
)

target_compile_definitions(CapusynStandalone PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    NO_AUTH=1
)

target_link_libraries(CapusynStandalone
    PUBLIC
        CapusynData
        ${CAPUSYN_JUCE_SHARED_MODULES}
        CURL::libcurl
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
