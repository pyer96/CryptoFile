#include <iostream>
#include <regex>

int main() {
  auto regex_pattern = std::regex(R"(code=([^&])*)");
  std::string str = "/?code=4/"
                    "2wBOjitQFe5jbZkClU2WoVWQ6rrEBvbzLgFAjK6WWDwt_"
                    "s8uAsPnwEd3KgiJN3Y0LYkDAn5DZ5nzlVcBBOV0Ueg&scope=https://"
                    "www.googleapis.com/auth/drive.file";
  std::cerr << str << '\n';
  std::smatch sm;
  auto match = std::regex_match(str, sm, regex_pattern);
  std::cout << "match = " << match << '\n'
            << "smatch = " << sm[0] << ' ' << sm[1] << '\n';

  return 0;
}
