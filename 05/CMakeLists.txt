cmake_minimum_required(VERSION 3.10)
project(physics)

set(CMAKE_CXX_STANDARD 17)

# Указываем путь к SFML из MSYS2 UCRT64
set(SFML_DIR "C:/msys64/ucrt64/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED COMPONENTS graphics)

if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_executable(physics
        main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp Painter.cpp
        black_box/Application.cpp black_box/View.cpp black_box/PainterImpl.cpp)

target_link_libraries(physics PRIVATE sfml-graphics)

# ВОТ ЭТОТ БЛОК НУЖЕН, ЧТОБЫ СКОПИРОВАТЬ DLL ИЗ MSYS2 В ПАПКУ СБОРКИ
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