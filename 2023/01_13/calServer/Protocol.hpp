#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <cassert>
// 我们要在这里进行我们自己的协议定制!
// 网络版本的计算器

#define CRLF "\r\n"
#define CRLF_LEN strlen(CRLF) // 坑：sizeof(CRLF)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)

// decode，整个序列化之后的字符串进行提取长度
// 1. 必须具有完整的长度
// 2. 必须具有和len相符合的有效载荷
// 我们才返回有效载荷和len
// 否则，我们就是一个检测函数！
// 9\r\n100 + 200\r\n    9\r\n112 / 200\r\n
std::string decode(std::string &in, uint32_t *len)
{
  assert(len);
  // 1. 确认是否是一个包含len的有效字符串
  *len = 0;
  std::size_t pos = in.find(CRLF);
  if (pos == std::string::npos)
    return ""; // 1234\r\nYYYYY for(int i = 3; i < 9 ;i++) [)
  // 2. 提取长度
  std::string inLen = in.substr(0, pos);
  int intLen = atoi(inLen.c_str());
  // 3. 确认有效载荷也是符合要求的
  int surplus = in.size() - 2 * CRLF_LEN - pos;
  if (surplus < intLen)
    return "";
  // 4. 确认有完整的报文结构
  std::string package = in.substr(pos + CRLF_LEN, intLen);
  *len = intLen;
  // 5. 将当前报文完整的从in中全部移除掉
  int removeLen = inLen.size() + package.size() + 2 * CRLF_LEN;
  in.erase(0, removeLen);
  // 6. 正常返回
  return package;
}

// encode, 整个序列化之后的字符串进行添加长度
std::string encode(const std::string &in, uint32_t len)
{
  // "exitCode_ result_"
  // "len\r\n""exitCode_ result_\r\n"
  std::string encodein = std::to_string(len);
  encodein += CRLF;
  encodein += in;
  encodein += CRLF;
  return encodein;
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
    // 100 + 200
    std::size_t spaceOne = in.find(SPACE);
    if (std::string::npos == spaceOne)
      return false;
    std::size_t spaceTwo = in.rfind(SPACE);
    if (std::string::npos == spaceTwo)
      return false;

    std::string dataOne = in.substr(0, spaceOne);
    std::string dataTwo = in.substr(spaceTwo + SPACE_LEN);
    std::string oper = in.substr(spaceOne + SPACE_LEN, spaceTwo - (spaceOne + SPACE_LEN));
    if (oper.size() != 1)
      return false;

    // 转成内部成员
    x_ = atoi(dataOne.c_str());
    y_ = atoi(dataTwo.c_str());
    op_ = oper[0];
    return true;
  }

  void debug()
  {
    std::cout << "#################################" << std::endl;
    std::cout << "x_: " << x_ << std::endl;
    std::cout << "op_: " << op_ << std::endl;
    std::cout << "y_: " << y_ << std::endl;
    std::cout << "#################################" << std::endl;
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
  ~Response()
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
