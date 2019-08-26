#include "CryptoFile/CryptoFileSession.hpp"

#include "CryptoFile/Aont/Aont.hpp"
#include "CryptoFile/Db/DatabaseValues.hpp"
#include "CryptoFile/Session/DriveSession.hpp"
#include "CryptoFile/Session/DropboxSession.hpp"
#include "Tools/Checksum.hpp"
#include "Tools/Files.hpp"

#include <algorithm>
#include <numeric>

namespace cryptofile {
CryptoFileSession::CryptoFileSession(
    std::vector<db::CloudService> clouds_to_authenticate) {
  std::cerr << "cloud_to_authenticate.size() = "
            << clouds_to_authenticate.size() << '\n';
  for (const auto &cloud_to_authenticate : clouds_to_authenticate) {
    switch (cloud_to_authenticate) {
    case db::CloudService::Drive:
      std::cerr << "emplace_back(DriveSession)\n";
      m_authenticated_clouds.emplace_back(
          std::make_shared<session::DriveSession>());
      break;
    case db::CloudService::Dropbox:
      std::cerr << "emplace_back(DropboxSession)\n";
      m_authenticated_clouds.emplace_back(
          std::make_shared<session::DropboxSession>());
      break;
    }
  }
  std::cerr << "db::get_original_files(m_original_files)\n";
  db::get_original_files(m_original_files);
}

void CryptoFileSession::save_file_on_clouds(
    std::size_t section_number, boost::filesystem::path file_path,
    std::vector<db::CloudService> selected_clouds) {
  auto original_file_name = file_path.filename().c_str();
  // DEBUG
  std::cerr << "original_file_name = " << original_file_name << '\n';
  (void)section_number;

  std::vector<std::uint8_t> data;
  tools::read_from_file(data, file_path.c_str());

  std::string checksum;
  tools::calculate_sha256(data, checksum);
  // DEBUG
  std::cerr << "original_file_checksum = " << checksum << '\n';

  // We make a vector of pointers to the selected clouds for upload
  std::vector<std::shared_ptr<session::ServiceSession>>
      selected_authenticated_clouds;
  for (auto &cloud : selected_clouds) {
    const auto iterator = std::find_if(
        m_authenticated_clouds.begin(), m_authenticated_clouds.end(),
        [=](const std::shared_ptr<session::ServiceSession> &session) {
          return session->get_cloud_service_id() == cloud;
        });
    if (iterator != m_authenticated_clouds.end()) {
      selected_authenticated_clouds.emplace_back(*iterator);
    }
  }

  // DEBUG
  std::cerr << "selected_cloud_id:\n";
  for (const auto &selected_cloud : selected_authenticated_clouds) {
    std::cerr << '\t'
              << static_cast<int>(selected_cloud->get_cloud_service_id())
              << '\n';
  }

  aont::aont_mask(
      data, section_number,
      [original_files = &m_original_files, &original_file_name,
       &selected_authenticated_clouds, checksum](
          std::vector<std::unique_ptr<cryptofile::aont::Section>> &sections) {
        // make new db::OriginalFile
        auto &original_file = original_files->emplace_back(
            std::make_unique<cryptofile::db::OriginalFile>());
        original_file->set_name(original_file_name);
        original_file->set_checksum(checksum);
        auto &original_file_sections = original_file->sections();

        // vector<Db::Section>.size() == vector<aont::Section>.size()
        original_file_sections.reserve(sections.size());

        // Randomization of the sections order
        std::vector<std::size_t> index_buffer(sections.size());
        std::iota(index_buffer.begin(), index_buffer.end(), 0);
        std::random_shuffle(index_buffer.begin(), index_buffer.end());

        for (std::size_t i = 0; i < sections.size();) {
          for (std::size_t j = 0; j < selected_authenticated_clouds.size();
               ++j) {
            auto response = selected_authenticated_clouds[j]->upload_file(
                sections[index_buffer[i]]->get_data(), original_file_name);
            auto &new_section = original_file_sections.emplace_back(
                std::make_unique<db::Section>());
            new_section->set_name("CHANGEME!!");
            new_section->set_order(index_buffer[i]);
            new_section->set_cloud_service_id(static_cast<int>(
                selected_authenticated_clouds[j]->get_cloud_service_id()));
            new_section->set_section_cloud_id(response["id"].as_string());
            ++i;
          }
        }
        original_file->save();
      });
}
} // namespace cryptofile
