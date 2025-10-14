cmake_minimum_required(VERSION 3.17)

project(cpu-monitor CXX)

add_library(${PROJECT_NAME} SHARED
  src/cpu-monitor.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
