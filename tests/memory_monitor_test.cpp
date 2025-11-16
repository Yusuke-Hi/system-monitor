#include <gtest/gtest.h>

#include "memory-monitor.hpp"

TEST(MemoryMonitorTest, Normal) {
  MemoryMonitor monitor;
  EXPECT_NO_THROW(monitor.Monitor());
}
