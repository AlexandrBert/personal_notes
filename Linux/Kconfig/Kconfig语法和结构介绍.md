# Kconfig 语法和结构介绍

## 内核中的 Kconfig 结构介绍

1. 内核源码的顶层 linux-4.20.17/Kconfig 文件

    ```bash
    # SPDX-License-Identifier: GPL-2.0
    #
    # For a description of the syntax of this configuration file,
    # see Documentation/kbuild/kconfig-language.txt.
    #
    mainmenu "Linux/$(ARCH) $(KERNELVERSION) Kernel Configuration"

    comment "Compiler: $(CC_VERSION_TEXT)"

    source "scripts/Kconfig.include"

    source "init/Kconfig"

    source "kernel/Kconfig.freezer"

    source "fs/Kconfig.binfmt"

    source "mm/Kconfig"

    source "net/Kconfig"

    source "drivers/Kconfig"

    source "fs/Kconfig"

    source "security/Kconfig"

    source "crypto/Kconfig"

    source "lib/Kconfig"

    source "lib/Kconfig.debug"
    ```

menuconfig顶层菜单：

![顶层菜单截图]()

2. 