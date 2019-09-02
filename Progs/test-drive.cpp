#include "CryptoFile/Session/DriveSession.hpp"

#include <cpprest/http_client.h>
#include <vector>



int main () 
{

  auto request = web::http::http_request(web::http::methods::POST);
  auto uri = web::http::uri_builder("/upload/drive/v3/files");
  uri.append_query("uploadType", "multipart" );

//  request.headers().set_content_type("multipart/related");
 request.headers().add("Content-Type","multipart/related; boundary=--CryptoFile ");
//  request.headers().
  request.set_request_uri(uri.to_uri());
  std::string boundary= "--CryptoFile";
  std::string body_content;
  std::cerr<<request.to_string();
  /*
 
  auto request = web::http::http_request(web::http::methods::POST);

 //  web::http::client::http_client driveclient("https://www.googleapis.com", http_client_config());
  std::string boundary = "---CryptoFile-boundary---";
  std::vector<std::pair<std::string, std::string>> params;
  params.push_back(std::pair<std::string, std::string> ("name", "idfhoairf"));
  std::string body_content;

  body_content += "\r\n--"; 
  body_content += boundary;
  body_content += "\r\nContent-Type: application/json; charset=UTF-8";
  body_content += "\r\n{\n\"name\" : \"shfdsioad\"\r\n}";

 request.set_body(body_content, "multipart/related; boundary=" + boundary);

 auto uri = web::http::uri_builder("/upload/drive/v3/files");
 uri.append_query("uploadType", "multipart");

 request.set_request_uri(uri.to_uri());
 request.headers().set_content_type("multipart/related");
 std::cerr<< request.to_string();
*/ 

} 

