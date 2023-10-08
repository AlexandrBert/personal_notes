# u-boot环境变量和常用命令

## uboot 环境变量

|环境变量|解释说明|
|-|-|
|baudrate|串口控制台的波特率|
|bootcmd|自动启动时执行命令|
|bootdelay|执行自启动的等候时间|
|bootfile|默认的下载文件名|
|bootargs|传递给Linux内核的启动参数|
|console|控制台所用的串口波特率| 
|mmcboot|从mmc（sd卡）启动的启动参数|
|serverip|TFTP/NFS服务器端的IP地址|
|ipaddr|本地ip地址|
|netmask|以太网网络掩码|
|ethaddr|以太网MAC地址|

## uboot 常用命令

### 1. 帮助命令
- help或者?   获取uboot支持的命令
- help <cmd>  获取命令的详细帮助

### 2. 环境变量命令
- printenv  打印环境变量
- setenv <envname> <value>  设置环境变量
- savenv  保存环境变量

### 3. 网络命令
- ping <ipaddr>   ping指定ip地址
- dhcp    从dhcp服务器自动获取ip地址

### 4. 以太网 PHY 命令
- mii device  查看当前所有 phy 设备
- mii device <devname>  选中以太网PHY设备
- mii info <phyaddr>  查看以太网PHY设备信息
- mii read <phyaddr> <reg>  读取以太网PHY寄存器
- mii write <phyaddr> <reg> <val>  写入以太网PHY寄存器
- mii dump <phyaddr> <reg> 列举选中的寄存器的配置（具体到bit），只支持reg0-5

### 5. SD卡（mmc） 命令
- mmc info      查看当前 MMC 设备信息
- mmc read addr blk# cnt    读取mmc内容到内存
- mmc write addr blk# cnt   将内存内容写入到mmc
- mmc erase blk# cnt        擦除mmc块的内容
- mmc rescan                重新查找设备
- mmc part                  列举当前设备的分区状况
- mmc dev [dev] [part]      选中设备
- mmc list                  列举所有设备

addr ： 读取到内存的位置
blk# ： 是mmc内的块号，这个位置是mmc的0地址的偏移量，16进制，block单位是512字节
cnt ： 读取block的个数，16进制

### 6. Nand Flash 命令
- nand info  查看可以适用的Nand Flash设备信息
- nand device <devname>  选中Nand Flash设备
- nand read <addr> <offset> <size>  从nand flash的offset偏移地址处读取size字节的数据到RAM的addr地址处
- nand write <addr> <offset> <size>  将RAM的addr地址处的size字节的数据写入到Nand Flash的offset偏移地址处
- nand erase <offset> <size>  擦除Nand Flash的offset偏移地址处的size字节的数据
- nand bad  显示Nand Flash的坏块信息
- nand erase.chip   擦除整块Nand Flash中的数据

### 7. SPI Flash 命令
- sf probe  查看当前SPI Flash设备信息
- sf read <addr> <offset> <len> 从 spi flash 的 offset 偏移地址处读取 len 字节的数据到 RAM 的 addr 地址处
- sf write <addr> <offset> <len> 将 RAM 的 addr 地址处的 len 字节的数据写入到 spi flash 的 offset 偏移地址
- sf erase <offset> <len> 擦除 spi flash 的 offset 偏移地址处的 len 字节的数据

### 8. USB 命令
- usb start 启动并扫描 usb 控制器
- usb reset 重启 usb 控制器
- usb stop  关闭 usb 控制器
- usb tree  显示已连接的 usb 控制器树状结构
- usb info <devname>    显示 usb 设备 <devname> 信息
- usb storage   显示已连接的 usb 存储设备
- usb dev <devname> 选中或设置 usb 设备 <devname>
- usb part <devname>    显示 usb 设备 <devname> 中的分区信息
- usb read <addr> <blk#> <cnt> 从 usb 存储设备中读取数据到 RAM 的 addr 地址处
- usb write <addr> <blk#> <cnt> 将 RAM 的 addr 地址处的数据写入到 usb 存储设备中的 blk#

### 9. 内存操作命令
- nm [.b,.w,.l] <address>   修改内存值（指定地址），填写数据是十六进制
- mm [.b,.w,.l] <address>   修改内存值（每写完一个数据，修改的地址自动加一）
- md [.b,.w,.l] <address>   显示内存值
- mw [.b,.w,.l] <address> <value> [count]   用指定的数据填充内存，count表示填充的次数
- cp [.b,.w,.l] <source> <target> [count]   内存的拷贝

其中，.b表示按字节，.w表示按字，.l表示按双字，例如 nm.b 0x80008000.
- mw 0x80008000 66666666 2 : 把 0x80008000 开始的两个字的内容改为 66666666，即 0x80008000 0x80008001 两个地址都修改为 66666666.

#### 使用内存操作点亮 LED

先找到需要点亮的 LED 灯的引脚 GPIO ，通过数据手册找到该 GPIO 的地址，最后修改该地址为的数据。

## uboot 添加命令

### 1. 添加源码中已有的命令
1. 在 cmd/Kconfig 中添加该命令的编译配置；
2. 在 menuconfig 中选中该命令；
3. 编译 uboot ；
4. 如果编译出错，根据提示，在 include/configs/xxx_evm.h 中添加该命令的编译配置或宏定义；

### 2. 添加自己编写的命令
1. 在 cmd 目录下增加源码；
2. 在 cmd/Makefile 中添加该命令的编译；
3. 在 cmd/Kconfig 中添加该命令的编译配置；
4. 编译 uboot 。

### 3. 旧版 uboot 添加命令的方法
1. 在 include/config_cmd_all.h 中查看该命令的宏定义；
2. 在上述的宏定义复制到 include/config_cmd_default.h 中；
3. 编译 uboot 。