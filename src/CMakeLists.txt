cmake_minimum_required(VERSION 3.17)

project(execute-system-monitor CXX)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  integration-monitors
)
