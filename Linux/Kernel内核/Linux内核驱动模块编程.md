# Linux 内核驱动模块编程

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
    printk(KERN_EMERG "[KERN_EMERG] Hello, world!\n");      /* KERN_EMERG 表示内核紧急情况，系统无法使用； */
    // printk(KERN_ALERT "[KERN_ALERT] Hello, world!\n");      /* KERN_ALERT 表示内核警告级别 */
    // printk(KERN_CRIT "[KERN_CRIT] Hello, world!\n");        /* KERN_CRIT 表示内核临界状态，需要注意 */
    // printk(KERN_ERR "[KERN_ERR] Hello, world!\n");          /* KERN_ERR 表示内核错误信息 */
    // printk(KERN_WARNING "[KERN_WARNING] Hello, world!\n");  /* KERN_EMERG 表示内核警告信息 */
    // printk(KERN_NOTICE "[KERN_NOTICE] Hello, world!\n");    /* KERN_EMERG 表示内核普通但重要的信息 */
    // printk(KERN_INFO "[KERN_INFO] Hello, world!\n");        /* KERN_EMERG 表示内核一般信息 */
    // printk(KERN_DEBUG "[KERN_DEBUG] Hello, world!\n");      /* KERN_EMERG 表示内核调试信息 */
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_EMERG "Goodbye, world!\n");  /* KERN_EMERG 表示内核警告级别 */
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fengkang");
MODULE_DESCRIPTION("hello world module");
MODULE_ALIAS("hello_module");

```

### 编写 Makefile 文件
```makefile
ifneq ($(KERNELRELEASE),)
obj-m := hello.o
else
KDIR=/opt/kernel/ebf_linux_kernel
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
4. 执行完成后会生成一个 hello.ko 的内核对象；

### hello.ko 内核模块的加载
1. 将 hello.ko 传输到开发板中（可以用sftp、ftp或者其他方式），可以传输到任意路径下；
2. 先使用 lsmod 命令查看当前系统中已安装的所有模块：
```bash
root@npi:~# lsmod
Module                  Size  Used by
g_multi                16384  0
...
snd_timer              32768  1 snd_pcm
```
2. 使用模块安装指令 insmod 安装 hello.ko 模块：
```bash
root@npi:~# insmod hello.ko

Message from syslogd@npi at Feb 14 18:44:57 ...
 kernel:[ 1987.052642] [KERN_EMERG] Hello, world!
```
3. hello.ko 模块安装完成后，再次通过 lsmod 可以查看到 hello.ko 模块已经安装完成；
```bash
root@npi:~# lsmod
Module                  Size  Used by
hello                  16384  0
g_multi                16384  0
...
snd_timer              32768  1 snd_pcm
```

### hello.ko 内核模块的卸载

使用 rmmod 命令删除已经安装好的模块，卸载时是根据 Module 名卸载的，所以无需加 .ko 后缀，可以看到删除后就没有该模块了。

```bash
root@npi:~# rmmod hello
root@npi:~#
Message from syslogd@npi at Feb 14 18:48:43 ...
 kernel:[ 2213.387172] Goodbye, world!
root@npi:~# lsmod
Module                  Size  Used by
g_multi                16384  0
...
snd_timer              32768  1 snd_pcm

```

## 在内核中直接编译 helloworld 内核模块

1. 找到内核源码目录中找到需要安装目录的，如安装在 `drivers/ebf_module/` 目录下，新建一个文件夹 `hello`；

2. 在 `drivers/ebf_module/hello` 目录中新建一个 `Makefile` 文件，写入如下内容：
```makefile
 obj-$(CONFIG_HELLO) := hello.o
```

3. 修改 `drivers/ebf_module/` 目录中的 `Makefile` 文件，添加相关内容，例如：
```makefile
#core
obj-y += dht11/ 
obj-y += ds18b20/ 
obj-y += infrared/
#下面一句为新增
obj-y += hello/
```

4.  修改 `drivers/ebf_module/` 目录中的 `Kconfig` 文件，并添加 `hello` 的模块选项，例如在 `drivers/ebf_module/Kconfig` ：
```Kconfig
menu "Embedfire Modules"

menuconfig EBF_MODULE
	bool "Embedfire Modules"

if EBF_MODULE

config EBF_DHT11
	tristate "dht11"

config HELLO
	tristate "hello"

endif # EBF_MODULE

endmenu
```

5. 完成以上步骤后，在内核源码主目录中，使用 menuconfig 时，就可以找到目录下多了一个新的选项，选中该选项重新编译内核即可：
```c
arch/arm/configs/npi_v7_defconfig - Linux/arm 4.19.35 Kernel Configuration
 > Device Drivers > Embedfire Modules > Embedfire Modules ──────────────────────
  ┌─────────────────────────── Embedfire Modules ────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty  │
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y>         │
  │  includes, <N> excludes, <M> modularizes features.  Press <Esc><Esc> to  │
  │  exit, <?> for Help, </> for Search.  Legend: [*] built-in  [ ] excluded │
  │ ┌──────────────────────────────────────────────────────────────────────┐ │
  │ │    --- Embedfire Modules                                             │ │
  │ │    <M>   dht11                                                       │ │
  │ │    <M>   ds18b20                                                     │ │
  │ │    <M>   infrared                                                    │ │
  │ │    <M>   hello_module(NEW)                                           │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ │                                                                      │ │
  │ └──────────────────────────────────────────────────────────────────────┘ │
  ├──────────────────────────────────────────────────────────────────────────┤
  │         <Select>    < Exit >    < Help >    < Save >    < Load >         │
  └──────────────────────────────────────────────────────────────────────────┘
```