#ifndef DISKIO_MONITOR_
#define DISKIO_MONITOR_

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct DiskIOInfo {
  uint32_t major;
  uint32_t minor;
  std::string name;
  uint32_t reads;
  uint32_t reads_merged;
  unsigned long long sectors_read;
  uint32_t time_reading;
  uint32_t writes;
  uint32_t writes_merged;
  unsigned long long sectors_written;
  uint32_t time_writing;
};

class DiskIOMonitor {
 public:
  DiskIOMonitor() = default;
  ~DiskIOMonitor() = default;

  void Monitor();

 private:
  std::vector<std::string> GetLines_();
  DiskIOInfo GetDiskIOInfo_(const std::string& line);
  std::vector<std::string> SplitLine_(const std::string& line);
  void ShowDiskIOInfo();

  const std::string path{"/proc/diskstats"};
  bool first_time{true};
  std::vector<std::string> target_names{"sda", "sdb", "sdc", "sdd"};
  std::unordered_map<std::string, DiskIOInfo> diskio_info_prev_map{};
  std::unordered_map<std::string, DiskIOInfo> diskio_info_current_map{};
};

#endif
