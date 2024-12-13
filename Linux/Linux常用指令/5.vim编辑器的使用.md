# 不同发行版启动程序 init.d 和 systemd 的比较

## 1. init.d 和 systemd 简介
`systemd` 、 `init` 是发行版 Linux 操作系统的进程自启动，也就是进程 ID 号（PID）1 的守护进程，负责管理所有应用程序的启动、停止、重启，以及系统状态的维护。

目前市面上各种发行版 Linux 操作系统，1号进程基本已经替换成 `systemd` 进程，在较早版本的 Linux 系统中 1号进程是 `init.d` 进程。

启动管理器定义不取决于 Linux 内核本身不，完全取决于不同的Linux发行版。内核只提供接口支持 `init.d` 和 `systemd` ，但不决定使用哪一种启动管理器。关于启动管理器从 `init.d` 过渡到 `systemd` ，需要区分内核版本和发行版版本:

 Linux 发行版从 `init.d` 系统启动程序改为 `systemd` ,主要发生在以下版本:
- `Fedora`:     从 `Fedora 15` 开始采用 `systemd` 。
- `openSUSE`:   从 `openSUSE 12.1` 开始采用 `systemd` 。 
- `Debian`:     从 `Debian 8“Jessie”` 开始采用 `systemd` 。
- `Ubuntu`:     从 `Ubuntu 15.04` 开始采用 `systemd` 。
- `CentOS`:     从 `CentOS 7` 开始采用 `systemd` 。

 `init.d` 和 `systemd` 的主要区别如下:
- 设计理念: `init.d` 是脚本式设计,systemd是基于服务的设计理念。
- 启动流程: `init.d` 是序列启动,systemd是并行启动加依赖关系管理。
- 配置文件: `init.d` 使用脚本,systemd使用.service和.target单元文件。 
- 服务管理: `init.d` 使用init脚本启动,systemd使用systemctl管理服务。
- 设备管理: `systemd` 直接支持设备管理,init.d需要udev子系统。
- 日志管理: `systemd` 内置journald日志管理,init.d需要rsyslog。
- 性能: `systemd` 启动更快,并行化管理更高效。
总体来说, `systemd` 相比 `init.d` 采用了更先进的设计,大多数主流Linux都已采用 `systemd` 。

## 2. systemd 的进程启动方式

`systemd` 是Linux上系统守护进程管理工具，字母 d（daemon）是守护进程的缩写，所以， `systemd` 的意思就是 守护整个系统。 `systemd` 可以管理Linux系统中的所有资源，不同的资源统称为 `Unit` ，常见的 `unit` 有：
- Service unit：文件扩展名为.Service，用于定义系统服务（常用）
- Target unit：文件名扩展为.target，用于模拟实现“运行级别”
- Mount unit：文件名扩展为.mount定义文件系统挂载点。

`Systemd` 是内核启动后的第一个用户进程，PID为1，是所有其它用户进程的父进程。`systemd` 进程拉起的方式，主要是在启机时执行指定目录下的 `*.service` 脚本。

### 2.1 service 文件
 `.service` 文件的存放路径：
- `/etc/systemd/system/*` : 系统管理员手动软件安装包或脚本放置于此，优先级最高；
- `/run/systemd/system/*` : 运行时配置文件，这个目录一般是进程在运行时动态创建 `unit` 文件的目录， 一般很少修改，除非是修改程序运行时的一些参数时，即 `Session` 级别的，才在这里做修改；
- `/usr/lib/systemd/system/*` : 该目录中包含的是软件包安装的单元，也就是说通过 yum 、dnf、 rpm 等软件包管理命令管理的 `systemd` 单元文件，都放置在该目录下；
- `/lib/systemd/system` :指向 `/usr/lib/systemd/system` ；

`Systemd` 默认从目录 `/etc/systemd/system/` 读取配置文件。但是，里面存放的大部分文件都是符号链接，指向目录 `/usr/lib/systemd/system/` ，真正的配置文件是（自动生成）存放在这个目录。

### 2.2 systemd 操作 service 的命令 : systemctl

- `systemd` 使用语法

    > systemctl [command] [unit]（配置的应用名称）

- command可选项：
    - start：启动指定的unit : `systemctl start nginx`
    - stop：关闭指定的unit  : `systemctl stop nginx`
    - restart：重启指定unit : `systemctl restart nginx`
    - reload：重载指定unit  : `systemctl reload nginx`
    - enable：系统开机时自动启动指定 unit ，前提是配置文件中有相关配置 `systemctlenable nginx`
    - disable：开机时不自动运行指定unit : `systemctl disable nginx`
    - status：查看指定unit当前运行状态  : `systemctl status nginx `

