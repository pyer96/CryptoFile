#include "CryptoFile/Aont/Aont.hpp"

#include <cmath>
#include <cryptopp/osrng.h> //AutoSeededRandomPool
#include <gsl/span>

namespace aont {
Aont::Aont(std::unique_ptr<std::vector<uint8_t>> data,
           std::size_t sections_number)
    : m_data{std::move(data)}, m_sections_number{sections_number} {
  m_sections.reserve(m_sections_number);

  /**  We auto generate the key and the initialization vector and we use them to
   * encrypt every section.
   */
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock key(
      CryptoPP::AES::MAX_KEYLENGTH); // 16 bytes (128 bits)
  CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
  prng.GenerateBlock(key, key.size());
  prng.GenerateBlock(iv, sizeof(iv));

  /** We split the data in the number of section defined by the user. The
   * sections will have all the same size except for the last one that will
   * usually be slighty smaller.
   */
  double standard_section_size =
      static_cast<float>(m_data->size()) / static_cast<float>(m_sections_number);
  auto normal_section_size = std::ceil(standard_section_size);
  auto last_section_size =
      normal_section_size -
      ((normal_section_size * m_sections_number) - m_data->size());

  /** Make Sections
   */
  for (std::size_t i = 0; i < m_sections_number; ++i) {
    auto section_size =
        i < m_sections_number - 1 ? normal_section_size : last_section_size;
    auto section_data = gsl::span<std::uint8_t>(
        &(m_data->data()[static_cast<std::size_t>(normal_section_size) * i]),
        section_size);
    m_sections.emplace_back(std::move(section_data), key, iv);
  }
}

} // namespace aont
