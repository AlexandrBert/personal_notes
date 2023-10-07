# buildroot
## buildroot 简介
buildroot 是一个通过交叉编译器生成嵌入式 Linux 系统的工具，其简单、高效并易于使用。

## 安装依赖

### Debian 下的 apt 依赖包
`'sudo apt-get install zlib1g-dev unzip gcc g++ aptitude lib32stdc++6-4.8-dbg make build-essential libncurses5 libncurses5-dev u-boot-tools traceroute -y'`

## 编译过程中遇到过的问题

### Centos 问题 1
```bash
Your Perl installation is not complete enough; at least the following
modules are missing:

         ExtUtils::MakeMaker

make: *** [dependencies] 错误 1
```

解决方法：

安装缺省的包
```bash
    yum install -y perl::ExtUtils::MakeMaker
```

### Centos 问题 2
```bash
checking whether mknod can create fifo without root privileges... configure: error: in `/opt/filesystem/buildroot/buildroot-2023.05.1/output/build/host-tar-1.34':
configure: error: you should not run configure as root (set FORCE_UNSAFE_CONFIGURE=1 in environment to bypass this check)
See `config.log' for more details
make: *** [/opt/filesystem/buildroot/buildroot-2023.05.1/output/build/host-tar-1.34/.stamp_configured] 错误 1
```
解决方法:

无法在root账户下编译，按照提示在环境变量文件中将 FORCE_UNSAFE_CONFIGURE 设置为 1

```bash
    #在 ~/.bashrc （或 /etc/profile）中添加该环境变量
    echo "export set FORCE_UNSAFE_CONFIGURE=1"  >> ~/.bashrc
    #使用 source 生效脚本
    source ~/.bashrc
```