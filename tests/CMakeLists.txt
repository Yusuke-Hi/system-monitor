include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(cpu_monitor_test cpu_monitor_test.cpp)
target_link_libraries(cpu_monitor_test
  gtest_main
  cpu-monitor
)
add_test(NAME cpu_monitor_test COMMAND cpu_monitor_test)

add_executable(memory_monitor_test memory_monitor_test.cpp)
target_link_libraries(memory_monitor_test
  gtest_main
  memory-monitor
)
add_test(NAME memory_monitor_test COMMAND memory_monitor_test)

add_executable(diskio_monitor_test diskio_monitor_test.cpp)
target_link_libraries(diskio_monitor_test
  gtest_main
  diskio-monitor
)
add_test(NAME diskio_monitor_test COMMAND diskio_monitor_test)
