#include <cstdint>
#include <gsl/span>
#include <memory>
#include <vector>

class SectionBase {
private:
  std::vector<std::uint8_t> m_data;

public:
  void print_section_data() const;
};

class Section : public SectionBase {

private:
  std::vector<uint8_t> m_transformed_data;
  std::vector<uint8_t> m_hash;

public:
  void print_transformed_data() const;
};

int main() {
  SectionBase pippo;
  Section sowlo;

//  std::vector<Section> bella(20);
  std::vector<std::unique_ptr<SectionBase>> BELLISSIMA;

  //bella.emplace_back(pippo);
  //bella.emplace_back(sowlo);
  BELLISSIMA.emplace_back(std::make_unique<Section> (sowlo));
  BELLISSIMA.emplace_back(std::make_unique<SectionBase> (pippo));
}
