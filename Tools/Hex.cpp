#include "Tools/Hex.hpp"

#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>

namespace tools {
void random_hex_string_generator(std::size_t size, std::string &str) {
  CryptoPP::AutoSeededRandomPool prng;
  std::vector<std::uint8_t> name_hex(size);

  prng.GenerateBlock(name_hex.data(), name_hex.size());
  CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(str));
  encoder.Put(name_hex.data(), name_hex.size());
  encoder.MessageEnd();
}
} // namespace tools
