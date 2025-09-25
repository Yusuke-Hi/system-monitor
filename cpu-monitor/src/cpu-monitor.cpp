#include "cpu-monitor.hpp"

CPUMonitor::CPUMonitor() {}
CPUMonitor::~CPUMonitor() {}

void CPUMonitor::Monitor() {
  while (true) {
    ShowCPULoad_();
    usleep(1000000);
  }
}

void CPUMonitor::ShowCPULoad_() {
  std::string line = GetFirstLine_();

  CPUStat cpu_stat = GetCPUStat_(line);
}

std::string CPUMonitor::GetFirstLine_() {
  std::ifstream file(path.c_str());
  std::string line;

  std::getline(file, line);
  return line;
}

CPUStat CPUMonitor::GetCPUStat_(const std::string &line) {
  std::vector<std::string> line_split = SplitLine(line);

  CPUStat cpu_stat{};
  cpu_stat.cpu_name = line_split.at(0);
  cpu_stat.user = static<size_t>(line_split.at(1));
}

std::vector<std::string> SplitLine(const std::string &line) {
  std::vector<std::string> line_split;
  std::string tmp{};
  for (auto c : line) {
    tmp += c;
    if (c == ' ') {
      if (tmp != "") {
        line_split.emplace_back(tmp);
      }
      tmp = "";
      continue;
    }
  }

  return line_split;
}
