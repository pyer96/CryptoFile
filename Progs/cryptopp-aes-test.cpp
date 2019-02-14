#include "Tools/Files.hpp"

#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h> //AutoSeededRandomPool

#include <istream>
#include <iterator>
#include <vector>

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cerr << "Error: missing file path\n";
    exit(1);
  }
  // Open file as binary (simulate section)
  std::vector<uint8_t> section;
  tools::read_from_file(section, argv[1]);

  // Make random key and random iv
  // NOTE: For multiple files the key can remain the same but the iv has to
  // change to guarantee security
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock key(
      CryptoPP::AES::DEFAULT_KEYLENGTH); // 16 bytes (128 bits)
  CryptoPP::byte iv[CryptoPP::AES::DEFAULT_BLOCKSIZE];
  prng.GenerateBlock(key, key.size());
  prng.GenerateBlock(iv, sizeof(iv));
  std::cerr << "DEFAULT_BLOCKSIZE = " << CryptoPP::AES::DEFAULT_BLOCKSIZE
            << "\nBLOCKSIZE = " << CryptoPP::AES::BLOCKSIZE
            << "\nDEFAULT_KEYLENGHT = " << CryptoPP::AES::DEFAULT_KEYLENGTH
            << "\nMAX_KEYLENGHT = " << CryptoPP::AES::MAX_KEYLENGTH << '\n';

  CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
  encryptor.SetKeyWithIV(key, key.size(), iv);

  std::vector<std::uint8_t> result;
  // The resulting crypted file will not be bigger than the original file plus
  // the maximum padding (that correpsonds to the blocksize).
  result.resize(section.size() + CryptoPP::AES::BLOCKSIZE);
  std::cerr << "result.size() = " << result.size() << '\n';
  CryptoPP::ArraySink cs(&result[0], result.size());

  try {
    CryptoPP::ArraySource(
        section.data(), section.size(), true,
        new CryptoPP::StreamTransformationFilter(
            encryptor, new CryptoPP::Redirector(cs),
            CryptoPP::StreamTransformationFilter::PKCS_PADDING));
  } catch (const CryptoPP::Exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    exit(1);
  }
  std::cerr << "result.size() = " << result.size() << '\n';
  // Now that we have the right size of the result we can remove the additional
  // bytes. Note: this is not the padding!! The padding is removed by the
  // StreamTrasformationFilter. The point of the two resize is to directly
  // allocate the closest size to the final size to avoid reallocations during
  // the process of encrypting/decrypting.
  result.resize(cs.TotalPutLength());
  std::cerr << "result.size() = " << result.size() << '\n';
  CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
  //  std::cout << "Chiper text:\n";
  //  encoder.Put(result.data(), result.size());
  //  encoder.MessageEnd();
  std::cout << '\n';
  tools::write_2_file(
      result, "/home/umberto/Progetti/CryptoFile/elefante-crypted.jpeg");

  // Decrypt
  CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
  decryptor.SetKeyWithIV(key, key.size(), iv);

  std::vector<std::uint8_t> decrypted_file;
  decrypted_file.resize(result.size());
  CryptoPP::ArraySink rs(&decrypted_file[0], decrypted_file.size());

  try {
    CryptoPP::ArraySource(
        result.data(), result.size(), true,
        new CryptoPP::StreamTransformationFilter(
            decryptor, new CryptoPP::Redirector(rs),
            CryptoPP::StreamTransformationFilter::PKCS_PADDING));
  } catch (const CryptoPP::Exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    exit(1);
  }
  std::cerr << "decrypted_file.size() = " << decrypted_file.size() << '\n';
  decrypted_file.resize(rs.TotalPutLength());
  std::cerr << "decrypted_file.size() = " << decrypted_file.size() << '\n';
  //  std::cout << "Recovered text:\n";
  //  encoder.Put(decrypted_file.data(), decrypted_file.size());
  //  encoder.MessageEnd();
  std::cout << '\n';
  tools::write_2_file(
      decrypted_file,
      "/home/umberto/Progetti/CryptoFile/elefante-restored.jpeg");

  return 0;
}
