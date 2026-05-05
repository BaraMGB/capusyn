cmake_minimum_required(VERSION 3.15)
project(VitalStandaloneApp LANGUAGES CXX)

# Standalone-specific unity-build source.
set(VITAL_STANDALONE_CPP
    ${CMAKE_SOURCE_DIR}/src/unity_build/standalone.cpp
)

juce_add_gui_app(VitalStandalone
    BUNDLE_ID "audio.vital.standalone"
    VERSION "1.0.6"
    COMPANY_NAME "Matt Tytel"
    COMPANY_WEBSITE "vital.audio"
    COMPANY_EMAIL "matthewtytel@gmail.com"
    COMPANY_COPYRIGHT "Matt Tytel"
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(VitalStandalone)

target_sources(VitalStandalone PRIVATE
    ${VITAL_STANDALONE_CPP}
    $<TARGET_OBJECTS:VitalCore>
    $<TARGET_OBJECTS:VitalGui>
)

target_include_directories(VitalStandalone PRIVATE
    BEFORE
    ${CMAKE_SOURCE_DIR}/src/standalone
)

target_include_directories(VitalStandalone PRIVATE
    ${VITAL_COMMON_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/third_party/JUCE/modules
)

target_compile_definitions(VitalStandalone PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    NO_AUTH=1
)

target_link_libraries(VitalStandalone
    PUBLIC
        VitalData
        ${VITAL_JUCE_SHARED_MODULES}
        CURL::libcurl
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
