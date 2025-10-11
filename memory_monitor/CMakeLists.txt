cmake_minimum_required(VERSION 3.17)

project(memory-monitor CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/memory-monitor.cpp
)
