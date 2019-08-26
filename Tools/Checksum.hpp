#ifndef ___Tools__Chechsum__
#define ___Tools__Chechsum__

#include <cryptopp/sha.h>

namespace tools {
void calculate_sha256(std::vector<std::uint8_t> &data,
                      std::vector<std::uint8_t> &digest_hash);
void calculate_sha256(std::vector<std::uint8_t> &data,
                      std::string &digest_hash);
} // namespace tools

#endif
