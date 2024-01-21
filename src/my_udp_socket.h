#ifndef _MY_UDP_SOCKET_
#define _MY_UDP_SOCKET_

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
#include <string>
using namespace std;

class MyUdpReceiveSocket
{
public:
    int sockfd;

    struct sockaddr_in addr;
    MyUdpReceiveSocket(string _ip, uint16_t _port);
    void receive();
    ~MyUdpReceiveSocket();
};

class MyUdpSendSocket
{
public:
    int sockfd;

    struct sockaddr_in self_addr, dst_addr;
    MyUdpSendSocket(string self_ip, uint16_t self_port);
    void send(string dst_ip, uint16_t dst_port, char *information);
    ~MyUdpSendSocket();
};
#endif
