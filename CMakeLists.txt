cmake_minimum_required(VERSION 3.21)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(GENERATE_TAGS_SCRIPT ${CMAKE_SOURCE_DIR}/generate_tags.py)

execute_process(
    COMMAND ${Python3_EXECUTABLE} ${GENERATE_TAGS_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GENERATE_TAGS_RESULT
)

if (NOT GENERATE_TAGS_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to execute generate_tags.py. Please check the script.")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Geodify VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

if (DEFINED ENV{GITHUB_ACTIONS})
    message("Github Actions Build")
    add_definitions(-DGITHUB_ACTIONS)
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
