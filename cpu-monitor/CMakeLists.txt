cmake_minimum_required(VERSION 3.17)

project(cpu-monitor CXX)

add_executable(cpu-monitor
  src/main.cpp
  src/cpu-monitor.cpp
)
