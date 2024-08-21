cmake_minimum_required(VERSION 3.4.1)

project(native-lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(native-lib SHARED native-lib.cc)

find_library(log-lib log)

target_link_libraries(native-lib ${log-lib})
