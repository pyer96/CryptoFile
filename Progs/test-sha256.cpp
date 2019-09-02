#include "Tools/Files.hpp"
#include <bitset>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <vector>

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cout << "use: ./a.out <section_path> ...\n";
    return 1;
  }
  std::vector<std::vector<std::uint8_t>> sections;
  sections.resize(argc - 1);
  for (std::size_t i = 1; i < static_cast<std::size_t>(argc); ++i) {
    tools::read_from_file(sections[i - 1], argv[i]);
  }
  std::vector<std::uint8_t> m_hash;
  CryptoPP::SHA256 hash;

  CryptoPP::ArraySource(
      sections[0].data(), sections[0].size(), true,
      new CryptoPP::HashFilter(
          hash, new CryptoPP::HexEncoder(new CryptoPP::VectorSink(m_hash))));
  std::cerr << "m_hash.size() = " << m_hash.size() << '\n';

  for (std::size_t i = 0; i < m_hash.size(); i++) {
    std::cerr << "m_hash_vector[" << i << "]:" << m_hash[i] << ' '
              << std::bitset<8>(m_hash[i]) << '\n';
  }

  CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
  encoder.Put(m_hash.data(), m_hash.size());
  encoder.MessageEnd();
  std::cerr << '\n';
  return 0;
}
