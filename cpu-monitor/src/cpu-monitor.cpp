#include "cpu-monitor.hpp"

CPUMonitor::CPUMonitor() {}
CPUMonitor::~CPUMonitor() {}

void CPUMonitor::Monitor() {
  printf("\033[2J\033[H");
  while (true) {
    ShowCPULoad_();
    usleep(1000000);
  }
}

void CPUMonitor::ShowCPULoad_() {
  std::vector<std::string> lines = GetLines_();

  ShowTotalCPUUsage_(lines);
}

std::vector<std::string> CPUMonitor::GetLines_() {
  std::ifstream file(path.c_str());

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    if (line.at(0) == 'c' && line.at(1) == 'p' && line.at(2) == 'u') {
      lines.emplace_back(line);
    }
  }

  return lines;
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
        // std::cout << tmp << std::endl;
        line_split.emplace_back(tmp);
      }
      tmp = "";
      continue;
    }
    tmp += c;
  }

  return line_split;
}

void CPUMonitor::ShowTotalCPUUsage_(const std::vector<std::string> &lines) {
  std::vector<CPUStat> cpu_stat_now_vector;
  for (auto line : lines) {
    cpu_stat_now_vector.emplace_back(GetCPUStat_(line));
  }

  if (time_zero) {
    for (auto cpu_stat : cpu_stat_now_vector) {
      cpu_stat_prev_vector.emplace_back(cpu_stat);
    }
    time_zero = false;
    return;
  }

  printf("\033[H");
  printf("=== System Monitor ===\n");

  // get total
  for (size_t i = 0; i < cpu_stat_now_vector.size(); ++i) {
    int total_diff = GetTotalLoad_(cpu_stat_now_vector.at(i)) -
                     GetTotalLoad_(cpu_stat_prev_vector.at(i));
    int idle_diff =
        cpu_stat_now_vector.at(i).idle - cpu_stat_prev_vector.at(i).idle;

    double cpu_usage = 100 * (total_diff - idle_diff) / (double)total_diff;

    printf("%s: %.2f[%%]\n", cpu_stat_now_vector.at(i).cpu_name.c_str(),
           cpu_usage);
  }

  fflush(stdout);

  // update
  for (size_t i = 0; i < cpu_stat_now_vector.size(); ++i) {
    cpu_stat_prev_vector.at(i) = cpu_stat_now_vector.at(i);
  }

  printf("Press Ctrl+C to exit\n");
}

int CPUMonitor::GetTotalLoad_(const CPUStat &cpu_stat) {
  return cpu_stat.user + cpu_stat.nice + cpu_stat.system + cpu_stat.idle +
         cpu_stat.iowait + cpu_stat.irq + cpu_stat.softirq;
}
