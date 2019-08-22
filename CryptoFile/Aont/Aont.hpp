#ifndef __CryptoFile__Aont__Aont__
#define __CryptoFile__Aont__Aont__

#include "CryptoFile/Aont/Section.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace cryptofile {
namespace aont {
void aont_mask(std::vector<std::uint8_t> &data, std::size_t sections_number,
               std::function<void(
                   std::vector<std::unique_ptr<cryptofile::aont::Section>> &)>
                   callback);

void aont_restore(std::vector<std::vector<std::uint8_t>> &sections_data,
                  std::function<void(std::vector<std::uint8_t> &)> callback);
} // namespace aont
} // namespace cryptofile
#endif
