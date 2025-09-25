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

  printf(
      "cpu_name: %s\nuser: %zu, nice: %zu, system: %zu, idle: %zu, iowait: "
      "%zu, irq: %zu, softirq: %zu\n",
      cpu_stat.cpu_name.c_str(), cpu_stat.user, cpu_stat.nice, cpu_stat.system,
      cpu_stat.idle, cpu_stat.iowait, cpu_stat.irq, cpu_stat.softirq);
}

std::string CPUMonitor::GetFirstLine_() {
  std::ifstream file(path.c_str());
  std::string line;

  std::getline(file, line);
  return line;
}

CPUStat CPUMonitor::GetCPUStat_(const std::string &line) {
  std::vector<std::string> line_split = SplitLine_(line);

  CPUStat cpu_stat{};
  cpu_stat.cpu_name = line_split.at(0);
  cpu_stat.user = static_cast<size_t>(stoi(line_split.at(1)));
  cpu_stat.nice = static_cast<size_t>(stoi(line_split.at(2)));
  cpu_stat.system = static_cast<size_t>(stoi(line_split.at(3)));
  cpu_stat.idle = static_cast<size_t>(stoi(line_split.at(4)));
  cpu_stat.iowait = static_cast<size_t>(stoi(line_split.at(5)));
  cpu_stat.irq = static_cast<size_t>(stoi(line_split.at(6)));
  cpu_stat.softirq = static_cast<size_t>(stoi(line_split.at(7)));

  return cpu_stat;
}

std::vector<std::string> CPUMonitor::SplitLine_(const std::string &line) {
  std::vector<std::string> line_split;
  std::string tmp = "";
  for (auto c : line) {
    if (c == ' ') {
      if (tmp != "") {
        line_split.emplace_back(tmp);
      }
      tmp = "";
      continue;
    }
    tmp += c;
  }

  return line_split;
}
