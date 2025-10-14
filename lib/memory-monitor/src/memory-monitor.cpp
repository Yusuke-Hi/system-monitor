#include "memory-monitor.hpp"

void MemoryMonitor::Monitor() { ShowMemoryUsage(); }

void MemoryMonitor::ShowMemoryUsage() {
  StoreMemoryInfo();
  ShowMainParts();
}

void MemoryMonitor::StoreMemoryInfo() {
  std::ifstream file(path.c_str());

  std::string line;
  while (std::getline(file, line)) {
    SaveToMap(line);
  }
}

void MemoryMonitor::ShowMainParts() {
  float usage = 100.0 *
                (meminfo_map.at("MemTotal") - meminfo_map.at("MemAvailable")) /
                meminfo_map.at("MemTotal");

  printf("=== Memory Monitor ===\n");

  printf(
      "Total:          %lld kB\n"
      "Available:      %lld kB\n"
      "Free:           %lld kB\n"
      "Used:           %lld kB\n"
      "Usage:          %.1f %%\n\n"
      "Buffers:        %lld kB\n"
      "Cached:         %lld kB\n"
      "Swap Total:     %lld kB\n"
      "Swap Free:      %lld kB\n",
      meminfo_map.at("MemTotal"), meminfo_map.at("MemAvailable"),
      meminfo_map.at("MemFree"),
      meminfo_map.at("MemTotal") - meminfo_map.at("MemAvailable"), usage,
      meminfo_map.at("Buffers"), meminfo_map.at("Cached"),
      meminfo_map.at("SwapTotal"), meminfo_map.at("SwapFree"));
}

void MemoryMonitor::SaveToMap(const std::string& line) {
  std::string item{}, usage{};
  bool item_flg{true};
  for (auto c : line) {
    if (c == ':' || c == ' ') {
      item_flg = false;
      continue;
    }
    if (!item_flg && c == 'k') {
      break;
    }

    if (item_flg) {
      item += c;
    } else {
      usage += c;
    }
  }

  meminfo_map.insert_or_assign(item, stoll(usage));
}
