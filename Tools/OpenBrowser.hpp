#include <string>

namespace tools {
static void open_browser(std::string auth_uri) {
  std::string browser_cmd("xdg-open \"" + auth_uri + "\"");
  (void)system(browser_cmd.c_str());
}
} // namespace tools
