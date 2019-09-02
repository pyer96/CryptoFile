#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

/** This demo program takes as argument the name of the output file the file
 * sections.
 * It join the file sections as a unique file and save it with the specified
 * output name
 */

int main(int argc, const char *argv[]) {
  // vector of bytes of the original size
  std::vector<uint8_t> data;

  /** write the sections in the vector.
   * Note: the first is reserved for the name of the ouput file
   */
  for (int i = 2; i < argc; ++i) {
    std::cerr << argv[i] << '\n';

    // open the section as a stream of bytes
    std::ifstream section{argv[i], std::ios::binary};

    // get the section's size
    section.unsetf(std::ios::skipws);
    section.seekg(0, std::ios::end);
    auto section_size = section.tellg();
    section.seekg(0, std::ios::beg);

    data.reserve(data.size() + section_size);
    data.insert(data.end(), std::istream_iterator<uint8_t>(section),
                std::istream_iterator<uint8_t>());
    std::cout << "section = " << argv[i] << '\n';
    section.close();
  }

  // save the final file
  std::ofstream file_copy;
  file_copy.open(argv[1], std::fstream::out | std::fstream::binary);
  file_copy.write(reinterpret_cast<const char *>(data.data()), data.size());
}
