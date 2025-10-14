cmake_minimum_required(VERSION 3.17)

project(integration-monitors)

add_library(${PROJECT_NAME} SHARED
  src/integration-monitors.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
  cpu-monitor
  memory-monitor
)
