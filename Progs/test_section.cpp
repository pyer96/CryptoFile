#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
class Section {
private:
  std::vector<std::uint8_t> m_data;
  std::vector<std::uint8_t> m_hash;
  std::string m_name = "Section Padre";

public:
  virtual void  print_name(void)  { std::cout << "Section Name :" << m_name << '\n';};
   virtual ~Section() {}
};

class Encrypt : public Section {
private:
  std::string m_name = "Section Encrypt";

public:
  void print_name() override {
    std::cout << "Section Name :" << m_name << '\n';
   } 
};

class Decrypt : public Section {
private:
  std::string m_name = "Section Decrypt";

public:
  void print_name() override { std::cout << "Section Name :" << m_name << '\n'; }
};

int main() {
  std::vector<uint8_t> p;
  Section Padre;
  Encrypt Figlio;
  Decrypt Figlio2;
  std::unique_ptr
    <Encrypt> ptr;
  ptr->print_name();

  return 0;
}
