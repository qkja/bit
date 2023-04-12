/**
* User: Qkj
* Description: 认识json 也就是序列化与反序列化 
* Date: 2023-04-12
* Time: 22:53
*/


// 先说一下我们我们关于序列化与反序列化的知识点
// 序列化   结构体  --> 字符串
// 反序列化 字符串  --> 结构体


// 那么我们因该如何理解在序列化在网络中的应用
// 很简单,我们这里存在一个请求和相应的结构体
// 每一个结构体里面都保存一个序列化和反序列化的函数
//
// 请求 -> 经过序列化传递给 服务端,服务端拿到字符串转为请求,然后经过业务处理得到相应
// 把相应转为字符串转发给客户端,客户端进行反序列化后拿到相应

// 不过我们主要是认识 序列化和反序列化如何做,我们可以自己写
// 这里我们使用json第三方库
#include <iostream>
#include <jsoncpp/json/json.h>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>

#include <memory>

int main()
{
  const char* name = "小明";
  int x = 10;
  float f = 1.0f;
  int num[] = {1, 2, 3};
  Json::Value val; //这里可以理解我们把所有的数据都保存在这结构中
  val["name"] = name;
  val["x"] = x;
  val["f"] = f;

  val["num"].append(num[0]);
  val["num"].append(num[1]);
  val["num"].append(num[2]);

  // 那么我们这里开始反序列化 -- 这里是低版本
  // 这个速度快,但是我们看的不舒服
  Json::FastWriter fastWriter;
  std::string str;
  str =  fastWriter.write(val);
  //std::cout << str << std::endl;

  Json::Value root;
  Json::Reader read;
  read.parse(str, root);
  std::cout << root["name"] << std::endl;
  std::cout << root["name"].asString() << std::endl;
  // 这个我们测试一下就可以了,非常好看
  // Json::StyledWriter styledWriter;
  // std::cout << styledWriter.write(val) << std::endl;


  // 我们这里使用一个高版本
  //std::stringstream s;
  //Json::StreamWriter str; //注意这是一个抽象类,我们不能实例化,因此这里我们使用指针接收

  //Json::StreamWriterBuilder swb;
  //std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());
  //sw->write(val, &s);
  ////std::cout << str.write(val, &s) << std::endl;
  ////std::cout << s.str() << std::endl;
  //std::string str = s.str();
  //std::unique_ptr<Json::CharReader> cr(Json::CharReaderBuilder().newCharReader());
  //Json::Value root;
  //cr->parse(str.c_str(), str.c_str() + str.size(), &root, nullptr);
  //std::cout << root["name"].asString() << std::endl;
  return 0;
}
