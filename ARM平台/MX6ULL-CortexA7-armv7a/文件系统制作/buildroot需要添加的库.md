# package 设置
## 1. 网络
### 1.1. `ssh` 远程协议
选择：openssh，或其他同类库： libssh 、 libssh2 、 tinyssh 等。
- 图形选项设置：
    ```config
    [*] openssh
    [*]   client
    [*]   server
    [*]   key utilities
    [*]   use sandboxing
    ```
- 配置选择：
    - `BR2_PACKAGE_OPENSSH`
    - |-- `BR2_PACKAGE_OPENSSH_CLIENT`
    - |-- `BR2_PACKAGE_OPENSSH_SERVER`
    - |-- `BR2_PACKAGE_OPENSSH_KEY_UTILS`
    - |-- `BR2_PACKAGE_OPENSSH_SANDBOX`

### 1.2. 网络协议栈

### 1.3. `ethtool` 网络检测工具
- ethtool ：一个用于检查和调整基于以太网的网络接口的小工具。  
    - 使用方法： `ethtool <eth0>` ；

### 1.4. `PPP` 拨号工具
用于 4G 模组拨号上网；
- 工具介绍： PPP 工具是用于拨号上网的协议栈，PPP 协议是一种链路层协议，它提供了一个在两个不同的网络之间进行数据交换的框架。
- 图形选项设置：
    ```config
    -*-pppd
        [*]   filtering
        [*]   radius
        [*]   overwrite /etc/resolv.conf
    ```
- 配置选择：
    - `BR2_PACKAGE_PPP`
    - |-- `BR2_PACKAGE_PPPD_FILTER`
    - |-- `BR2_PACKAGE_PPPD_RADIUS`
    - |-- `BR2_PACKAGE_PPPD_OVERWRITE_RESOLV_CONF`

### 1.4. `iw` wifi 连接工具
无线网络监测工具；
- 工具介绍：iw 是一个命令行工具，用于配置和监控 IEEE 802.11 无线网络。
- 图形选项设置：
    ```config
    [*] iw
    ```
- 配置选择：
    - `BR2_PACKAGE_IW`

### 1.5. `wpa_supplicant` wifi 连接工具
用于 WIFI 模组登录上网；
- 工具介绍：wpa_supplicant 是适用于 Linux、BSD、Mac OS X 和 Windows 的 WPA 请求方，支持 WPA、WPA2 （IEEE 802.11i / RSN） 和 WPA3。它适用于台式机/笔记本电脑和嵌入式系统。请求方是客户端工作站中使用的 IEEE 802.1X/WPA 组件。它实现与 WPA 身份验证器的密钥协商，并控制 WLAN 驱动程序的漫游和 IEEE 802.11 身份验证/关联。
- 图形选项设置：
    ```config
    --- wpa_supplicant                                                                                      
    [*]   Enable nl80211 support (NEW)                                                                      
    [ ]   Enable wext (deprecated) (NEW)                                                                    
    [ ]   Enable wired support (NEW)                                                                        
    [ ]   Enable IBSS RSN (NEW)                                                                             
    [ ]   Enable AP mode                                                                                    
    [*]   Enable autoscan                                                                                   
    [ ]   Enable EAP                                                                                        
    [ ]   Enable HS20 (NEW)                                                                                 
    [ ]   Enable syslog support (NEW)                                                                       
    [*]   Enable WPS                                                                                        
    [ ]   Enable WPA3 support                                                                               
    [ ]   Install wpa_cli binary (NEW)                                                                      
    [ ]   Install wpa_client shared library (NEW)                                                           
    [ ]   Install wpa_passphrase binary (NEW)                                                               
    [ ]   Enable the Unix-socket control interface                                                          
    [ ]   Enable support for the DBus control interface
    ```
- 配置选择：
    - `BR2_PACKAGE_WPA_SUPPLICANT`
    - |-- `BR2_PACKAGE_WPA_SUPPLICANT_NL80211`
    - |-- `BR2_PACKAGE_WPA_SUPPLICANT_AUTOSCAN`
    - |-- `BR2_PACKAGE_WPA_SUPPLICANT_WPS`


## 2. 串口
### ~~2.1. `minicom` 串口调试工具(改为busybox自带的microcom)~~
用于调试 4G 模组的 AT 指令测试；
- 工具介绍：minicom 是一个用于串行通信的简单控制台程序。
- 配置选择： `BR2_PACKAGE_MINICOM`

## 3. 数据库
### 3.1. `sqlite` 数据库
- 工具介绍：sqlite3 是一个轻量级关系型数据库，它支持 SQL 语言，它是一个嵌入式数据库，也就是说，它被编译到应用程序中，而不是作为一个单独的服务器。
- `menuconfig` 图形选项设置：
    ```config
    [*] sqlite
    [ ]   Additional query optimizations (stat4)                                                            
    [ ]   Enable convenient access to meta-data about tables and queries                                    
    [ ]   Enable version 3 of the full-text search engine                                                   
    [ ]   Enable the JSON extensions for SQLite                                                             
    [ ]   Enable sqlite3_unlock_notify() interface                                                          
    [ ]   Set the secure_delete pragma on by default                                                        
    [ ]   Disable fsync                                                                                     
    [ ] unixodbc
    ```
- 配置选择：
    - `BR2_PACKAGE_SQLITE`


# busybox 设置
## 1. 网络

## 2. 串口
### 2.1. microcom（默认选择）