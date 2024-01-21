# CppSocket
一个UDP套接字程序

正在学习：[c++套接字编程](https://blog.csdn.net/qq_40243750/article/details/135721098)


# 编译
```bash
# 创建并进入build文件夹
mkdir build
cd build

# 前提是通过apt install cmake安装了cmake
cmake .

# 编译生成socket_receive和socket_send
make

```

# 如何使用
```bash
# 如./sockret_reveice 127.0.0.1 8080
# 将在本地8080端口监听接受数据
./socket_receive ip port

# 如./socket_send 127.0.0.1 9090 127.0.0.1 8080
# 将通过9090端口向8080端口发送数据
./socket_send self_ip self_port dst_ip dst_port

```