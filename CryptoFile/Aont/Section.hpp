#ifndef __CryptoFile__Aont__Section__
#define __CryptoFile__Aont__Section__

#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cstdint>
#include <gsl/span>
#include <vector>

namespace cryptofile {
namespace aont {

class Section {
private:
public:
  virtual ~Section() {}
  virtual const std::vector<std::uint8_t> &get_data() = 0;
};

class LastSection : public Section {
private:
  std::vector<std::uint8_t> m_section_data;

public:
  LastSection(std::vector<uint8_t> data);
  const std::vector<std::uint8_t> &get_data() override {
    return m_section_data;
  }
};

class EncryptSection : public Section {
private:
  gsl::span<std::uint8_t> m_data_section;
  std::vector<std::uint8_t> m_encrypted_data;
  std::vector<std::uint8_t> m_digest_hash;

public:
  EncryptSection(gsl::span<std::uint8_t> sec, CryptoPP::SecByteBlock &key);
  const std::vector<std::uint8_t> &get_data() override {
    return m_encrypted_data;
  }
  void encrypt_data(CryptoPP::SecByteBlock &key);
  const std::vector<std::uint8_t> &get_hash() const { return m_digest_hash; }
  void calculate_hash();
};

class DecryptSection : public Section {
private:
  gsl::span<std::uint8_t> m_data_section;
  std::vector<std::uint8_t> m_decrypted_data;
  std::vector<std::uint8_t> m_digest_hash;

public:
  DecryptSection(gsl::span<std::uint8_t> data_section);
  const std::vector<std::uint8_t> &get_data() override {
    return m_decrypted_data;
  }
  void decrypt_data(CryptoPP::SecByteBlock &key);
  const std::vector<std::uint8_t> &get_hash() const { return m_digest_hash; }
  void calculate_hash();
};
} // namespace aont
} // namespace cryptofile
#endif

