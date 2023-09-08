# MFG 量产工具制作

## 工具简介

`Manufacturing (MFG) tool V2` 量产工具是 NXP 官方提供的使用 `USB OTG` 方式烧写的量产工具。当前实例版本选择为 `IMX6_L4.1.15_2.0.0_MFG_TOOL` 。

直接下载链接：
[IMX6_L4.1.15_2.0.0_MFG_TOOL](https://www.nxp.com.cn/webapp/sps/download/license.jsp?colCode=IMX6_L4-1-15_2-0-0_MFG-TOOL&appType=file1&location=null&DOWNLOAD_ID=null)

## 官方工具认知

官方工具解压后主要需要认识的部分是三个文件:

1. **cfg.ini** ：  
    存放路径在解压后的一级目录，主要作用就是存放烧写的相关配置文件，分为四个部分：`[profiles]`、`[platform]`、`[LIST]` 和 `[variable]` 。
    
    - `[profiles]` 

        设置烧写的类型，即索引到 [Profiles] 目录下的文件夹，选择对应的 `ucl2.xml` 文件以及其所在文件夹的镜像。
    - `[platform]` 
    
        选择板子的类型，暂时不适用，无需修改。
    - `[LIST]` 
    
        设置操作列表，其名称对应到 `ucl2.xml` 文件中的 LIST 设置，例如文件中有:
        ```xml
        <LIST name="eMMC" desc="Choose eMMC as media">
            <CMD state="BootStrap" type="boot" body="BootStrap" file ="firmware/u-boot-imx6q%plus%%board%_sd.imx" ifdev="MX6Q">Loading U-boot</CMD>
            ...
            <CMD state="Updater" type="push" body="$ echo Update Complete!">Done</CMD>
        </LIST>
        ```
        此时若要选择该配置，可以设置 cfg.ini 中的 [LIST]/name = eMMC 。
    - `[variable]`

        设置 `ucl2.xml` 文件所在 LIST 下的变量的值，例如上面的 xml 文件中有 `%plus%%board%` ，这里我们就可以在 `[variable]` 下添加两个变量 `plus` 和 `board` 并用 `=` 赋值，即可替换指向的文件名中的这两个变量。
        

2. **UICfg.ini**
    存放路径在解压后的一级目录，文件中只有一个默认配置：[UICfg]/PortMgrDlg=1，变量 `PortMgrDlg` 用于设置单次烧写的最大板子数量，设置为 `1-4` 即可一次烧写最多 4 个设备。

3. **ucl2.xml**：  
    存放在 `"Profiles\[profiles]\OS Firmware"` 目录下，其中 profiles 为 `cfg.ini` 文件中设置的 profiles 名。
     默认示例存放在 `"Profiles\Linux\OS Firmware"` 目录下

## 使用官方工具需要做出的修改

1. 将一级目录下的 `cfg.ini` 文件复制一份，并备份改名为 `cfg-Linux.ini` ；
2. 将 `Profiles` 目录下的 Linux 文件夹复制一份，并命名为 `BOE-Linux` ；
3. 确认烧写的版本为 eMMC 版本，烧写的芯片为 imx6ull，根据 `BOE-Linux` 目录下的官方 `ucl2.xml` 文件，找到需要的文件版本。使用时，***为避免同系列种类和参数太多，可以将非目标设置的所有设置注释掉。***
4. 确认要烧写的镜像版本：
    - `U-boot` 的路径 `firmware/u-boot-imx6ul%lite%%6uluboot%_emmc.imx` 对应芯片的版本为 `u-boot-imx6ull14x14evk_emmc.imx` ;
    - `kernel` 版本为 `zImage` ;
    - `Initramfs` 的路径 `firmware/%initramfs%` 对应芯片的版本为 `fsl-image-mfgtool-initramfs-imx_mfgtools.cpio.gz` ;
    - `dtb` 的路径 `firmware/zImage-imx6ul%lite%-%6uldtb%-emmc.dtb` 对应芯片的版本为 `zImage-imx6ull-14x14-evk-emmc.dtb` ;

5.  根据上述文件需要的变量，将一级目录下的 `cfg.ini` 文件修改为如下设置：
    ```ini
        [profiles]
        chip = BOE-Linux

        [platform]
        board = SabreSD

        [LIST]
        # 选择操作列表下的参数
        name = eMMC

        [variable]
        board = sabresd
        # 设置要创建分区的路径变量 /dev/mmcblk%mmc% 
        mmc = 1
        sxuboot=sabresd
        sxdtb=sdb
        7duboot=sabresd
        7ddtb=sdb
        # 设置 MFG 工具加载的烧写套件版本
        6uluboot=14x14evk
        6uldtb=14x14-evk
        ldo=
        plus=
        lite=l
        initramfs=fsl-image-mfgtool-initramfs-imx_mfgtools.cpio.gz.u-boot
        seek = 1
        sxnor=qspi2
        7dnor=qspi1
        6ulnor=qspi1
        nor_part=0
    ```
