#include <vector>
#include <cstdint>
#include <iostream>
int main () { 
  std::vector<std::uint8_t> vettore;

  vettore.reserve(10);
  auto begin = vettore.begin();
  for (std::size_t i = 0; i < 10 ; i++ )
  { 
    int j  = 10 - i;
    vettore.emplace(begin + j, i);
  } 

  for( const auto &num : vettore )
  { 
    std::cerr<<num<<std::endl; 
  } 
}
