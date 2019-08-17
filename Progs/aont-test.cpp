#include "CryptoFile/Aont/Section.hpp"
#include "Tools/Files.hpp"

int main(int argc, const char *argv[]) {
  if (argc != 3) {
    std::cout << "use: ./a.out <file_path> <section_number>\n";
    return 1;
  }
  std::size_t sections_number = std::atoi(argv[2]);
  std::vector<std::uint8_t> data;
  tools::read_from_file(data, argv[1]);
  auto ptr = std::make_unique<std::vector<std::uint8_t>>(std::move(data));
  auto aont_trans = aont::Aont{std::move(ptr), sections_number};
  aont_trans.print_sections();
  return 0;
}
