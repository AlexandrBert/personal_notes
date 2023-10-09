# Linux内核配置及编译

## 内核源码目录

|目录|存放文件|
|:--|:--|
|arch|内核源码的体系结构相关代码文件，每一个子目录代表一种架构|
|block|块设备的通用函数|
|certs|内核证书签名检查|
|crypto|常用加密和散列算法、压缩和CRC校核算法|
|Documentation|内核文档，用来描述模块功能和协议规范|
|drivers|驱动相关文件|
|firmware|保存用于驱动第三方设备的固件|
|fs|Linux支持的文件系统，每一个子目录代表一种文件系统|
|include|内核源码依赖的大部分头文件|
|init|内核初始化程序，其中 main.c 中的 start_kernel 函数是内核引导后执行的第一个函数|
|ipc|进程间通信代码|
|kernel|内核核心代码，包含进程管理、IRQ、时间等|
|lib|内核用到的库函数|
|mm|内存管理相关文件，包含共享内存、信号量、匿名管道等|
|net|网络相关文件，如TCP、IPv6、WiFi、以太网等|
|samples|内核编程的范例|
|scripts|内核脚本相关文件|
|security|安全密钥相关文件|
|sound|音频相关驱动程序|
|tools|与内核交互，以便在用户态时测试相关内核功能|
|usr|用户空间相关文件，实现了用于打包和压缩的 cpio 等|
|virt|内核虚拟机相关文件|

## 内核编译
1. 设置交叉编译环境
2. 板级配置 `make xxxxxxx_defconfig`  
    如 `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- x86_64_defconfig`
3. 内核配置 `make menuconfig`  
    如 `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig`
4. 编译内核 `make`  
    如 `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage -j 4`
5. 编译模块  
    如 `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules -j 4`
6. 编译设备树，dts后缀文件改为dtb  
    如 `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x-icev2.dtb`

