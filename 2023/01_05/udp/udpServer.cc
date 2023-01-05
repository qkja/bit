#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unordered_map>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"

using namespace std;
static void Usage(const std::string proc)
{
    std::cout << "Usage:\n\t" << proc << "  port [ip]  " << std::endl;
}
class udpServer
{
public:
    udpServer(int port, std::string ip = "")
        : _socketFd(-1), _port(port), _ip(ip)
    {
    }
    ~udpServer()
    {
    }

public:
    void init()
    {
        _socketFd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_socketFd < 0)
        {
            logMessage(FATAL, "%s : %d", strerror(errno), _socketFd);
            exit(1);
        }
        logMessage(DEBUG, "socket create success : %d", _socketFd);

        struct sockaddr_in local;
        bzero(&local, sizeof(local)); // 初始化一下

        local.sin_family = AF_INET;
        local.sin_port = htons(_port);

        local.sin_addr.s_addr = _ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());

        if (bind(_socketFd, (const struct sockaddr *)&local, sizeof(local)) == -1)
        {
            logMessage(FATAL, "%s:%d", strerror(errno), _socketFd);
            exit(2);
        }
        logMessage(DEBUG, "socket bind success : %d", _socketFd);
    }

    void start()
    {
        char inbuffer[1024];  // 读去信息
        char outbuffer[1024]; // 发送信息
        while (true)
        {
            memset(inbuffer, '\0', sizeof(inbuffer));
            memset(outbuffer, '\0', sizeof(outbuffer));

            struct sockaddr_in peer;      // 输出型参数
            socklen_t len = sizeof(peer); // 输入输出行参数
            ssize_t s = recvfrom(_socketFd, inbuffer, sizeof(inbuffer) - 1, 0, (struct sockaddr *)&peer, &len);
            if (s > 0)
            {
                inbuffer[s] = '\0';
            }
            else if (s == -1)
            {
                logMessage(WARINING, "读取失败 %s", strerror(errno));
                continue;
            }

            // cout << "============================" << endl;
            //  拿到给服务器发消息的 ip和port
            std::string peerIP = inet_ntoa(peer.sin_addr); // IP 地址转 字符串
            uint16_t peerPort = ntohs(peer.sin_port);
            // 检测用户是不是存在 如果存在,什么都不做,不存在就添加
            checkOnlineUser(peerIP, peerPort, peer);
            // 到这里一定读取成功了
            logMessage(NOTICE, "[%s:%d]# %s", peerIP.c_str(), peerPort, inbuffer);

            // for (size_t i = 0; i < strlen(inbuffer); i++)
            // {
            //     if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
            //         outbuffer[i] = toupper(inbuffer[i]);
            //     else
            //         outbuffer[i] = inbuffer[i];
            // }
            // 消息路由
            messageRoute(inbuffer, peerIP, peerPort);
            // cout << outbuffer<<" "<< strlen(outbuffer)<<  endl;
            // logMessage(NOTICE, "[%s:%d]# %s", peerIP.c_str(), peerPort, outbuffer);
            // sendto(_socketFd, outbuffer, strlen(outbuffer), 0, (struct sockaddr *)&peer, len);
        }
    }

private:
    void messageRoute(char *news, const std::string &ip, const uint16_t &port)
    {
        std::string message = "[ ";
        message += ip;
        message += ":";
        message += to_string(port);
        message += " ]: ";
        message += news;

        for (auto ch : _users)
        {
            sendto(_socketFd, message.c_str(), message.size(), 0, (struct sockaddr *)&(ch.second), sizeof(ch.second));
        }
    }
    // void messageRoute(char *mseeage)
    // {

    //     for (auto ch : _users)
    //     {
    //         sendto(_socketFd, mseeage, strlen(mseeage), 0, (struct sockaddr *)&(ch.second), sizeof(ch.second));
    //     }
    // }

    void checkOnlineUser(const std::string &peerIP, const uint16_t &peerPort,
                         struct sockaddr_in &p)
    {
        std::string name = peerIP;
        name += ":";
        name += to_string(peerPort);
        auto iter = _users.find(name);

        if (iter == _users.end())
        {
            _users[name] = p;
        }
        else
        {
            // 什么都不做
        }
    }

private:
    int _socketFd;   // fd
    uint16_t _port;  // 端口号
    std::string _ip; // ip地址
    std::unordered_map<std::string, struct sockaddr_in> _users;
};

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        Usage(argv[0]);
        exit(3);
    }

    int port = atoi(argv[1]);
    std::string ip;
    if (argc == 3)
    {
        ip = argv[2];
    }
    udpServer ser(port, ip.c_str());
    ser.init();
    ser.start();
    return 0;
}
