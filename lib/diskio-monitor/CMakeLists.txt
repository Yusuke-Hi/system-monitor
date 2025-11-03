cmake_minimum_required(VERSION 3.17)

project(diskio-monitor CXX)

add_library(${PROJECT_NAME} SHARED
  src/diskio-monitor.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
