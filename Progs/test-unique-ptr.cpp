#include "Tools/Files.hpp"
#include "fmt/format.h"
#include <cmath>
#include <cstdlib>
#include <gsl/pointers>
#include <gsl/span>
#include <iostream>
#include <memory>
#include <vector>

#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h> //AutoSeededRandomPool

class Section {
private:
  gsl::span<std::uint8_t> m_data;

public:
  Section(gsl::span<std::uint8_t> data) : m_data{std::move(data)} {}
  void print_address() {
    //   std::cout << fmt::format("\ndata[0] = {}\ndata[{}] = {}\n",
    //                            &m_data.data()[0], m_data.size(),
    //                            &m_data.data()[m_data.size()]);
    std::cout << "\ndata[0] = " << static_cast<void *>(&(m_data.data()[0]))
              << "\ndata[" << m_data.size()
              << "] = " << static_cast<void *>(&(m_data.data()[m_data.size()]))
              << "\n";
  }
  void print_content() {
    std::cout << "Section data content:\n"
              << std::string((char *)m_data.data(), m_data.size()) << "\n";
  }
  void encrypt() {

    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock key(
        CryptoPP::AES::MAX_KEYLENGTH); // 16 bytes (128 bits)
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, sizeof(iv));

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    std::vector<std::uint8_t> result;
    // The resulting crypted file will not be bigger than the original file plus
    // the maximum padding (that correpsonds to the blocksize).
    result.resize(m_data.size() + CryptoPP::AES::BLOCKSIZE);
    CryptoPP::ArraySink cs(&result[0], result.size());

    try {
      CryptoPP::ArraySource(
          m_data.data(), m_data.size(), true,
          new CryptoPP::StreamTransformationFilter(
              encryptor, new CryptoPP::Redirector(cs),
              CryptoPP::StreamTransformationFilter::PKCS_PADDING));
    } catch (const CryptoPP::Exception &e) {
      std::cerr << "Error: " << e.what() << '\n';
      exit(1);
    }
    result.resize(cs.TotalPutLength());
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
    std::cerr << "result.size() = " << result.size() << '\n';
    encoder.Put(result.data(), result.size());
    encoder.MessageEnd();
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "use: ./a.out <file_path> <section_number>\n";
    return 1;
  }
  std::size_t sections_number = std::atoi(argv[2]);
  std::vector<Section> sections;
  sections.reserve(sections_number);
  /*
    std::vector<std::uint8_t> data;
    tools::read_from_file(data, argv[1]);
  */
  std::vector<std::uint8_t> data;
  tools::read_from_file(data, argv[1]);
  //  std::cout << fmt::format("\ndata[0] = {}\ndata[{}] = {}\n",
  //  &data.data()[0],
  //                           data.size(), &data.data()[data.size()]);
  std::cout << "\ndata[0] = " << static_cast<void *>(&(data.data()[0]))
            << "\ndata[" << data.size()
            << "] = " << static_cast<void *>(&(data.data()[data.size()]))
            << "\n";
  auto ptr = std::make_unique<std::vector<std::uint8_t>>(std::move(data));
  // try use data

  // make sections
  double standard_section_size =
      static_cast<float>(ptr->size()) / static_cast<float>(sections_number);
  auto normal_section_size = std::ceil(standard_section_size);
  auto last_section_size =
      normal_section_size -
      ((normal_section_size * sections_number) - ptr->size());

  for (std::size_t i = 0; i < sections_number; ++i) {
    auto section_size =
        i < sections_number - 1 ? normal_section_size : last_section_size;
    std::cout << "Section =  " << i << " section_size = " << section_size
              << "\n";
    auto sec = gsl::span<std::uint8_t>(
        &(ptr->data()[static_cast<std::size_t>(normal_section_size) * i]),
        section_size);
    sections.emplace_back(std::move(sec));
    /*   sections.emplace_back(gsl::make_span(
           &(ptr->data()[static_cast<std::size_t>(normal_section_size) * i]),
           section_size));*/
  }

  std::cout << "\ndata[0] = " << static_cast<void *>(&(ptr->data()[0]))
            << "\ndata[" << ptr->size()
            << "] = " << static_cast<void *>(&(ptr->data()[ptr->size()]))
            << "\n";

  for (std::size_t i = 0; i < sections_number; ++i) {
    std::cout << "\n*******\nSection " << i << '\n';
    sections[i].print_address();
    sections[i].print_content();
    sections[i].encrypt();
  }
  return 0;
}

