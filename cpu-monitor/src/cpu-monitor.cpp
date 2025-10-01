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

  ShowTotalCPUUsage_(line);

  // printf(
  //     "cpu_name: %s\nuser: %zu, nice: %zu, system: %zu, idle: %zu, iowait: "
  //     "%zu, irq: %zu, softirq: %zu\n",
  //     cpu_stat.cpu_name.c_str(), cpu_stat.user, cpu_stat.nice,
  //     cpu_stat.system, cpu_stat.idle, cpu_stat.iowait, cpu_stat.irq,
  //     cpu_stat.softirq);
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
  cpu_stat.user = stoi(line_split.at(1));
  cpu_stat.nice = stoi(line_split.at(2));
  cpu_stat.system = stoi(line_split.at(3));
  cpu_stat.idle = stoi(line_split.at(4));
  cpu_stat.iowait = stoi(line_split.at(5));
  cpu_stat.irq = stoi(line_split.at(6));
  cpu_stat.softirq = stoi(line_split.at(7));

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

void CPUMonitor::ShowTotalCPUUsage_(const std::string &line) {
  cpu_stat_now = GetCPUStat_(line);
  if (time_zero) {
    cpu_stat_prev = cpu_stat_now;
    time_zero = false;
    return;
  }
  // get total
  int total_diff = GetTotalLoad_(cpu_stat_now) - GetTotalLoad_(cpu_stat_prev);
  int idle_diff = cpu_stat_now.idle - cpu_stat_prev.idle;

  double total_cpu_usage = 100 * (total_diff - idle_diff) / (double)total_diff;

  printf("\033[H");
  printf("=== System Monitor ===\n");
  printf("Total CPU Usage: %.2f[%%]\n", total_cpu_usage);
  printf("Press Ctrl+C to exit\n");
  fflush(stdout);

  // update
  cpu_stat_prev = cpu_stat_now;
}

int CPUMonitor::GetTotalLoad_(const CPUStat &cpu_stat) {
  return cpu_stat.user + cpu_stat.nice + cpu_stat.system + cpu_stat.idle +
         cpu_stat.iowait + cpu_stat.irq + cpu_stat.softirq;
}
