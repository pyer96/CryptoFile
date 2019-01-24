#include "CryptoFile/CryptoFile.hpp"

#include <fstream>
#include <iostream>

int main(int argc, const char *argv[]) {
  std::ifstream file("Sources/CryptoFile/crypto_file_banner");
  std::cout << file.rdbuf() << '\n';

  if (argc != 2) {
    std::cerr << "Wrong usage: specify file path.\n";
    return 1;
  }
  std::cout << "input file = " << argv[1] << '\n';

  return startup(argv[1]);
}

