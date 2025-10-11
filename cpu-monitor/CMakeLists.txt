cmake_minimum_required(VERSION 3.17)

project(cpu-monitor CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/cpu-monitor.cpp
)
