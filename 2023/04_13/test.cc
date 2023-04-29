// #include <istream> // 这里是标准输入
////#include <iostream>
// #include <string>
// using namespace std;
//
// int main()
//{
//   std::string str;
//   std::getline(std::cin, str);
//   printf("%s\n", str.c_str());
//   return 0;
// }

// 先用起来,这里我们问题要讨论

#include <iostream>
#include "httplib/httplib.h"
using namespace httplib;

int main(void)
{
  Server svr;
  auto ret = svr.set_mount_point("/", "./www");

  svr.Get("/hi", [](const Request &req, Response &res)
          { res.set_content("Hello World!", "text/plain"); });

  svr.Get(R"(/numbers/(\d+))", [&](const Request &req, Response &res)
          {
              auto numbers = req.matches[1];
              res.set_content(numbers, "text/plain"); });

  svr.Post("/multipart", [&](const Request &req, Response &res)
           {
              auto size = req.files.size();
              auto ret = req.has_file("file1");
              const auto& file = req.get_file_value("file1");
              std::cout << file.filename << std::endl;
              std::cout << file.content_type << std::endl;
              std::cout << file.content << std::endl; });

  svr.listen("0.0.0.0", 8080);
  return 0;
}