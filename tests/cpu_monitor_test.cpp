#include <gtest/gtest.h>

#include "cpu-monitor.hpp"

TEST(CPUMonitorTest, Normal) {
  CPUMonitor monitor;
  EXPECT_NO_THROW(monitor.Monitor());
}
