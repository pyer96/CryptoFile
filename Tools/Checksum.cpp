#include "Tools/Checksum.hpp"

#include <cryptopp/base64.h>

namespace tools {
void calculate_sha256(std::vector<std::uint8_t> &data,
                      std::vector<std::uint8_t> &digest_hash) {
  digest_hash.resize(CryptoPP::SHA256::DIGESTSIZE);
  CryptoPP::SHA256 hash;
  hash.CalculateDigest(digest_hash.data(), data.data(), data.size());
}

void calculate_sha256(std::vector<std::uint8_t> &data,
                      std::string &digest_hash) {
  std::vector<std::uint8_t> digest_hash_buffer;
  digest_hash_buffer.resize(CryptoPP::SHA256::DIGESTSIZE);
  CryptoPP::SHA256 hash;
  hash.CalculateDigest(digest_hash_buffer.data(), data.data(), data.size());
  CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(digest_hash));
  encoder.Put(digest_hash_buffer.data(), digest_hash_buffer.size());
  encoder.MessageEnd();
}
} // namespace tools
