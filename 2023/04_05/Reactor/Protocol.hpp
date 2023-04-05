#pragma once
#include <string>
#include <vector>
#define SEP 'X'
#define SEP_LEN sizeof(SEP)
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
