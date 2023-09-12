# socket 基本概念

## socket 是什么

socket是在应用层和传输层之间的一个抽象层，它把TCP/IP层复杂的操作抽象为几个简单的接口供应用层调用已实现进程在网络中通信。

socket起源于UNIX，在Unix一切皆文件哲学的思想下，socket是一种"打开—读/写—关闭"模式的实现，服务器和客户端各自维护一个"文件"，在建立连接打开后，可以向自己文件写入内容供对方读取或者读取对方内容，通讯结束时关闭文件。

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