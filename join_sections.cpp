#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <cmath>
#include <cstring>

int main(int argc, const char *argv[])
{
  std::vector<uint8_t> data;
  for (int i = 1; i < 8; ++i){
    std::cerr<<argv[i]<<'\n';
    std::ifstream section{argv[i], std::ios::binary};
    section.unsetf(std::ios::skipws);
    section.seekg(0, std::ios::end);
    auto section_size = section.tellg();
    section.seekg(0, std::ios::beg);
    data.reserve(data.size() + section_size);
    data.insert(data.end(), std::istream_iterator<uint8_t>(section), std::istream_iterator<uint8_t>());
    std::cerr<< "section_size = "<<section_size<< "\ndata.size() = "<< data.size()<< "\n\n";
    section.close();
  }
  std::ofstream file_copy;
  file_copy.open("elefant_copy.jpg", std::fstream::out | std::fstream::binary);
  file_copy.write(
      reinterpret_cast<const char * >(data.data()), data.size());
}
