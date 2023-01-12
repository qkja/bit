#pragma once
#include <string>
class Request
{
public:
  Request(/* args */);
  ~Request();

public:
  // 序列化
  void serialize(std::string &out)
  {
  }
  void deSerialize(std::string &in)
  {
  }
  // 序列化之后的字符创添加长度
  std::string encode(const std::string &in, uint32_t len)
  {
  }
  // 提出长度
  std::string decode(const std::string &in, uint32_t len)
  {
  }

private:
  int _x;
  int _y;
  char _op;
};

class Response
{
public:
  Response(/* args */);
  ~Response();

public:
  void serialize(std::string &out)
  {
  }
  void deSerialize(std::string &in)
  {
  }

private:
  int _exitCode; // 退出码
  int _result;
};
