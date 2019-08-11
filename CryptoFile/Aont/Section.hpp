#ifndef __Section__
#define __Section__

#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cstdint>
#include <gsl/span>
#include <vector>

namespace aont {
class Section {
private:
  gsl::span<std::uint8_t> m_data_section;
  //  std::vector<std::uint8_t> m_encrypteddata;
  std::vector<uint8_t> m_transformed_data;
  std::vector<uint8_t> m_hash;
  // CryptoPP::SecByteBlock m_key;
  // CryptoPP::byte m_iv;

public:
  Section(gsl::span<std::uint8_t> sec, CryptoPP::SecByteBlock &key,
          CryptoPP::byte *iv);
  ~Section(){};

  const auto &get_hash() const { return m_hash; };
  void calculate_hash();
  void print_section_data() const;
  void print_transformed_data() const;
  void encrypt_data(CryptoPP::SecByteBlock &key, CryptoPP::byte *iv);
};
} // namespace aont
#endif

