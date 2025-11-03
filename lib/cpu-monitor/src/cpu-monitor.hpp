#ifndef CPU_MONITOR_
#define CPU_MONITOR_

#include <unistd.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct CPUStat {
  std::string cpu_name;
  int user;
  int nice;
  int system;
  int idle;
  int iowait;
  int irq;
  int softirq;
};

class CPUMonitor {
 public:
  CPUMonitor() = default;
  ~CPUMonitor() = default;

  void Monitor();

 private:
  std::vector<std::string> GetLines_();
  CPUStat GetCPUStat_(const std::string& line);
  std::vector<std::string> SplitLine_(const std::string& line);

  void ShowTotalCPUUsage_(const std::vector<std::string>& line);
  int GetTotalLoad_(const CPUStat& cpu_stat);

  // variables
  const std::string path{"/proc/stat"};
  bool first_time{true};
  std::vector<CPUStat> cpu_stat_current_vector{};
  std::vector<CPUStat> cpu_stat_prev_vector{};
};

#endif
