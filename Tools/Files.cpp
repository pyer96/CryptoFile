#include "Tools/Files.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

namespace tools {
int write_2_file(const std::vector<std::uint8_t> &data,
                 const std::string file_path) {
  std::ofstream os;
  try {
    os.open(file_path, std::ofstream::out | std::fstream::binary);
    os.write(reinterpret_cast<const char *>(data.data()), data.size());
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}

int read_from_file(std::vector<std::uint8_t> &data,
                   const std::string file_path) {
  std::ifstream file{file_path, std::ios::binary};
  if (not file.is_open()) {
    std::cerr << "Error: file not found\n";
    return 1;
  }
  file.unsetf(std::ios::skipws);
  file.seekg(0, std::ios::end);
  data.reserve(file.tellg());
  file.seekg(0, std::ios::beg);
  data.insert(data.begin(), std::istream_iterator<uint8_t>(file),
              std::istream_iterator<uint8_t>());
  file.close();
  return 0;
}
} // namespace tools