### 2.3 service unit文件的书写格式
下面为 `/lib/systemd/system/ssh.service` 文件的全文，将根据该文件来讲解 `systemd` 的配置文件。
```bash
# [Unit]：记录unit文件的通用信息。
# Description* ：对本service的描述
# Documentation ：提供本service的文档
# Before/After：定义启动顺序，Before=xxx.service，代表本服务在xxx.service启动之前启动。After=xxox.service，代表本服务在 xxx之后启动。
# ConditionPathExists：定义启动条件，ConditionPathExists=/path/to/file，代表只有当/path/to/file文件存在时，本服务才会启动。
# Requires：定义依赖，Requires=xxx.service，代表本服务需要xxx.service服务启动后才能启动。
# Wants：定义依赖，Wants=xxx.service，代表本服务需要xxx.service服务启动后才能启动。
# Conflicts：定义冲突，Conflicts=xxx.service，代表本服务与xxx.service服务冲突，不能同时启动。
# Replaces：定义替代，Replaces=xxx.service，代表本服务与xxx.service服务互相替代，只能启动一个
[Unit]
Description=OpenBSD Secure Shell server
Documentation=man:sshd(8) man:sshd_config(5)
After=network.target auditd.service
ConditionPathExists=!/etc/ssh/sshd_not_to_be_run

# [Service]：记录Service的信息
# Type* ：定义启动类型 :
#       simple：默认值，启动的程序就是主体程序，这个程序要是退出，那么一切都退出。
#       forking：fork指定命令，fork子进程，父进程退出。
#       oneshot：一次性执行，执行完就退出。
#       dbus：使用dbus进行通信。
#       notify：执行命令后通知其他服务。
#       idle：等待，等待其他service执行完毕再执行。
#       notify：执行命令后通知其他服务。
#       failed：执行失败时执行。
# EnvironmentFile：定义环境变量文件
# ExecStartPre：定义启动前执行的命令，ExecStartPre=/usr/sbin/sshd -t
# ExecStartPost：定义启动后执行的命令
# ExecStart：定义启动命令，ExecStart=/usr/sbin/sshd -D $SSHD_OPTS
# ExecReload：定义重启命令，ExecReload=/usr/sbin/sshd -t
# ExecStop：定义停止命令，ExecStop=/usr/sbin/sshd -t
# KillMode：定义退出模式，KillMode=process，代表以进程为单位进行退出。
# Restart：定义重启策略，Restart=on-failure，代表退出码非0时重启。
# RestartSec：定义重启间隔，RestartSec=52s，代表重启间隔为52秒。
# RestartPreventExitStatus：定义重启前停止状态，RestartPreventExitStatus=255，代表重启前停止状态
# Type=notify：定义通知模式，Type=notify，代表通知模式。
# RuntimeDirectory：定义运行目录，RuntimeDirectory=sshd，代表运行目录为sshd。
# RuntimeDirectoryMode：定义运行目录权限，RuntimeDirectoryMode=0755，代表运行目录权限为755。
# RemainAfterExit：定义退出后是否继续运行，RemainAfterExit=yes，代表退出后继续运行。
# CapabilityBoundingSet：定义权限限制，CapabilityBoundingSet=CAP_IPC_LOCK CAP_SYS_ADMIN
# SupplementaryGroups：定义辅助组，SupplementaryGroups=sudo
[Service]
EnvironmentFile=-/etc/default/ssh
ExecStartPre=/usr/sbin/sshd -t
ExecStart=/usr/sbin/sshd -D $SSHD_OPTS
ExecReload=/usr/sbin/sshd -t
ExecReload=/bin/kill -HUP $MAINPID
KillMode=process
Restart=on-failure
RestartPreventExitStatus=255
Type=notify
RuntimeDirectory=sshd
RuntimeDirectoryMode=0755

# [lnstall]：安装信息
# WantedBy：启动目标，WantedBy=multi-user.target，多用户环境下启用。
# Alias：定义别名，Alias=sshd.service，定义别名为sshd.service
[Install]
WantedBy=multi-user.target
Alias=sshd.service
```


### 2.4 新增一个 service 启动进程
例如，你要拉起的可执行程序名称是 `my_dev.sh` ，放在linux上 `/root` 目录下:
1. 新建一个 `my_dev.sh` 脚本，脚本执行循环打印 `hello world!` ，赋予可执行权限:
    ```bash
    root@boeos:~# vi my_dev.sh
    # 以下为 my_dev.sh 内容，每 5 秒打印一次到 debug 串口（如果不重定向到串口设备，脚本在后台会作为 service 服务启动，这时运行的脚本会脱离当前终端，导致不显示打印信息）
    #!/bin/bash

    while true; do
            sleep 5
            echo "hello world!" > /dev/ttymxc0

    done

    ~
    ~
    root@boeos:~# chmod 777 my_dev.sh
    ```
