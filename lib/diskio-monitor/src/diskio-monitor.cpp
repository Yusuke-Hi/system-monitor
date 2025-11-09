#include "diskio-monitor.hpp"

constexpr uint32_t BytesInSector{512};
constexpr double OneKiloByte{1024.0};

void DiskIOMonitor::Monitor() {
  std::vector<std::string> lines = GetLines_();
  for (auto line : lines) {
    diskio_info_current_vector.push_back(GetDiskIOInfo_(line));
  }

  if (first_time) {
    diskio_info_prev_vector = std::move(diskio_info_current_vector);
    first_time = false;
    return;
  }

  printf("=== DiskIO Monitor ===\n");

  for (int i = 0; i < diskio_info_current_vector.size(); ++i) {
    for (auto target_name : target_names) {
      if (diskio_info_current_vector.at(i).name == target_name) {
        int sectors_read_diff = diskio_info_current_vector.at(i).sectors_read -
                                diskio_info_prev_vector.at(i).sectors_read;
        int sectors_written_diff =
            diskio_info_current_vector.at(i).sectors_written -
            diskio_info_prev_vector.at(i).sectors_written;

        long long bytes_read = sectors_read_diff * BytesInSector;
        long long bytes_written = sectors_written_diff * BytesInSector;

        double read_kb_per_sec = bytes_read / OneKiloByte;
        double written_kb_per_sec = bytes_written / OneKiloByte;
        printf("%s: Read: %f KB/s, Write: %f KB/s\033[K\n",
               diskio_info_current_vector.at(i).name.c_str(), read_kb_per_sec,
               written_kb_per_sec);
      }
    }
  }

  diskio_info_prev_vector = std::move(diskio_info_current_vector);
}

std::vector<std::string> DiskIOMonitor::GetLines_() {
  std::ifstream file(path.c_str());

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.emplace_back(line);
  }

  return lines;
}

DiskIOInfo DiskIOMonitor::GetDiskIOInfo_(const std::string& line) {
  std::vector<std::string> line_split = SplitLine_(line);

  DiskIOInfo diskio_info{};
  diskio_info.major = stoi(line_split.at(0));
  diskio_info.minor = stoi(line_split.at(1));
  diskio_info.name = line_split.at(2);
  diskio_info.reads = stoi(line_split.at(3));
  diskio_info.reads_merged = stoi(line_split.at(4));
  diskio_info.sectors_read = stoll(line_split.at(5));
  diskio_info.time_reading = stoi(line_split.at(6));
  diskio_info.writes = stoi(line_split.at(7));
  diskio_info.writes_merged = stoi(line_split.at(8));
  diskio_info.sectors_written = stoll(line_split.at(9));
  diskio_info.time_writing = stoi(line_split.at(10));

  return diskio_info;
}

std::vector<std::string> DiskIOMonitor::SplitLine_(const std::string& line) {
  std::vector<std::string> line_split{};
  std::string tmp{};
  for (auto c : line) {
    if (c == ' ') {
      if (tmp != "") {
        line_split.push_back(tmp);
        tmp = "";
      }
    } else {
      tmp += c;
    }
  }

  return line_split;
}
