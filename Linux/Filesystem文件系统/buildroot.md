# buildroot
## buildroot 简介
Buildroot是一个简化和自动化为嵌入式系统构建完整Linux系统的工具,它使用交叉编译技术。

为了实现这个目的,Buildroot能够生成交叉编译工具链,根文件系统,Linux内核镜像以及引导加载程序等目标。Buildroot可以独立使用这些选项中的任何组合(例如,您可以使用现有的交叉编译工具链,仅使用Buildroot构建根文件系统)。

Buildroot对于从事嵌入式系统开发的人来说很有用。嵌入式系统通常使用不是PC上普遍使用的x86处理器,可能是PowerPC处理器,MIPS处理器,ARM处理器等。

Buildroot支持许多处理器及其变体;它还为几款现成的开发板提供了默认配置。此外,许多第三方项目都基于Buildroot开发其BSP或SDK。

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