#include <gtest/gtest.h>

#include "diskio-monitor.hpp"

TEST(DiskIOMonitorTest, Normal) {
  DiskIOMonitor monitor;
  EXPECT_NO_THROW(monitor.Monitor());
}
