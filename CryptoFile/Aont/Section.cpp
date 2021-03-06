#include "CryptoFile/Aont/Section.hpp"
namespace cryptofile {
namespace aont {

LastSection::LastSection(std::vector<uint8_t> data)
    : m_section_data{std::move(data)} {}

EncryptSection::EncryptSection(gsl::span<std::uint8_t> data_section,
                               CryptoPP::SecByteBlock &key)
    : m_data_section{std::move(data_section)} {
  encrypt_data(key);
  m_digest_hash.resize(CryptoPP::SHA256::DIGESTSIZE);
  calculate_hash();
}
void EncryptSection::encrypt_data(CryptoPP::SecByteBlock &key) {
  CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {'1', '2', '3', '4', '5', '6',
                                                 '7', '8', '9', '0', '1', '2',
                                                 '3', '4', '5', '6'};
  m_encrypted_data.resize(m_data_section.size() + CryptoPP::AES::BLOCKSIZE);
  CryptoPP::ArraySink cs(&m_encrypted_data[0], m_encrypted_data.size());
  CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
  encryptor.SetKeyWithIV(key, key.size(), iv);
  try {
    CryptoPP::ArraySource(
        m_data_section.data(), m_data_section.size(), true,
        new CryptoPP::StreamTransformationFilter(
            encryptor, new CryptoPP::Redirector(cs),
            CryptoPP::StreamTransformationFilter::PKCS_PADDING));
    m_encrypted_data.resize(cs.TotalPutLength());
  } catch (const CryptoPP::Exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    exit(1);
  }
}

void EncryptSection::calculate_hash() {
  CryptoPP::SHA256 hash;
  hash.CalculateDigest(m_digest_hash.data(), m_encrypted_data.data(),
                       m_encrypted_data.size());
}

DecryptSection::DecryptSection(gsl::span<std::uint8_t> data_section)
    : m_data_section{std::move(data_section)} {
  m_digest_hash.resize(CryptoPP::SHA256::DIGESTSIZE);
  calculate_hash();
}

void DecryptSection::decrypt_data(CryptoPP::SecByteBlock &key) {
  CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {'1', '2', '3', '4', '5', '6',
                                                 '7', '8', '9', '0', '1', '2',
                                                 '3', '4', '5', '6'};
  m_decrypted_data.resize(m_data_section.size());
  CryptoPP::ArraySink rs(&m_decrypted_data[0], m_decrypted_data.size());
  CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
  decryptor.SetKeyWithIV(key, key.size(), iv);
  try {
    CryptoPP::ArraySource(
        m_data_section.data(), m_data_section.size(), true,
        new CryptoPP::StreamTransformationFilter(
            decryptor, new CryptoPP::Redirector(rs),
            CryptoPP::StreamTransformationFilter::PKCS_PADDING));
    m_decrypted_data.resize(rs.TotalPutLength());
  } catch (const CryptoPP::Exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    exit(1); //????
  }
}

void DecryptSection::calculate_hash() {
  CryptoPP::SHA256 hash;
  hash.CalculateDigest(m_digest_hash.data(), m_data_section.data(),
                       m_data_section.size());
}
} // namespace aont
} // namespace cryptofile
