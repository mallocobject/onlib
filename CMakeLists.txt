cmake_minimum_required(VERSION 3.22)

project(onlib)

set(CMAKE_C_STANDARD 17)

aux_source_directory(. C_SOURCES)

aux_source_directory(src/ C_SOURCES)

add_executable(onlib ${C_SOURCES})