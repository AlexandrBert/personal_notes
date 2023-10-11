# Linux 内核镜像烧写

## USB OTG 烧写

烧写方式见 NXP mfgtool 文件夹。

## U-Boot 命令行 TFTP 方式烧写（用于升级更新）

1. 先在启动过程中打断进入命令行模式；

2. 开启电脑的 tftp 服务器并与之能通讯的 IP 地址；

3. 在 U-Boot 命令行模式下设置好 tftp 的相关环境变量的设置（如 serverip 、ipaddr）；
```bash
    => setenv ipaddr 192.168.1.20
    => setenv serverip 192.168.1.15
```

4. SD 卡烧写步骤
```bash
tftp 80800000 zImage
tftp 83000000 imx6ull-14x14-evk.dtb
bootz 0x80800000 - 0x83000000;
```

5. NAND板的在uboot下运行如下代码
```bash
ubi part rootfs;
ubifsmount ubi0;
ubifsload 0x84000000 /lib/firmware/fatboot.img;
tftp 0x80800000 zImage;
ubifsload 0x83000000 /usr/lib/linux-image-4.19.35-imx6/imx6ull-nand-npi.dtb;
load ramblock 0:1 0x88000000 /kernel/initrd.img-4.19.35-imx6;
bootz 0x80800000 0x88000000:${filesize} 0x83000000;
```