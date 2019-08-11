#include "CryptoFile/Aont/Section.hpp"

namespace aont {
Section::Section(gsl::span<std::uint8_t> data_section,
                 CryptoPP::SecByteBlock &key, CryptoPP::byte *iv)
    : m_data_section{std::move(data_section)} {
  encrypt_data(key, iv);
  // calculate_hash();
}

void Section::encrypt_data(CryptoPP::SecByteBlock &key, CryptoPP::byte *iv) {
  m_transformed_data.resize(m_data_section.size() + CryptoPP::AES::BLOCKSIZE);
  CryptoPP::ArraySink cs(&m_transformed_data[0], m_transformed_data.size());
  CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
  encryptor.SetKeyWithIV(key, key.size(), iv);

  try {
    CryptoPP::ArraySource(
        m_data_section.data(), m_data_section.size(), true,
        new CryptoPP::StreamTransformationFilter(
            encryptor, new CryptoPP::Redirector(cs),
            CryptoPP::StreamTransformationFilter::PKCS_PADDING));
    m_transformed_data.resize(cs.TotalPutLength());
  } catch (const CryptoPP::Exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    exit(1);
  }
}

void Section::calculate_hash() {
  CryptoPP::SHA256 hash;

  CryptoPP::ArraySource(
      m_data_section.data(), m_data_section.size(), true,
      new CryptoPP::HashFilter(
          hash, new CryptoPP::HexEncoder(new CryptoPP::VectorSink(m_hash))));
}

void Section::print_transformed_data() const {
  std::cout << "Transformed data content:\n";
  CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
  std::cerr << "m_transformed_data.size() = " << m_transformed_data.size()
            << '\n';
  encoder.Put(m_transformed_data.data(), m_transformed_data.size());
  encoder.MessageEnd();
}

void Section::print_section_data() const {
  std::cout << "Section data content:\n"
            << std::string((char *)m_data_section.data(), m_data_section.size())
            << "\n";
}
} // namespace aont

