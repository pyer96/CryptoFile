#ifndef __CryptoFile__Db__DatabaseValues__
#define __CryptoFile__Db__DatabaseValues__

#include "CryptoFile/Db/OriginalFile.hpp"

#include <memory>
#include <vector>

namespace cryptofile {
namespace db {

static std::vector<std::unique_ptr<OriginalFile>> s_original_files;

// std::vector<std::unique_ptr<OriginalFile>> &get_original_file();
void get_original_files(
    std::vector<std::unique_ptr<OriginalFile>> &original_files);

void init_database();
} // namespace db
} // namespace cryptofile
#endif
