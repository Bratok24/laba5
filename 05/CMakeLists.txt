cmake_minimum_required(VERSION 3.10)
project(physics)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_DIR "C:/msys64/ucrt64/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics QUIET)
endif()

if (NOT SFML_FOUND)
    message(STATUS "SFML not found locally. Fetching from source...")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_executable(physics
        main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp Painter.cpp
        black_box/Application.cpp black_box/View.cpp black_box/PainterImpl.cpp)

target_link_libraries(physics PRIVATE sfml-graphics)

if (WIN32 AND SFML_FOUND)
    add_custom_command(TARGET physics POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "C:/msys64/ucrt64/bin"
            $<TARGET_FILE_DIR:physics>)
endif()

target_compile_options(physics PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )