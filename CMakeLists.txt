# 项目信息
project(Test)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread -g")


cmake_minimum_required(VERSION 3.10)

project(MyProject)

# 编译接受程序
add_executable(socket_send socket_send.cpp  src/my_udp_socket.cpp)
target_include_directories(socket_send PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 编译发送程序
add_executable(socket_receive socket_receive.cpp  src/my_udp_socket.cpp)
target_include_directories(socket_receive PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

