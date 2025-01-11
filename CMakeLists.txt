cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Geodify VERSION 1.0.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

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

include("cmake/CPM.cmake")

# Fetch the external-hook-api package
CPMAddPackage("gh:OmgRod/External-Hook-API#master")

# Add your Geode SDK as a subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Link the external-hook-api target to your project using the same style
target_link_libraries(${PROJECT_NAME} PRIVATE external-hook-api)

# Setup Geode module (if applicable)
setup_geode_mod(${PROJECT_NAME})
