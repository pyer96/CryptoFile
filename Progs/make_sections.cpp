#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

/** This demo splits the input file in N sections and stores them.
 * It takes as arguments the name of the target file and the N number of
 * sections
 */

int main(int argc, const char *argv[]) {
  if (argc < 3 || argc > 3) {
    std::cerr << "make_section: invalid argument\n";
    return 1;
  }

  // Open input file
  std::vector<uint8_t> data;
  std::string file_name = argv[1];
  std::ifstream file{file_name, std::ios::binary};
  if (not file.is_open()) {
    std::cerr << "make_section: unable to open the file\n";
    return 1;
  }

  // Find input file size
  file.unsetf(std::ios::skipws);
  file.seekg(0, std::ios::end);
  auto filesize = file.tellg();
  file.seekg(0, std::ios::beg);
  std::cout << "initial file size = " << filesize << '\n';

  // Store file as a vector of uint8_t
  data.reserve(filesize);
  data.insert(data.begin(), std::istream_iterator<uint8_t>(file),
              std::istream_iterator<uint8_t>());

  // We consider the section_number to be always valid ex: "4"
  int section_number = std::atoi(argv[2]);

  /** standard_section_size is the size of the file divided by the
   *  section_number without rounding
   */
  double standard_section_size =
      static_cast<float>(data.size()) / static_cast<float>(section_number);

  // normal_section_size is the size of all the sections but the last one
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
    std::string section_name = file_name + '_' + std::to_string(i + 1);
    file_section.open(section_name, std::fstream::out | std::fstream::binary);
    int section_size;
    if (i == section_number - 1) {
      section_size = last_section_size;
    } else {
      section_size = normal_section_size;
    }

    // file sections are saved as <name>_i
    file_section.write(
        reinterpret_cast<const char *>(&data[normal_section_size * i]),
        section_size);
    std::cout << "section = " << section_name
              << " section size = " << section_size << '\n';
  }
  return 0;
}
