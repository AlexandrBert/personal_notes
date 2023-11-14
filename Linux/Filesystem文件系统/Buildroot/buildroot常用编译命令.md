# buildroot 常用编译命令

## 1、图形化配置
```bash
make nuvoton_nuc980_iot_defconfig   使用开发板defconfig
make menuconfig                     进入buildroot配置界面
make savedefconfig                  保存defconfig
```

## 2、内核配置
```bash
make linux-menuconfig           进入Linux内核配置界面
make linux-savedefconfig        保存配置
make linux-update-defconfig     向Buildroot更新配置
make linux-rebuild              重新编译内核
```

## 3、Busybox配置
```bash
make busybox-menuconfig           配置busybox
make busybox-update-config        更新busybox配置文件到package
make busybox-rebuild              重新编译busybox
```

## 4、uboot配置
```bash
make uboot-menuconfig            配置uboot
make uboot-savedefconfig         保存配置
make uboot-update-defconfig      更新配置到buildroot包
```

## 5、单独编译模块
```bash
make 模块名
```

## 6、编译中出现github链接失败，编译失败。比较头疼。使用局域网一台windows电脑运行梯子工具，在开发机设置代理
```bash
export http_proxy="http://192.168.0.199:4780/"
export https_proxy="http://192.168.0.199:4780/"
```

## 7、烧录SD卡后将根分区扩充至最大
```bash
resize2fs /dev/mmcblk1p1
```
