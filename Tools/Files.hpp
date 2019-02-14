#ifndef __Files__
#define __Files__

#include <string>
#include <vector>

namespace tools {
int write_2_file(const std::vector<std::uint8_t> &data,
                 const std::string file_path);

int read_from_file(std::vector<std::uint8_t> &data,
                   const std::string file_path);

} // namespace tools
#endif
