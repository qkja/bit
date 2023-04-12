#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#define SEP 'X'
#define SEP_LEN sizeof(SEP)

#define CRLF "\r\n"
#define CRLF_LEN strlen(CRLF) // 坑：sizeof(CRLF)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)

#define OPS "+-*/%"
// 定制协议
// xxxxxxxxx\3xxxxxxxxxxxxx\3xxxx
void PackageSplit(std::string &inbuffer, std::vector<std::string> *results)
{
  while (true)
  {
    std::size_t pos = inbuffer.find(SEP);
    if (pos == std::string::npos)
      break;

    // 分割字符串
    results->push_back(std::move(inbuffer.substr(0, pos)));
    // 移除字符串
    inbuffer.erase(0, pos + SEP_LEN);
  }
}

// 这里是式请求 和 相应 --这个等到后面再说
struct Request
{
  int x;
  int y;
  char op;
};
struct Response
{
  int code;
  int result;
};

/// @brief 反序列化,把字符串转化为结构体
/// @param message
/// @param rep
bool Parser(std::string &in, struct Request *rep)
{
  // 1 + 1, 2 * 4  6 / 0
  // 100 + 200
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
  rep->x = atoi(dataOne.c_str());
  rep->y = atoi(dataTwo.c_str());
  rep->op = oper[0];
  return true;
}

// 把结果序列化 --> 把结果转化为字符串
void Serialize(const struct Response &rsp, std::string *out)
{
  std::string ec = std::to_string(rsp.code);
  std::string res = std::to_string(rsp.result);

  *out = ec;
  *out += SPACE;
  *out += res;
  *out += CRLF;
}