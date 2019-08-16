#include "CryptoFile/Aont/Section.hpp"
#include "Tools/Files.hpp"
#include <boost/filesystem.hpp>

typedef std::function<void(std::vector<std::uint8_t> &)> callback_t;

void aont_restore(std::vector<std::vector<std::uint8_t>> &sections_data,
                  callback_t callback) {
  std::vector<std::unique_ptr<aont::DecryptSection>> sections;
  sections.resize(sections_data.size() - 1);
  std::vector<std::uint8_t> decrypted_key( //?
      &(sections_data.back().data()[0]),
      &(sections_data.back().data()[sections_data.back().size()]));

  for (/*const*/ auto &sec : sections_data) {
    if (sec != sections_data.back()) {
      auto section_data = gsl::span<std::uint8_t>(&(sec.data()[0]), sec.size());
      auto decrypt_section =
          std::make_unique<aont::DecryptSection>(std::move(section_data));
      const auto &hash = decrypt_section->get_hash();
      CryptoPP::xorbuf(decrypted_key.data(), decrypted_key.data(), hash.data(),
                       hash.size());
      sections.emplace_back(std::move(decrypt_section));
    }
  }
  std::vector<std::uint8_t> plain_text;
  CryptoPP::SecByteBlock key(decrypted_key.data(), decrypted_key.size()); //?
  for (auto &sec : sections) {
    sec->decrypt_data(key);
    plain_text.insert(plain_text.end(), sec->get_data().begin(),
                      sec->get_data().end());
  }
  callback(plain_text);
}

int main(int argc, const char *argv[]) {

  if (argc != 3) {
    std::cout << "use: ./a.out <section_path> ...\n";
    return 1;
  }
  std::vector<std::vector<std::uint8_t>> sections;
  for (std::size_t i = 1; i < static_cast<std::size_t>(argc); ++i) {
    tools::read_from_file(sections[i - 1], argv[i]);
  }
  boost::filesystem::path full_path(boost::filesystem::current_path());
  aont_restore(sections, [=](std::vector<std::uint8_t> &plaintext) {
    tools::write_2_file(plaintext, (full_path / "Temp/restored_file").c_str());
  });

  return 0;
}
