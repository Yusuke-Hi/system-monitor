#include "integration-monitors.hpp"

void IntegrationMonitors::StartMonitoring() {
  printf("\033[2J\033[H");

  CPUMonitor cpu_monitor;
  MemoryMonitor memory_monitor;
  DiskIOMonitor diskio_monitor;

  bool first{true};

  while (true) {
    printf("\033[H");

    cpu_monitor.Monitor();
    if (first) {
      first = false;
      continue;
    }
    memory_monitor.Monitor();
    diskio_monitor.Monitor();

    usleep(1000000);
  }
}
