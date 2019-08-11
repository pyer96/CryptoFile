#ifndef __Aont__
#define __Aont__

#include "Section.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace aont {
class Aont {
private:
  std::unique_ptr<std::vector<std::uint8_t>> m_data;
  std::size_t m_sections_number;
  std::vector<Section> m_sections;

public:
  Aont(std::unique_ptr<std::vector<uint8_t>> data, std::size_t sections);
  void print_sections() {
    for (const auto &sec : m_sections) {
      sec.print_section_data();
      std::cout << '\n';
      sec.print_transformed_data();
      std::cout << '\n';
      sec.print_transformed_data();
      //  std::cout << "sha256 : " << sec.get_hash().data();
      //  std::cout << "\n\n";
    }
  }
};

} // namespace aont
#endif
