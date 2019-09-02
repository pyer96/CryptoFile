#include "CryptoFile/Aont/Aont.hpp"

#include <cmath>
#include <cryptopp/osrng.h> //AutoSeededRandomPool
#include <gsl/span>

namespace cryptofile {
namespace aont {
void aont_mask(
    std::vector<std::uint8_t> &data, std::size_t sections_number,
    std::function<void(std::vector<std::unique_ptr<aont::Section>> &)>
        callback) {
  std::vector<std::unique_ptr<cryptofile::aont::Section>> sections;
  sections.reserve(sections_number);
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock key(
      CryptoPP::AES::MAX_KEYLENGTH);           // 32 bytes (256 bits)
  prng.GenerateBlock(key, key.size());

  /** We split the data in the number of section defined by the user. The
   * sections will have all the same size except for the last one that will
   * usually be slighty smaller.
   */
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
  sections.emplace_back(
      std::make_unique<cryptofile::aont::LastSection>(encrypted_key));
  callback(sections);
}

void aont_restore(std::vector<std::vector<std::uint8_t>> &sections_data,
                  std::function<void(std::vector<std::uint8_t> &)> callback) {
  std::vector<std::unique_ptr<aont::DecryptSection>> sections;
  sections.reserve(sections_data.size() - 1);
  std::vector<std::uint8_t> decrypted_key( //?
      &(sections_data.back().data()[0]),
      &(sections_data.back().data()[sections_data.back().size()]));
  for (std::size_t i = 0; i < sections_data.size() - 1; ++i) {
    sections.emplace_back(
        std::make_unique<aont::DecryptSection>(gsl::span<std::uint8_t>(
            &(sections_data[i].data()[0]), sections_data[i].size())));
    const auto &digest_hash = sections[i]->get_hash();
    CryptoPP::xorbuf(decrypted_key.data(), decrypted_key.data(),
                     digest_hash.data(), digest_hash.size());
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
} // namespace aont
} // namespace cryptofile
