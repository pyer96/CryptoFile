#include "Tools/Base64.hpp"

#include <cryptopp/base64.h>
#include <cryptopp/osrng.h>

namespace tools {
void random_base64_string_generator(std::size_t size, std::string &str) {
  CryptoPP::AutoSeededRandomPool prng;
  std::vector<std::uint8_t> name_base64(size);
  std::string name;

  prng.GenerateBlock(name_base64.data(), name_base64.size());
  CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(str));
  encoder.Put(name_base64.data(), name_base64.size());
  encoder.MessageEnd();
}
} // namespace tools
