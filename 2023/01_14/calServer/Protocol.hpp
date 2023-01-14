#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <cassert>
#include <jsoncpp/json/json.h>

#define CRLF "\r\n"
#define CRLF_LEN strlen(CRLF)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
#define OPS "+-*/%"
// #define MY_SELF 1

// 封包
std::string encode(std::string &in, uint32_t len)
{
  // "len/r/xxxxxxyyy/r/n"
  std::string encodein = std::to_string(len);
  encodein += CRLF;
  encodein += in;
  encodein += CRLF;
  return encodein;
}

// 解包
std::string decode(std::string &in, uint32_t *len)
{
  // 我们的格式是 "len\r\n123 + 346\r\n"
  assert(len);
  *len = 0;

  // 检测长度
  // 查找第一个\r\n
  size_t pos = in.find(CRLF);
  if (pos == std::string::npos)
    return "";

  // 一定包含长度, 提取长度
  std::string inLen = in.substr(0, pos); // 可以用一个例子测试一下
  int intLen = atoi(inLen.c_str());

  // 拿到长度  判断是不不是>= 有效载荷的长度 确认有效载荷是否符合要求
  // "len\r\n123 + 346\r\n"
  int surplus = in.size() - 2 * CRLF_LEN - pos;
  if (surplus < intLen) // 此时没有拿到有效的报文,一个都没有
    return "";

  // 此时有完整的报文,甚至是多个,
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
#ifdef MY_SELF
    // 它的格式是123 + 346
    std::string dataOne = std::to_string(x_);
    std::string dataTwo = std::to_string(y_);
    *out = dataOne;
    *out += SPACE;
    //*out += std::to_string(op_);
    (*out).push_back(op_);
    *out += SPACE;
    *out += dataTwo;
#else
    // json
    // 1. Value 对象,接受几乎任意类型
    // 2. json是基于KV的
    // 3. 两套操作方法 和版本有关系,我们这里是简单的一板
    // 4. 会将所有的数据内容转化为字符串
    Json::Value root;
    root["x"] = x_;
    root["y"] = y_;
    root["op"] = op_;
    // Json::FastWriter fw; // 看成一个map
    Json::StyledWriter fw;

    //*out = fw.write(&root);
    *out = fw.write(root);
#endif
  }

  // 反序列化 -- 字符串 -> 结构化的数据
  bool deserialize(const std::string &in)
  {
    size_t spaceOne = in.find(SPACE);
    if (spaceOne == std::string::npos)
      return false;

    size_t spaceTwo = in.rfind(SPACE);
    if (spaceTwo == std::string::npos)
      return false;
      
#ifdef MY_SELF
    // 开始进行 反序列化
    // 100 + 200
    std::string dataOne = in.substr(0, spaceOne);
    std::string dataTwo = in.substr(spaceTwo + SPACE_LEN);

    std::string oper = in.substr(spaceOne + SPACE_LEN, spaceTwo - (spaceOne + SPACE_LEN));
    if (oper.size() != 1)
      return false;
    x_ = atoi(dataOne.c_str());
    y_ = atoi(dataTwo.c_str());
    op_ = oper[0];
#else
    Json::Value root;
    Json::Reader rd;
    rd.parse(in, root);

    x_ = root["x"].asInt();
    y_ = root["y"].asInt();
    op_ = root["op"].asInt();
#endif
    return true;
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
#ifdef MY_SELF
    // "exitCode_ result_"
    std::string ec = std::to_string(exitCode_);
    std::string res = std::to_string(result_);
    *out = ec;
    *out += SPACE;
    *out += res;
#else
    // json
    // 1. Value 对象,接受几乎任意类型
    // 2. json是基于KV的
    // 3. 两套操作方法 和版本有关系,我们这里是简单的一板
    // 4. 会将所有的数据内容转化为字符串
    Json::Value root;
    root["exitCode"] = exitCode_;
    root["result"] = result_;
    // Json::FastWriter fw; // 看成一个map
    Json::StyledWriter fw;

    //*out = fw.write(&root);
    *out = fw.write(root);
#endif
  }

  // 反序列化
  bool deserialize(std::string &in)
  {
    size_t space = in.find(SPACE);
    if (space == std::string::npos)
      return false;
#ifdef MY_SELF
    // "exitCode_ result_;
    exitCode_ = atoi(in.substr(0, space).c_str());
    result_ = atoi(in.substr(space + SPACE_LEN).c_str());
#else
    Json::Value root;
    Json::Reader rd;
    rd.parse(in, root);

    exitCode_ = root["exitCode"].asInt();
    result_ = root["result"].asInt();
#endif
    return true;
  }

  void debug()
  {
    std::cout << "##########################" << std::endl;
    std::cout << "exitCode_: " << exitCode_ << std::endl;
    std::cout << "result_: " << result_ << std::endl;
    std::cout << "##########################" << std::endl;
  }

public:
  // 退出状态，0标识运算结果合法，非0标识运行结果是非法的，!0是几就表示是什么原因错了！
  int exitCode_;
  // 运算结果
  int result_;
};

bool buyRequest(std::string &str, Request *req)
{
  char strtmp[1024];
  snprintf(strtmp, sizeof(strtmp), "%s", str.c_str());
  char *left = strtok(strtmp, OPS);
  if (!left)
    return false;
  char *right = strtok(nullptr, OPS);
  if (!right)
    return false;

  char mid = str[strlen(left)];
  req->x_ = atoi(left);
  req->y_ = atoi(right);
  req->op_ = mid;
  return true;
}