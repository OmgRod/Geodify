file(GLOB TOOL_DIRECTORIES
    LIST_DIRECTORIES true
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/tools/*"
)

set(TOOLS)

foreach(TOOL_DIRECTORY ${TOOL_DIRECTORIES})
    if (NOT IS_DIRECTORY "${TOOL_DIRECTORY}")
        continue()
    endif()

    get_filename_component(
        TOOL_NAME
        "${TOOL_DIRECTORY}"
        NAME
    )

    if (TOOL_NAME STREQUAL "external")
        continue()
    endif()

    file(GLOB_RECURSE TOOL_SOURCES
        CONFIGURE_DEPENDS
        "${TOOL_DIRECTORY}/*.cpp"
    )

    if (NOT TOOL_SOURCES)
        continue()
    endif()

    message(STATUS "Found tool: ${TOOL_NAME}")

    add_executable(
        ${TOOL_NAME}
        ${TOOL_SOURCES}
    )

    target_include_directories(
        ${TOOL_NAME}
        PRIVATE
        "${CMAKE_SOURCE_DIR}/tools/external"
    )

    list(APPEND TOOLS ${TOOL_NAME})

    set(TOOL_CONFIGURE_BINARY
        "${CMAKE_BINARY_DIR}/tools/${TOOL_NAME}"
    )

    if (WIN32)
        set(TOOL_CONFIGURE_BINARY
            "${TOOL_CONFIGURE_BINARY}.exe"
        )
    endif()

    file(MAKE_DIRECTORY
        "${CMAKE_BINARY_DIR}/tools"
    )

    execute_process(
        COMMAND
            ${CMAKE_CXX_COMPILER}
            -std=c++23
            "-I${CMAKE_SOURCE_DIR}/tools/external"
            ${TOOL_SOURCES}
            -o
            "${TOOL_CONFIGURE_BINARY}"

        WORKING_DIRECTORY
            "${CMAKE_SOURCE_DIR}"

        RESULT_VARIABLE
            TOOL_COMPILE_RESULT

        OUTPUT_VARIABLE
            TOOL_COMPILE_OUTPUT

        ERROR_VARIABLE
            TOOL_COMPILE_ERROR
    )

    if (NOT TOOL_COMPILE_RESULT EQUAL 0)
        message(
            FATAL_ERROR
            "Failed to compile tool ${TOOL_NAME}:\n${TOOL_COMPILE_ERROR}"
        )
    endif()

    message(STATUS "Running tool: ${TOOL_NAME}")

    execute_process(
        COMMAND
            "${TOOL_CONFIGURE_BINARY}"

        WORKING_DIRECTORY
            "${CMAKE_SOURCE_DIR}"

        RESULT_VARIABLE
            TOOL_RUN_RESULT

        OUTPUT_VARIABLE
            TOOL_RUN_OUTPUT

        ERROR_VARIABLE
            TOOL_RUN_ERROR
    )

    if (NOT TOOL_RUN_RESULT EQUAL 0)
        message(
            FATAL_ERROR
            "Failed to run tool ${TOOL_NAME}:\n${TOOL_RUN_ERROR}"
        )
    endif()

    if (NOT TOOL_RUN_OUTPUT STREQUAL "")
        message(STATUS "${TOOL_RUN_OUTPUT}")
    endif()
endforeach()
