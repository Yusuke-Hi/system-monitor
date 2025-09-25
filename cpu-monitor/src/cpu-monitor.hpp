#include <unistd.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct CPUStat {
  std::string cpu_name;
  size_t user;
  size_t nice;
  size_t system;
  size_t idle;
  size_t iowait;
  size_t irq;
  size_t softirq;
};

class CPUMonitor {
 public:
  CPUMonitor();
  ~CPUMonitor();

  void Monitor();

 private:
  void ShowCPULoad_();
  std::string GetFirstLine_();
  CPUStat GetCPUStat_(const std::string &line);
  std::vector<std::string> SplitLine_(const std::string &line);

  // variables
  const std::string path{"/proc/stat"};
};
