#include <bitset>
#include <cstdint>
#include <iostream>
#include <valarray>
#include <vector>

template <class T> void print_binary(const T &data) {
  for (size_t i = 0; i < data.size(); ++i) {
    std::bitset<8> byte(data[i]);
    std::cout << byte << (i + 1 < data.size() ? ' ' : '\0');
  }
}
template <class T> void print_plain_text(const T &data) {
  for (size_t i = 0; i < data.size(); ++i) {
    std::cout << (char)data[i] << (i + 1 < data.size() ? ' ' : '\0');
  }
}

std::vector<std::uint8_t> operator^(std::vector<std::uint8_t> a,
                                    std::vector<std::uint8_t> b) {
  std::vector<std::uint8_t> c;
  c.reserve(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) {
    c.emplace_back(a[i] ^ (i < b.size() ? b[i] : 0));
  }
  return c;
}

int main() {

  {
    std::valarray<std::uint8_t> a{'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
    std::valarray<std::uint8_t> b{'b', 'b', 'b', 'b', 'b',
                                  'b', 'b', 'b', 'b', 'b'};
    auto c = a ^ b;
    std::cout << "\nstd::valarray<std::uint8_t> a = ";
    print_binary(a);
    std::cout << "\nstd::valarray<std::uint8_t> b = ";
    print_binary(b);
    std::cout << "\n                        a ^ b = ";
    print_binary(c);
    std::cout << "\n                            c = ";
    print_plain_text(c);
    std::cout << std::endl;
  }
  {
    std::valarray<std::uint8_t> a{'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
    std::valarray<std::uint8_t> b{'b', 'b', 'b'};
    auto c = a ^ b;
    std::cout << "\nstd::valarray<std::uint8_t> a = ";
    print_binary(a);
    std::cout << "\nstd::valarray<std::uint8_t> b = ";
    print_binary(b);
    std::cout << "\n                        a ^ b = ";
    print_binary(c);
    std::cout << std::endl;
  }
  {
    std::valarray<std::uint8_t> a{'a', 'a', 'a'};
    std::valarray<std::uint8_t> b{'b', 'b', 'b', 'b', 'b',
                                  'b', 'b', 'b', 'b', 'b'};
    auto c = a ^ b;
    std::cout << "\nstd::valarray<std::uint8_t> a = ";
    print_binary(a);
    std::cout << "\nstd::valarray<std::uint8_t> b = ";
    print_binary(b);
    std::cout << "\n                        a ^ b = ";
    print_binary(c);
    std::cout << std::endl;
  }
  {
    std::vector<std::uint8_t> a{'a', 'a', 'a'};
    std::vector<std::uint8_t> b{'b', 'b'};
    auto c = a ^ b;
    std::cout << "\nstd::vector<std::uint8_t> a = ";
    print_binary<std::vector<std::uint8_t>>(a);
    std::cout << "\nstd::vector<std::uint8_t> b = ";
    print_binary(b);
    std::cout << "\n                      a ^ b = ";
    print_binary(c);
    std::cout << std::endl;
  }

  return 0;
}
