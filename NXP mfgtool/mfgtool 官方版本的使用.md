# MFG 量产工具

## 工具简介

`Manufacturing (MFG) tool V2` 量产工具是 NXP 官方提供的使用 `USB OTG` 方式烧写的量产工具。

## 快速入门

1. 在运行可执行程序 `MfgTool2.exe` 之前，在文件夹中**必须存在** `cfg.ini` 和 `UICfg.ini` 两个配置文件，且里面的设置信息必须完全正确，否则将会导致程序运行失败。

    - `UICfg.ini` 文件用来配置端口数量，表明可以同时支持的板子数量。
    ```ini
        [UICfg]
        PortMgrDlg=1
        # 比如，如果同时间只需要支持一块板，就应该设置为 "PortMgrDlg=1" 。
        # 增加到四块板时，PortMgrDlg 就应该设置为 1-4 。
    ```
    - `cfg.ini` 文件用于配置目标芯片配置文件和目标操作列表。文件格式如下：
    ```ini
        [profiles]
        chip = MX6DL Linux Update

        [platform]
        board = ARM2

        [LIST]
        name = Android-SD
        # 1. “profiles/chip” 指定目标文件的名称；“list/name” 指定目标操作列表的名称；
        #    这两个文件存放的文件路径为 "profiles/CHIP_PROFILE/OS Firmware/ucl2.xml" 。
        # 2. 当前 V2 版本的 “platform/board” 的配置暂时没有用到，可以忽略。
    ```

2. 设置好板子的启动模式，将 `OTG` 接口连接到电脑上，电脑上会多一个 `HID-compliant` 设备。

    ***（野火开发板的操作流程为，将拨码开关设置为 OTG 启动，再按住MODE按键，按一下RESET案件松开，最后松开MODE按键，也可以查看官方文档：Linux BSP User Guide）***

3. 需要注意的是，当  `MFGTool V2` 第一次烧写设备镜像时，设备必须在 `MFGTool V2` 运行前与电脑连接。运行 `MFGTool V2` 后只有两个按键：
    - `Start/Stop` 用于开始和停止烧写进程。(***如果使用 `Stop` 后再使用 `Start` 完成 re-start 的操作，进程将会尝试在上次停止的点位上继续烧写，但是不能保证一定会成功，所以不建议使用该方式。***)
    - `Exit` 用于退出程序，在退出时需要先使用 `Stop` 停止进程。

4. 在烧写过程中，可以打开板子的调试串口有利于查看更多有效信息。

    *NOTE: 制造工具在将文件系统下载到 SD卡时，有时可能会报告错误消息。这可能是由于分区大小小导致SD卡空间不足造成的。要解决这个问题，请解压缩该文件 "Profiles\ CHIP_PROFILE \OS Firmware\mksdcard.sh.tar",然后修改脚本以增加分区的大小，并根据文件系统需求创建更多分区。修改完成后，重新压缩为tar脚本。*

## 如何在专用板上选择专用存储设备
每个专用板上都有一个操作列表专用于一种存储设备。您可以从 `ucl2.xml` 中的操作列表名称获取此信息。例如:
- “`<LIST name="Sabre-SD" desc="Choose SD as media">`” 表示此操作将在 `Freescale Sabre-SD` 参考板上将映像烧录到 SD 卡。
- “`<LIST name="ubuntu-SabreSD-eMMC" desc="Choose eMMC as media">`”表示此操作将在`Freescale Sabre-SD` 参考板上将映像烧录到 eMMC 存储器。
- “`<LIST name="ARM2-SD" desc="Choose SD as media">`” 表示此操作将在 `Freescale ARM2` 参考板上将映像烧录到 SD 卡。

## 如何烧写熔丝（FUSE）
`MfgTool V2` 支持将指定的值写入保险丝。可以通过以下命令编程OTP保险丝：

```ini
<CMD state="Updater" type="push" body="send" file="files/u-boot-mx6q-arm2.bin">Sending u-boot.bin</CMD>
<CMD state="Updater" type="push" body="$ dd if=$FILE of=/dev/mmcblk0 bs=1k seek=1 skip=1 conv=fsync">write u-boot.bin to sd card</CMD>
<CMD state="Updater" type="push" body="send" file="files/uImage">Sending kernel uImage</CMD>
<CMD state="Updater" type="push" body="$ dd if=$FILE of=/dev/mmcblk0 bs=1M seek=1 conv=fsync">write kernel image to sd card</CMD>
```
- 关键字 `"file"` 的值表示要烧录的映像文件的相对路径（基于 `ucl2.xml` 路径）。
- 关键字 `"send"` 表示该文件将被发送到目标设备。
在文件被目标设备接收后，我们可以使用 `"dd"` 命令将文件烧录到相关存储设备上。`"dd"` 是一个标准的 `Linux` 命令。更详细的信息请参考 `i.MX 6Dual/6Quad Linux` 参考手册。

