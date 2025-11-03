#ifndef INTEGRATION_MONITORS_
#define INTEGRATION_MONITORS_

#include "cpu-monitor.hpp"
#include "diskio-monitor.hpp"
#include "memory-monitor.hpp"

class IntegrationMonitors {
 public:
  IntegrationMonitors() = default;
  ~IntegrationMonitors() = default;

  void StartMonitoring();
};

#endif
