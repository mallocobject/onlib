cmake_minimum_required(VERSION 3.22)

project(static_system)

set(CMAKE_C_STANDARD 17)

aux_source_directory(. C_SOURCES)

add_executable(static_system ${C_SOURCES})