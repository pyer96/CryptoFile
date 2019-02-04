#include "CryptoFile/CryptoFile.hpp"
#include "CryptoFile/Session/DropboxSession.hpp"
#include "CryptoFile/Session/DriveSession.hpp"

#include <fstream>
#include <iostream>
#include <vector>

void list(){}
void upload(){}
void download(){}


int main(int argc, char* argv[]){
std::ifstream file("Resources/CryptoFile/crypto_file_banner");
std::cout<<file.rdbuf()<<"\n";
std::cout<<"AUTHENTICATION WITH ONLINE CLOUDS...\n";



session::DropboxSession dropbox;
session::DriveSession   drive;
//  std::vector<db::OriginalFile> original_files;
//  std::vector<db::Section> sections;

  bool exit =false;
  
  while(!exit){
    std::cout<< "Choose one of the following\n"
                "1.  LIST\n"
                "2.  UPLOAD\n"
                "3.  DOWNLOAD\n"
                "4.  EXIT\n";
   char choice;
   std::cin >> choice;
      switch (choice){

      case '1': list();
        break;
    
      case '2': upload();
        break;
    
      case '3': download();
        break;
    
      case '4': exit=true;
        break;
    }
  } //while
}
