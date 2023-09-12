# socket 基本概念

## socket 创建的函数

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

```c
#include <sys/socket.h>

sockfd = socket(int socket_family, int socket_type, int protocol);
```

## 常用函数接口

socket()：创建socket

bind()：绑定socket到本地地址和端口，通常由服务端调用

listen()：TCP专用，开启监听模式

accept()：TCP专用，服务器等待客户端连接，一般是阻塞态

connect()：TCP专用，客户端主动连接服务器

send()：TCP专用，发送数据

recv()：TCP专用，接收数据

sendto()：UDP专用，发送数据到指定的IP地址和端口

recvfrom()：UDP专用，接收数据，返回数据远端的IP地址和端口

closesocket()：关闭socket