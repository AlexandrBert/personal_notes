# uboot移植实例

## uboot的编译

1. 设置交叉编译环境；
2. 板级配置 `make xxxxxx_defconfig` ;
3. 生成 uboot 两个阶段的可执行文件；

## uboot的编译实操

上述第一步的交叉编译环境安装部分此处省略。

1. 编译命令
```bash
    # 方法1
    $ make CROSS_COMPILE=arm-linux-gnueabihf- mx6ul_14x14_evk_defconfig all
    # 方法2，先配置.config文件，再编译
    $ make CROSS_COMPILE=arm-linux-gnueabihf- mx6ul_14x14_evk_defconfig
    $ make CROSS_COMPILE=arm-linux-gnueabihf-
    # 方法3，编译后生成的文件都将指定到某个文件夹中
    $ make CROSS_COMPILE=arm-linux-gnueabihf- O=mx6ul_14x14_evk mx6ul_14x14_evk_defconfig all
```

2. 错误处理
```bash
    # 错误1：出现该错误需要先清除一下：
    # make CROSS_COMPILE=arm-linux-gnueabihf- distclean
    # 如果不使用 distclean 直接使用 clean ，将不会清除板级 deconfig 配置
    ../Makefile:1248: recipe for target 'prepare3' failed
    make[2]: *** [prepare3] Error 1
    /opt/u-boot/u-boot-2016.05-gb4e185a8c3/Makefile:459: recipe for target '__build_one_by_one' failed
    make[1]: *** [__build_one_by_one] Error 2
    make[1]: Leaving directory '/opt/u-boot/u-boot-2016.05-gb4e185a8c3/mx6ul_14x14_evk'
    Makefile:150: recipe for target 'sub-make' failed
    make: *** [sub-make] Error 2
```

## uboot的烧写
将生成的uboot镜像文件烧写到开发板

### 烧写启动错误：Failed to load 'boot.scr'
错误原因：为启动内核时环境变量设置错误。  
解决办法：新增环境变量：
```bash
=>  setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblk1p2 rootwait rw'
=>  setenv bootcmd 'fatload mmc 1:1 80800000 zImage;fatload mmc 1:1 83000000 imx6ull-14x14-evk.dtb;bootz 80800000 - 83000000'
=>  saveenv
```
