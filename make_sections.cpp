#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <cmath>
#include <cstring>

int main(int argc, const char *argv[])
{
  std::vector<uint8_t> data;
  std::ifstream file{"elefante.jpg", std::ios::binary};
  if (not file.is_open()) {
    std::cerr<<"file closed\n";
  } else {
    file.unsetf(std::ios::skipws);
    file.seekg(0, std::ios::end);
    // std::streampos
    auto filesize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::cerr << filesize << '\n';
    data.reserve(filesize);
    data.insert(data.begin(), std::istream_iterator<uint8_t>(file),
        std::istream_iterator<uint8_t>());
    int section_number = 7;
    double standard_section_size =
      static_cast<float>(data.size()) / static_cast<float>(section_number);
    auto normal_section_size = std::ceil(standard_section_size);
    auto last_section_size =
      normal_section_size -
      ((normal_section_size * section_number) - data.size());
    std::cerr << "data.size() = " << data.size()
      << "\nstandard_section_size = " << standard_section_size
      << "\nnormal_section_size = " << normal_section_size
      << "\nlast_section_size = " << last_section_size << '\n';
    for (int i = 0; i < section_number; ++i) {
      std::ofstream file_section;
      std::string ind(1, i + 49);
      char elefant[10] = "elefant_";
      auto name_section = std::strcat(elefant, ind.c_str());
      file_section.open(name_section, std::fstream::out | std::fstream::binary);
      int section_size;
      auto is_last = false;
      if (i == section_number - 1) {
        is_last = true;
        section_size = last_section_size;
      } else {
        section_size = normal_section_size;
      }
      file_section.write(
          reinterpret_cast<const char *>(&data[normal_section_size * i]),
          is_last ? last_section_size : normal_section_size);
    }
  }
  return 0;
}
