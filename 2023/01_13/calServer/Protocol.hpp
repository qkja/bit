#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <cassert>

#define CRLF "\r\n"
#define CRLF_LEN strlen(CRLF)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
// 封包
std::string encode(std::string &in, uint32_t len)
{
  // "exitCode_ result_"
  // "len/r/nexitCode_ result_/r/n"
  std::string encodein = std::to_string(len);
  encodein += CRLF;
  encodein += in;
  encodein += CRLF;
  return encodein;
}

// 解包
std::string decode(std::string &in, uint32_t *len)
{
  assert(len);
  *len = 0;
  // 检测长度
  // 查找第一个\r\n
  size_t pos = in.find(CRLF);
  if (pos == std::string::npos)
    return "";
  // 一定包含长度
  // 提去长度
  std::string inLen = in.substr(0, pos); // 可以用一个例子测试一下
  int intLen = atoi(inLen.c_str());
  // 拿到长度  判断是不不是>= 确认有效载荷是符合要求的
  int surplus = in.size() - 2 * CRLF_LEN - pos;
  if (surplus < intLen) // 此时没有拿到有效的报文os+
    return "";
  // 此时有完整的报文
  *len = intLen;
  std::string package = in.substr(pos + CRLF_LEN, intLen);
  // 不一定只有一个报文 将当前报文从in中移除掉
  int removeLen = pos + package.size() + 2 * CRLF_LEN;
  in.erase(0, removeLen);
  return package;
}

// 定制的请求 x_ op y_
class Request
{
public:
  Request()
  {
  }
  ~Request()
  {
  }
  // 序列化 -- 结构化的数据 -> 字符串
  void serialize(std::string *out)
  {
  }

  // 反序列化 -- 字符串 -> 结构化的数据
  bool deserialize(const std::string &in)
  {
    // 100 + 200 严格按照这种形式
    size_t spaceOne = in.find(SPACE);
    if (spaceOne == std::string::npos)
      return false;

    size_t spaceTwo = in.rfind(SPACE);
    if (spaceTwo == std::string::npos)
      return false;

    std::string dataOne = in.substr(0, spaceOne);
    std::string dataTwo = in.substr(spaceTwo + SPACE_LEN);

    std::string oper = in.substr(spaceOne + SPACE_LEN, spaceTwo - (spaceOne + SPACE_LEN));
    if (oper.size() != 1)
      return true;
    x_ = atoi(dataOne.c_str());
    y_ = atoi(dataTwo.c_str());

    op_ = oper[0];

    // if(in.empty())
    // return false;
    // //"1+2"
    // size_t pos = 0;
    // pos = in.find('+', 0);
    // pos = in.find('-', 0);
    // pos = in.find('*', 0);
    // pos = in.find('/', 0);
    // pos = in.find('%', 0);
    // if(pos == 0||pos==std::string::npos)
    // return false;
    // // 这里是查找到了
    // x_ = atoi(in.substr(0, pos).c_str());
    // op_ = in[pos];
    // y_ = atoi(in.substr(pos+1, ).c_str());
    // return true;
  }

  void debug()
  {
    std::cout << "##########################" << std::endl;
    std::cout << "x_: " << x_ << std::endl;
    std::cout << "op_: " << op_ << std::endl;
    std::cout << "y_: " << y_ << std::endl;
    std::cout << "##########################" << std::endl;
  }

public:
  // 需要计算的数据
  int x_;
  int y_;
  // 需要进行的计算种类
  char op_; // + - * / %
};

// 定制的响应
class Response
{
public:
  Response() : exitCode_(0), result_(0)
  {
  }
  // 序列化
  void serialize(std::string *out)
  {
    // "exitCode_ result_"
    std::string ec = std::to_string(exitCode_);
    std::string res = std::to_string(result_);
    *out = ec;
    *out += SPACE;
    *out += res;
  }
  // 反序列化
  void deserialize(std::string &in)
  {
    
  }

public:
  // 退出状态，0标识运算结果合法，非0标识运行结果是非法的，!0是几就表示是什么原因错了！
  int exitCode_;
  // 运算结果
  int result_;
};
