# Linux驱动模块编程

## 内核模块简介

内核模块是 Linux 内核向外部提供的一个插口，其全称为动态可加载内核模块（Loadable Kernel Module ， LKM），简称为模块。

内核模块不用编译进内核，控制内核大小；新增或删除功能，不需要重新编译内核，只需加载或卸载模块。

## 内核模块程序结构
### 1. 模块加载函数

Linux 内核模块加载函数一般以 __init 标识声明，示例代码如下：
```c
/* __init 标识表示函数仅在加载时有效，加载完成后函数就会失效，从内存中释放，其他函数无法调用 */
static int __init myModule_init(void)
{
    return 0;
}
/* 指定模块的入口 */
module_init(myModule_init);
```

### 2. 模块卸载函数

Linux 内核模块卸载函数一般以 __exit 标识声明，示例代码如下：
```c
static void __exit myModule_exit(void)
{
}
module_exit(myModule_exit);
```

### 3. 模块声明
- `MODULE_LICENSE("GPL");`    内核可以识别的模块许可协议，有 GPL 、GPLV2、GPLV3、LGPL、LGPLV2、LGPLV3 等；
- `MODULE_AUTHOR("author");`    模块作者信息，可不用；
- `MODULE_VERSION("version");`    模块版本信息，可不用；
- `MODULE_DESCRIPTION("description");`    模块描述信息，可不用。
- **注意：许可证声明描述内核模块的许可权限，如果不申明 LICENSE ，则模块被加载时，将收到内核被污染（kernel tainted）的警告。**

## 模块开发常用命令

系统的模块目录：`/lib/modules/4.19.35-imx6/kernel/drivers/`

- `insmod XXX.ko` ：加载内核模块；
- `rmmod XXX` ：卸载内核模块；
- `lsmod` ：查看内核模块；
- `modprobe XXX` ：加载指定的个别内核模块，或是载入一组相依赖的模块；
- `modinfo XXX.ko` ：查看内核模块信息；


## 编写最简单的 helloworld 内核模块

### 编写 hello.c 文件
```c
#include <linux/kernel.h>   /* printk */
#include <linux/init.h>     /* __init __exit */
#include <linux/module.h>   /* module_init module_exit */

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello, world!\n");  /* KERN_ALERT 表示内核警告级别 */
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, world!\n");  /* KERN_ALERT 表示内核警告级别 */
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("author");
```

### 编写 Makefile 文件
```makefile
ifneq ($(KERNELRELEASE),)
obj-m := hello.o
else
KDIR=/opt/kernel/ebf_linux_kernel-ebf_4.1.15_imx
CROSS_COMPILE=/opt/toolchain/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
all:
        make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE)
clean:
        rm -rf *.o *.ko *.mod.o *.mod.c *.symvers module* .hello.* .tmp_versions .*.*.cmd
help:
        @echo "make KDIR=<your kernel path> CROSS_COMPILE=<your CROSS_COMPILE>"
endif：
```

### 编译内核模块
1. 在虚拟机或编译环境中新建一个文件夹 hello，将 hello.c 和 Makefile 文件复制到该文件夹中；
2. 将 Makefile 中的 KDIR 和 CROSS_COMPILE 路径修改为内核路径和交叉编译工具链路径；
3. 执行 `make` 命令编译内核模块；
