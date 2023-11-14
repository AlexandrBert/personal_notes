# imx6ull 移植 buildroot-2022.02

## 1. 网络
### 1.1 ssh 远程协议
选择：openssh
其他同类库： libssh 、 libssh2 、 tinyssh 等。

### 1.2 网络协议栈

### 1.3 网络检测工具
- ethtool ：一个用于检查和调整基于以太网的网络接口的小工具。  
    - 使用方法： `ethtool <eth0>` ；