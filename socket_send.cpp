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

  if (argc != 5)
  {
    std::cout << ">>>> usage: ./exec self_ip self_port dst_ip dst_port" << std::endl;
    // return 0;
  }

  // 从用户输入要绑定到的ip和port
  std::string self_ip = argv[1];
  uint16_t self_port = std::stoi(argv[2]);
  std::string dst_ip = argv[3];
  uint16_t dst_port = std::stoi(argv[4]);

  MyUdpSendSocket myUdpReceiveSocket = MyUdpSendSocket(self_ip.c_str(), self_port);
  std::cout << "套接字创建成功" << std::endl;

  std::string information;

  while (true)
  {
    std::cout<<"请键入传输的信息：";
    std::getline(std::cin, information);
    myUdpReceiveSocket.send(dst_ip, dst_port, &information[0]);
  }

  return 0;
}
