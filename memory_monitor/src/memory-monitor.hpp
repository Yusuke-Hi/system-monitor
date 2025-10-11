#ifndef MEMORY_MONITOR_
#define MEMORY_MONITOR_

#include <unistd.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class MemoryMonitor {
 public:
  MemoryMonitor() = default;
  ~MemoryMonitor() = default;
  void Monitor();

 private:
  void ShowMemoryUsage();
  void StoreMemoryInfo();
  void ShowMainParts();
  float CaluculateUsage();
  void SaveToMap(const std::string& line);

  const std::string path{"/proc/meminfo"};
  std::unordered_map<std::string, long long> meminfo_map{};
};

#endif
