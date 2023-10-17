# 网络问题总结

## 不自动识别网络

### 问题描述：虚拟机安装成功后，开机不自动识别网络IP地址，使用 ifconfig 指令只有 172.0.0.1 这个网址

![不识别网络](png/%E4%B8%8D%E8%87%AA%E5%8A%A8%E8%AF%86%E5%88%AB%E7%BD%91%E7%BB%9C.png)

解决方法：

- 保证虚拟机是自动桥接模式
- 输入指令 `dhclient -v` ，输入完成后会自动识别出一个 ip 地址，表示识别成功。
```bash
root@ubuntu:~# dhclient -v
Internet Systems Consortium DHCP Client 4.3.5
Copyright 2004-2016 Internet Systems Consortium.
All rights reserved.
For info, please visit https://www.isc.org/software/dhcp/

Listening on LPF/ens33/00:0c:29:34:4a:4e
Sending on   LPF/ens33/00:0c:29:34:4a:4e
Sending on   Socket/fallback
DHCPDISCOVER on ens33 to 255.255.255.255 port 67 interval 3 (xid=0xde216345)
DHCPREQUEST of 192.168.124.54 on ens33 to 255.255.255.255 port 67 (xid=0x456321de)
DHCPOFFER of 192.168.124.54 from 192.168.124.1
DHCPACK of 192.168.124.54 from 192.168.124.1
bound to 192.168.124.54 -- renewal in 37833 seconds.
```

