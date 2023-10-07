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