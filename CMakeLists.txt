cmake_minimum_required(VERSION 3.15)
project(rhythmgame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/external/raylib")
set(RTMIDI_DIR "${CMAKE_SOURCE_DIR}/external/rtmidi")

add_subdirectory(${RAYLIB_DIR} raylib EXCLUDE_FROM_ALL)


add_library(rtmidi STATIC
    ${RTMIDI_DIR}/RtMidi.cpp
)
target_include_directories(rtmidi PUBLIC ${RTMIDI_DIR})

if(WIN32)
    target_compile_definitions(rtmidi PRIVATE __WINDOWS_MM__)
    target_link_libraries(rtmidi PRIVATE winmm)
elseif(UNIX)
    target_compile_definitions(rtmidi PRIVATE __LINUX_ALSA__)
    target_link_libraries(rtmidi PRIVATE asound pthread)
endif()

add_executable(pre4kz src/main.cpp)

target_link_libraries(pre4kz PRIVATE raylib rtmidi)

if(WIN32)
    target_link_libraries(pre4kz PRIVATE opengl32 gdi32 winmm)
else()
    target_link_libraries(pre4kz PRIVATE GL m pthread dl rt X11)
endif()

target_include_directories(pre4kz PRIVATE ${RAYLIB_DIR}/src)