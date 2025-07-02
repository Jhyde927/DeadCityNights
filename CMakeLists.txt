cmake_minimum_required(VERSION 3.15)
project(AdventureGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(include external/raygui src)

find_package(raylib REQUIRED)

add_executable(AdventureGame ${SOURCES})

target_link_libraries(AdventureGame PRIVATE raylib)

if(WIN32)
    target_compile_definitions(AdventureGame PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(AdventureGame PRIVATE PLATFORM_LINUX)
endif()

add_custom_command(TARGET AdventureGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:AdventureGame>/assets)