2. 为可执行脚本或程序制定一个 `*.service` 脚本：
- 创建一个 `my_dev.service` ，将 `my_dev.service` 放置在 `systemd` 启动 `*.service` 的源目录位置 `/usr/lib/systemd/system/txx.service` ；
- 添加脚本后赋予该 `service` 脚本可执行权限；
    ```bash
    root@boeos:~# vi /lib/systemd/system/my_dev.service
    # 以下为 my_dev.service 的内容
    [Unit]
    Description=this is my dev

    [Service]
    Type=simple
    ExecStart=/root/my_dev.sh
    RemainAfterExit=yes

    [Install]
    WantedBy=multi-user.target
    ~
    root@boeos:# chmod 777 /lib/systemd/system/my_dev.service
    root@boeos:# systemctl enable my_dev
    ```

3. 用 service 服务运行脚本

- 运行 `systemctl start my_dev` 命令，启动 `my_dev` 服务，此时会打印 `hello world!` 到 debug 串口；
- 使用 `top` 命令可以看到 `my_dev.sh` 服务已经存在，程序也成功循环打印出信息；
    ![systemctl的开启启动cmd_enable](png/systemctl的运行service.png)
- 运行 `systemctl stop my_dev` 命令，停止 `my_dev` 服务， `top` 命令可以看到 `my_dev.sh` 服务已经不存在，程序已经停止循环打印信息；

4. 设置开机自启动 service 服务
- 使用 `systemctl` 命令 `enable` 开启开机自启动服务，服务名为 `*.service` 的文件名，即 `my_dev` 。
    - `enable` 命令使用后将自动会在开机启动的 [WantedBy].wants 目录新增一个软连接，指定 `my_dev.service` 的路径；
    - `disable` 命令使用后将会删除 [WantedBy].wants 目录新增的软连接。
    ![systemctl的开启启动cmd_enable](png/systemctl的开启启动cmd_enable.png)

## 3. init.d 的进程启动方式

### 3.1 系统的运行级别(前置知识)

|级别|备注|
|---|---|
|运行级别0|系统停机状态，系统默认运行级别不能设为0，否则不能正常启动|
|运行级别1|单用户工作状态，root权限，用于系统维护，禁止远程登陆|
|运行级别2|多用户状态(没有网络)|
|运行级别3|完全的多用户状态(有网络)，登陆后进入控制台命令行模式|
|运行级别4|系统未使用，保留|
|运行级别5|X11控制台，登陆后进入图形GUI模式|
|运行级别6|系统正常关闭并重启，默认运行级别不能设为6，否则不能正常启动|

### 3.2 /etc/init.d 目录

目录/etc/init.d/中包含许多系统服务的启动和停止脚本，它控制着各种事务。

查看/etc/目录时，会发现 rc0-6.d(rc0.d、rc1.d…rc6.d) 形式的目录，在这些目录下包含许多控制进程的脚本。这些脚本以"K"或者"S"开头，以"K"开头的脚本运行在以"S"开头的脚本之前。这些脚本放置的位置，决定了脚本什么时候开始运行。

从目录结构得知，/etc/init.d是符号链接文件，实际链接到目录/etc/rc.d/init.d 。

大多数Linux发行版中，启动的是目录/etc/rc.d/init.d下的服务，这个目录下存放的是实际的服务脚本。
Linux的每个运行级别，在 /etc/rc.d/ 下都有一个子目录分别是 rc0.d，rc1.d …… rc6.d，其实这些 rcN.d/目录下存放的都是链接到目录/etc/rc.d/init.d/ 下部分脚本链接文件。每个级别要执行的服务就在相对应的目录下，比如级别 5要启动的服务就都放在 rc5.d/ 下，但是放在这个 rc5.d/ 下的都是一些链接文件，链接到 /etc/rc.d/init.d/中相对应的实际脚本文件。

例如，目录 /etc/rc.d/rc2.d/ 下的S90network 链接文件，实际是链接到目录 /etc/rc.d/init.d/下的脚本文件network。

### 3.3 /etc/rc.local 目录
/etc/rc.local是一个脚本文件，从上面 /etc 文件路径可知，它链接到/etc/rc.d/rc.local。它在运行级别3中执行一次，根据脚本命令一行一行读取执行，且在开机执行一次完成后进行系统用户登录。

- /etc/init.d 目录下的脚本执行权限高，有0-6级别 ，脚本的头部需要定义启动的级别，同级别以K开头的脚本运行在以S开头的脚本之前。
- /etc/rc.local 目录下的脚本只能在执行权限3以后执行，一般是用户自定义的脚本，按文件中的命令依次执行，执行顺序跟命令所在的行有关。
