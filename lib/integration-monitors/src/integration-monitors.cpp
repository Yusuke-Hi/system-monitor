#include "integration-monitors.hpp"

void IntegrationMonitors::StartMonitoring() {
  printf("\033[2J\033[H");

  CPUMonitor cpu_monitor;
  MemoryMonitor memory_monitor;

  bool first{false};

  while (true) {
    printf("\033[H");

    cpu_monitor.Monitor();
    if (!first) {
      first = true;
      continue;
    }
    memory_monitor.Monitor();

    usleep(1000000);
  }
}
