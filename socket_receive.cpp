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

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    std::cout << "usage: ./exec ip port" << std::endl;
    ;
    return 0;
  }

  // 从用户输入要绑定到的ip和port
  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]);

  MyUdpReceiveSocket yyUdpReceiveSocket = MyUdpReceiveSocket(ip, port);
  std::cout << "套接字创建成功" << std::endl;

  std::cout << "开启循环阻塞接受......" << std::endl;
  yyUdpReceiveSocket.receive();

  return 0;
}
