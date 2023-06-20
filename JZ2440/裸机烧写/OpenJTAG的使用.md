# OpenJTAG

## OpenJTAG 的驱动安装

1. OpenJTAG 的驱动安装

    插上OpenJTAG，直接右键选中驱动文件进行查找安装。

2. 如果选中驱动安装后，设备任然显示问号，需要设置windows端的数字签名.

    打开windows设置，选择“更新与安全 -> 恢复-> 高级启动”，按步骤取消数字签名。

## 使用OpenJTAG 进行程序下载

### 使用oflash.exe,根据提示下载程序。

1. 选择“0.OpenJTAG”；

2. 选择“1.S3C2440”；

3. 选择“Nand flash”

4. 选择烧写地址，一般为 00000000