## 如何使用 Manufacturing Tool 烧录自己的映像文件
上述过程仅适用于`Freescale`提供的参考设计板。所有的`U-Boot`映像和内核映像都是用于支持`Freescale`参考设计板。如果您想利用该工具在自己的板上烧录自己的映像文件，您只需要按照以下步骤进行操作：
- 为`MFG`工具生成特殊的`U-Boot`映像和内核映像。
- 生成普通的`U-Boot`映像和内核映像，并可能定制根文件系统以供最终用户使用。
- 参考`ucl2.xml`文件创建自己的操作列表。通常，只需更改原始映像（`U-Boot`和`kernel`）即可。
关于如何生成制造固件的详细信息，请参考 “Manufacturing Tool v2 Linux or Android Firmware Development Guide南” 文档。

## 命令行功能
MfgTool2支持命令行功能，可以接受的命令包括`“-c，-l，-p和-noui”`。命令行的格式如下：

`MfgTool2.exe [-noui] [-c] [“chip profile folder name”] [-l] [“list name”] [-p] [number] [-s] [“variable=value” ]`

参数说明：
- -noui：此命令没有任何参数，如果使用此命令，应用程序将使用控制台界面，否则将使用GUI界面。
注意：此命令必须作为第二个参数（第一个参数是应用程序名），如果要使用的话。
- -c: 指示目标配置文件名。此命令的参数是一对双引号中的字符串。
- -l: 指示目标操作列表名称，该名称可以在 `"profiles/CHIP_PROFILE/OS Firmware/ucl2.xml"` 文件中找到。此命令的参数是一对双引号中的字符串。
- -p: 指示端口数量，表示可以同时支持的板卡数量。此命令的参数必须是1到4之间的数字。
- -s: 设置ucl变量值。如果需要设置多个变量，可以支持乘法。
- 所有上述参数都不是必须的，如果命令行中没有参数，应用程序将尝试从相应的文件中找到参数，例如，如果命令行中没有提供‘-c’参数，应用程序将尝试从 `‘cfg.ini’` 文件中获取，就像 `v2.0.x` 一样，如果应用程序无法从命令行和cfg.ini文件中获取参数，应用程序将无法运行。
- 如果命令行和 `cfg.ini/UIcfg.ini` 都指定了相同的参数，应用程序将优先采用命令行参数。
- 按CTRL+C或关闭按钮以关闭APP。

以下是一些如何使用命令行功能的示例：
1. MfgTool2.exe –noui –c “MX6Q Linux Update” –l “Sabre-SD” –p 4

    应用程序将使用控制台接口同时为四块板卡烧写镜像。目标配置文件是‘MX6Q Linux Updater’，操作列表是‘Sabre-SD’，位于“profiles/ MX6Q Linux Updater/OS Firmware/ucl2.xml”。

2. MfgTool2.exe –c “MX6Q Linux Update” –l “Android-SabreSD-eMMC” –p 2

    应用程序将使用GUI界面同时为两块板卡烧写镜像。目标配置文件是‘MX6Q Linux Updater’，操作列表是‘Android-SabreSD-eMMC’，位于“profiles/ MX6Q Linux Updater/OS Firmware/ucl2.xml”。

3. MfgTool2.exe -noui –l “Android-SabreSD-eMMC” –p 1

    应用程序用控制台接口给一个板子烧写镜像，目标文件在 cfg.ini 文件的 “profiles/chip” 选项获取，操作列表是 ‘Android-SabreSD-eMMC’ ，位于 “profiles/ CHIP_PROFILE /OS Firmware/ucl2.xml”文件。

4. MfgTool2.exe –noui –c “MX6Q Linux Update” –l “Sabre-SD”

    应用程序用控制台接口给一个板子烧写镜像。‘MX6Q Linux Updater’ 是目标文件，‘Sabre-SD’ 是操作列表，都在文件 “profiles/ MX6Q Linux Updater/OS Firmware/ucl2.xml” 文件. 最大支持的板子数量由 UICfg.ini 文件中的 “UICfg/PortMgrDlg” 指定。

5. mfgtool2.exe -c "linux" -l "SDCard" -s "board=sabresd" -s "mmc=0" -s "sxuboot=sabresd" -s "sxdtb=sdb"

    应用程序将使用GUI界面同时为一块板卡烧写镜像。‘linux’ 是目标文件，‘SDCard’ 是操作列表，位于“profiles/Linux/OS Firmware/ucl2.xml”. ucl 变量 ‘board’ 设置为 ‘sabresd’ 。 ucl 变量 ‘mmc’ 设置 ‘0’。 ucl 变量 ‘sabresd’  设置为 ‘sxuboot’ 。 ucl variable ‘sdb’ 设置为 ‘sxdtb’ 。

6. MfgTool2.exe

    与 `v2.0.x’s` 相同的操作


