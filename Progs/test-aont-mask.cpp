#include "CryptoFile/Aont/Section.hpp"
#include "Tools/Files.hpp"
#include <boost/filesystem.hpp>
#include <memory>

typedef std::function<void(std::vector<std::unique_ptr<cryptofile::aont::Section>> &)>
    callback_t;

std::vector<std::unique_ptr<cryptofile::aont::Section>>
aont_mask(std::vector<std::uint8_t> &data, std::size_t sections_number,
          callback_t callback) {
  std::vector<std::unique_ptr<cryptofile::aont::Section>> sections;
  sections.reserve(sections_number);
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock key(
      CryptoPP::AES::MAX_KEYLENGTH);           // 32 bytes (256 bits)
  CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; // 16 bytes (128 bits)
  prng.GenerateBlock(key, key.size());
  prng.GenerateBlock(iv, sizeof(iv));

  double standard_section_size =
      static_cast<float>(data.size()) / static_cast<float>(sections_number);
  auto normal_section_size = std::ceil(standard_section_size);
  auto last_section_size =
      normal_section_size -
      ((normal_section_size * sections_number) - data.size());

  auto encrypted_key = std::vector<std::uint8_t>(&(key.BytePtr()[0]),
                                                 &(key.BytePtr()[key.size()]));
  for (std::size_t i = 0; i < sections_number; ++i) {
    auto section_size =
        i < sections_number - 1 ? normal_section_size : last_section_size;
    auto encrypt_section = std::make_unique<cryptofile::aont::EncryptSection>(
        gsl::span<std::uint8_t>(
            &(data.data()[static_cast<std::size_t>(normal_section_size) * i]),
            section_size),
        key);
    auto &hash = encrypt_section->get_hash();
    CryptoPP::xorbuf(encrypted_key.data(), encrypted_key.data(), hash.data(),
                     hash.size());
    sections.emplace_back(std::move(encrypt_section));
  }
  sections.emplace_back(std::make_unique<cryptofile::aont::LastSection>(encrypted_key));
  callback(sections);
  return sections;
}

int main(int argc, const char *argv[]) {
  if (argc != 3) {
    std::cout << "use: ./a.out <file_path> <section_number>\n";
    return 1;
  }
  std::size_t sections_number = std::atoi(argv[2]);
  std::vector<std::uint8_t> data;
  tools::read_from_file(data, argv[1]);
  auto sections =
      aont_mask(data, sections_number,
                [=](std::vector<std::unique_ptr<cryptofile::aont::Section>> &sections) {
                  boost::filesystem::path CryptoFile_base(
                      boost::filesystem::current_path());

                  int i = 0;
                  for (const auto &sec : sections) {
                    std::string path = CryptoFile_base.generic_string() +
                                       "/Temp/outsection_" + std::to_string(i);
                    std::cout << path << '\n';
                    i++;
                    tools::write_2_file(sec->get_data(), path);
                  }
                });
  return 0;
}
