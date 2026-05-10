cmake_minimum_required(VERSION 3.15)
project(CapusynTests LANGUAGES CXX)

# The aggregate test files include the individual *_test.cpp files directly.
# Do not compile those leaf sources separately, or the linker sees duplicates.
set(CAPUSYN_TESTS_CPP
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
    ${CMAKE_SOURCE_DIR}/tests/interface_tests.cpp
    ${CMAKE_SOURCE_DIR}/tests/stress_tests.cpp
    ${CMAKE_SOURCE_DIR}/tests/synthesis_tests.cpp
)

juce_add_console_app(CapusynTests
    BUNDLE_ID "io.github.BaraMGB.capusyn.tests"
    VERSION "1.0.6"
    COMPANY_NAME "Capusyn Project"
    COMPANY_WEBSITE "https://github.com/BaraMGB/capusyn"
    COMPANY_EMAIL "opensource@capusyn.invalid"
    COMPANY_COPYRIGHT "Capusyn Project"
    CPP_LANGUAGE_STANDARD "17"
)

juce_generate_juce_header(CapusynTests)

target_sources(CapusynTests PRIVATE
    ${CAPUSYN_TESTS_CPP}
    $<TARGET_OBJECTS:CapusynCore>
    $<TARGET_OBJECTS:CapusynGui>
)

target_include_directories(CapusynTests PRIVATE
    ${CAPUSYN_COMMON_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/tests/synthesis
)

target_compile_definitions(CapusynTests PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    NO_AUTH=1
)

target_link_libraries(CapusynTests
    PUBLIC
        CapusynData
        ${CAPUSYN_JUCE_SHARED_MODULES}
        CURL::libcurl
        Threads::Threads
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
