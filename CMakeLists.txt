cmake_minimum_required(VERSION 2.6)
project(BrainFuck)
add_executable(bf "${PROJECT_SOURCE_DIR}/bf.cc")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
