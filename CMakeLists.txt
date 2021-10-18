cmake_minimum_required(VERSION 3.17)
project(FormalLanguagesPractice_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${CMAKE_SOURCE_DIR}/cmake)

add_executable(FormalLanguagesPractice_1 main.cpp RegexParser.cpp RegexParser.h)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(CodeCoverage)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Tests run_tests.cpp Tests/MaxPrefixTests.cpp Tests/MaxPrefixTests.h RegexParser.cpp)
target_link_libraries(Tests ${GTEST_LIBRARIES} Threads::Threads)

setup_target_for_coverage(coverage_report Tests coverage)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

enable_testing()
