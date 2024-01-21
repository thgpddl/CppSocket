#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "my_udp_socket.h"

MyUdpReceiveSocket::MyUdpReceiveSocket(string _ip, uint16_t _port)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd) // 创建失败则返回-1
    {
        puts("Failed to create socket");
        return;
    }

    std::cout << "socket创建成功: " << _ip << ":" << _port << std::endl;
    memset(&addr, 0, sizeof(addr));                // 初始化清空，将addr前sizeof(addr)个字节设置为0
    addr.sin_family = AF_INET;                     // Use IPV4
    addr.sin_port = htons(_port);                  //    设置端口
    addr.sin_addr.s_addr = inet_addr(_ip.c_str()); // 参数为char *，c_str()是将cpp的string转为c的字符串即char *，指向字符串首地址

    // 将套接字绑定到接口，套接字只是应用层，必须依靠低层传输信息
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("Failed to bind socket on port %d\n", _port);
        close(sockfd);
        return;
    }
}

void MyUdpReceiveSocket::receive()
{
    char buffer[2048];                 // 定义用于接受消息的变量
    memset(buffer, 0, sizeof(buffer)); // 将buffer设置为0，即完成清理的操作

    int counter = 0;
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t src_len = sizeof(client_addr);
        memset(&client_addr, 0, sizeof(client_addr));

        // 接收消息，上面如果超时设置，在指定时间内阻塞等待，否则timeout
        int sz = recvfrom(sockfd, buffer, 2048, 0, (sockaddr *)&client_addr, &src_len);
        if (sz > 0) // 如果接收成功
        {
            buffer[sz] = 0; // 将成功或失败标志位重置
            printf("Get Message %d: %s\n", counter++, buffer);
        }
    }
}

MyUdpReceiveSocket::~MyUdpReceiveSocket()
{
    close(sockfd); // 关闭套接字
}

MyUdpSendSocket::MyUdpSendSocket(string self_ip, uint16_t self_port)
{
    // 创建socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
    {
        puts("Failed to create socket");
        // return;
    }

    // 设置地址与端口
    socklen_t addr_len = sizeof(self_addr);

    memset(&self_addr, 0, sizeof(self_addr));
    self_addr.sin_family = AF_INET;        // Use IPV4
    self_addr.sin_port = htons(self_port); //
    self_addr.sin_addr.s_addr = inet_addr(self_ip.c_str());

    // 超时设置
    // struct timeval tv;
    // tv.tv_sec  = 0;
    // tv.tv_usec = 200000;  // 200 ms
    // setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval));

    // 绑定获取数据的端口，作为发送方，不绑定也行
    if (bind(sockfd, (struct sockaddr *)&self_addr, addr_len) == -1)
    {
        printf("Failed to bind socket on port %d\n", self_port);
        close(sockfd);
        // return;
    }
}

void MyUdpSendSocket::send(string dst_ip, uint16_t dst_port, char *information)
{
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_port = htons(dst_port);
    dst_addr.sin_addr.s_addr = inet_addr(dst_ip.c_str());

    socklen_t addr_len = sizeof(dst_addr);

    int ret = sendto(sockfd, information, sizeof(information), 0, (sockaddr *)&dst_addr, addr_len);
    if (ret < 0)
    {
        cout << "send failed!" << endl;
    }
    cout << "send success from local to "<<dst_ip<<":"<<std::to_string(dst_port) << endl;
}

MyUdpSendSocket::~MyUdpSendSocket()
{
    close(sockfd); // 关闭套接字
}
