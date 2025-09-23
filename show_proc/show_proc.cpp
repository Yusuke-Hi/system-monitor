#include <fstream>
#include <iostream>
#include <string>

void show_file(const char* path);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments.", argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    show_file(argv[i]);
  }
}

void show_file(const char* path) {
  printf("%s\n", path);
  std::ifstream file(path);
  std::string line;

  while (std::getline(file, line)) {
    std::cout << line << std::endl;
  }

  printf("------------------------------------------\n");
}
