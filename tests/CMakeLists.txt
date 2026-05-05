cmake_minimum_required(VERSION 3.15)
project(VitalTests LANGUAGES CXX)

# The aggregate test files include the individual *_test.cpp files directly.
# Do not compile those leaf sources separately, or the linker sees duplicates.
set(VITAL_TESTS_CPP
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
    ${CMAKE_SOURCE_DIR}/tests/interface_tests.cpp
    ${CMAKE_SOURCE_DIR}/tests/stress_tests.cpp
    ${CMAKE_SOURCE_DIR}/tests/synthesis_tests.cpp
)

juce_add_console_app(VitalTests
    BUNDLE_ID "audio.vital.tests"
    VERSION "1.0.6"
    COMPANY_NAME "Matt Tytel"
    COMPANY_WEBSITE "vital.audio"
    COMPANY_EMAIL "matthewtytel@gmail.com"
    COMPANY_COPYRIGHT "Matt Tytel"
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(VitalTests)

target_sources(VitalTests PRIVATE
    ${VITAL_TESTS_CPP}
    $<TARGET_OBJECTS:VitalCore>
    $<TARGET_OBJECTS:VitalGui>
)

target_include_directories(VitalTests PRIVATE
    ${VITAL_COMMON_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/tests/synthesis
)

target_compile_definitions(VitalTests PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    NO_AUTH=1
)

target_link_libraries(VitalTests
    PUBLIC
        VitalData
        ${VITAL_JUCE_SHARED_MODULES}
        CURL::libcurl
        Threads::Threads
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
