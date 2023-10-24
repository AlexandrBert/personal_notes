# I 开始

## Chapter 1、关于 buildroot
Buildroot是一个简化和自动化为嵌入式系统构建完整Linux系统的工具,它使用交叉编译技术。

为了实现这个目的,Buildroot能够生成交叉编译工具链,根文件系统,Linux内核镜像以及引导加载程序等目标。Buildroot可以独立使用这些选项中的任何组合(例如,您可以使用现有的交叉编译工具链,仅使用Buildroot构建根文件系统)。

Buildroot对于从事嵌入式系统开发的人来说很有用。嵌入式系统通常使用不是PC上普遍使用的x86处理器,可能是PowerPC处理器,MIPS处理器,ARM处理器等。

Buildroot支持许多处理器及其变体;它还为几款现成的开发板提供了默认配置。此外,许多第三方项目都基于Buildroot开发其BSP或SDK。

## Chapter 2、系统要求
Buildroot设计用于在Linux系统上运行。

虽然Buildroot本身会构建大部分编译所需的主机软件包，是某标准的Linux工具应该已经安装在主机系统上。下面是强制和可选软件包的概述（请注意，软件包名称可能在不同的发行版中有所不同）。

### 2.1 强制软件包
- Build tools:
    - which
    - sed
    - make (version 3.81 or any later)
    - binutils
    - build-essential (only for Debian based systems)
    - diffutils
    - gcc (version 4.8 or any later)
    - g++ (version 4.8 or any later)
    - bash
    - patch
    - gzip
    - bzip2
    - perl (version 5.8.7 or any later)
    - tar
    - cpio
    - unzip
    - rsync
    - file (must be in /usr/bin/file) – bc
    - findutils
- Source fetching tools:
    - wget

### 2.2 可选软件包
- 推荐的依赖项：  
Buildroot中的一些功能或工具，如legal-info或图形生成工具，具有额外的依赖项。虽然它们对于简单的构建来说不是强制性的，但仍然强烈推荐使用：
    - python（版本2.7或更高版本）

- 配置界面的依赖项：  
对于这些库，您需要安装运行时和开发数据，这在许多发行版中通常是分开打包的。开发包通常具有-dev或-devel后缀。
    - ncurses5用于使用menuconfig界面
    - qt5用于使用xconfig界面
    - glib2、gtk2和glade2用于使用gconfig界面
- 源代码获取工具：  
在官方树中，大多数软件包源代码是使用ftp、http或https位置检索的。有一些软件包只能通过版本控制系统获得。此外，Buildroot还可以通过其他工具（如rsync或scp）下载源代码（有关更多详细信息，请阅第20章）。如果您使用任何这些方法启用软件包，则需要在主机系统上安装相应的工具：
    - bazaar
    - cvs
    - git
    - mercurial
    - rsync
    - scp
    - sftp
    - subversion 
- 如果需要为目标系统构建Java Classpath，则需要Java相关软件包：
    - javac编译器
    - jar工具 
- 文档生成工具：
    - asciidoc，版本8.6.3或更高版本
    - w3m
    - 带有argparse模块的python（在2.7+和3.2+中自动存在）
    - dblatex（仅适用于pdf手册）
- 图形生成工具：
    - graphviz用于使用graph-depends和-graph-depends
    - python-matplotlib用于使用graph-build

## Chapter 3、获取 buildroot
Buildroot每3个月发布一次，分别在2月、5月、8月和11月。发布版本号的格式为YYYY.MM，例如2013.02、2014.08。
发布的压缩包可以在[buildroot.org](http://buildroot.org/downloads/)上找到。

为了方便起见，在Buildroot源代码树的`support/misc/Vagrantfile`中提供了一个`Vagrantfile`，可以快速设置一个带有所需依赖项的虚拟机来开始使用。

如果您想在Linux或Mac OS X上设置一个隔离的Buildroot环境，请将以下命令粘贴到终端上：
```bash
curl -O https://buildroot.org/downloads/Vagrantfile; vagrant up
```

如果您使用的是Windows，请将以下命令粘贴到powershell中：
```bash
(new-object System.Net.WebClient).DownloadFile(
"https://buildroot.org/downloads/Vagrantfile","Vagrantfile");
vagrant up
```

如果您想跟踪开发进展，可以使用每日快照或克隆Git存储库。有关更多详细信息，请参阅Buildroot网站的下载页面。

## Chapter 4、buildroot 快速开始

**重要提示：** 可以并应该 **以普通用户的身份** 构建所有内容。在配置和使用 `Buildroot` 时，无需使用 `root` 权限。通过以普通用户身份运行所有命令，可以保护您的系统免受在编译和安装过程中出现问题的软件包的影响。

使用 `Buildroot` 的第一步是创建一个配置。 `Buildroot` 有一个很好的配置工具，类似于 `Linux` 内核或 `BusyBox` 中的配置工具。

从buildroot目录中运行以下命令：

    $ make menuconfig
使用基于curses的原始配置器，或者

    $ make nconfig
使用基于curses的新配置器，或者

    $ make xconfig
使用基于Qt的配置器，或者

    $ make gconfig
使用基于GTK的配置器。

所有这些"make"命令都需要构建一个配置工具（包括界面），因此您可能需要安装配置工具使用的相关库的"development"软件包关更多详细信息，请参阅第2章，特别是获取您喜欢的界面的依赖项的可选要求。

在配置工具的每个菜单项中，您可以找到描述该项目的帮助信息。有关某些特定配置方面的详细信息，请参阅第6章。
一旦完成配置，配置工具将生成一个包含整个配置的.config文件。此文件将由顶层Makefile读取。

要开始构建进程，只需运行：
$ make

默认情况下，Buildroot不支持顶层并行构建，因此不需要运行make -jN。但是，顶层并行构建有实验性支持，请参阅第8.12节。

make命令通常会执行以下步骤：

- 下载源文件（如果需要）；
- 配置、构建和安装交叉编译工具链，或者简单地导入外部工具链；
- 配置、构建和安装选定的目标软件包；
- 构建内核映像（如果选择的话）；
- 构建引加载程序映像（如果选择的话）；
- 在选定的格式中创建根文件系统。

Buildroot的输出存储在一个单独的目录output/中。该目录包含几个子目录：
- images/ 存储所有的映像（内核映像、引导加载程序和根文件系统映像）。这些是您需要放在目标系统上的文件。
- build/ 构建所有组件的地方（包括Buildroot在主机上需要的工具和为目标编译的软件包）。该目录包含每个组件的一个子目录。
- host/ 包含为主机构建的工具和目标工具链的sysroot。前者是为主机编译的工具的安装，这些工具对于Buildroot的正确执行是必需的，包括交叉编译工具链。后者是类似于根文件系统层次结构的层次结构。它包含所有用户空间软件包的头文件和库，这些软件包提供和安装其他软件包使用的库。然而，该目录不打算成为目标的根文件系统：它包含许多开发文件、未剥离的二进制文件和库，使其对于嵌入式系统来说太大了。这些开发文件用于为依赖于其他库的目标编译库和应用程序。
- staging/ 是host/中目标工具链sysroot的符号链接，用于向后兼容。
- target/ 包含几乎完整的目标根文件系统：除了/dev/中的设备文件之外，一切都已准备就绪（Buildroot无法创建它们，因为Buildroot不以root身份运行，也不希望以root身份运行）。此外，它没有正确的权限（例如busybox二进制文件的setuid）。因此，不应在目标上使用此目录。相反，您应该使用在images/目录中构建的其中一个映像。如果您需要一个已提取的根文件系统映像以通过NFS引导，则使用在images/中生成的tarball映像，并以root身份提取它。与staging/相比，target/仅包含运行选定目标应用程序所需的文件和库：开发文件（头文件等）不在其中，二进制文件已剥离。

这些命令，`make menuconfig|nconfig|gconfig|xconfig` 和 `make` ，是基本命令，可以轻松快速地生成符合您需求的映像，包含您启用的所有功能和应用程序。

有关"make"命令使用的更多详细信息，请参阅第8.1节。

## Chapter 5、社区资源
与任何开源项目一样，Buildroot在其社区内部和外部有不同的信息共享方式。

如果您正在寻求帮助、想要了解Buildroot或者想要为该项目做出贡献，那么这些方式可能会对您感兴趣。

### 邮件列表
Buildroot有一个用于讨和开发的邮件列表。这是Buildroot用户和开发者进行交流的主要方式。

只有订阅Buildroot邮件列表的用户才可以在该列表上发布帖子。您可以通过邮件列表信息页面进行订阅。

发送到邮件列表的邮件也可以在邮件列表存档中找到，可以通过Mailman或者lore.kernel.org访问。

### IRC
Buildroot的IRC频道#buildroot托管在OFTC上。这是一个提问快速问题或者讨论特定主题的有用场所。

在IRC上寻求帮助时，请使用代码共享网站（如https://.ack.tf/）共享相关日志或代码片段。

请注意，对于某些问题，发布到邮件列表可能更好，因为它可以触达更多的人，包括开发者和用户。

### Bug跟踪器
可以通过邮件列表或者Buildroot的Bug跟踪器报告Buildroot中的错误。在创建错误报告之前，请参考第22.6节。

### Wiki
Buildroot的Wiki页面托管在eLinux Wiki上。它包含一些有用的链接、过去和即将到来的活动概述以及一个待办事项列表。

### Patchwork
Patchwork是一个基于Web的补丁跟踪系统，旨在促进对开源项目的贡献和管理。已发送到邮件列表的补丁会被系统“捕获”，并显示在一个网页上。

任何与补丁相关的评论也附加到补丁页面上。有关Patchwork的更多信息，请参见http://jk.ozlabs.org/projects/patchwork/。

Buildroot的Patchwork网站主要供Buildroot的维护者使用，以确保不会错过补丁。它也被Buildroot的补丁审查人员使用。然而，由于该网站以清晰简洁的Web界面展示补丁及其相应的审查评论，对于所有的Buildroot开发者来说都很有用。

Buildroot的补丁管理界面可在https://patchwork.ozlabs.org/project/buildroot/list/上访问。





------------

------------


# II 用户指南

## Chapter 6、 buildroot 配置

在 `make *config` 中的所有配置选项都有一个帮助文本，提供有关该选项的详细信息。

`make *config`命令还提供了一个搜索工具。阅读不同前端菜单中的帮助消息，了解如何使用它：
- 在 `menuconfig` 中，按下/键调用搜索工具；
- 在 `xconfig` 中，按下 `Ctrl + f` 键调用搜索工具。

搜索的结果显示匹配项的帮助消息。在 `menuconfig` 中，左列的数字提供了对应条目的快捷方式。只需输入这个数字，即可直接跳转到该条目，或者跳转到包含该条目的菜单（如果由于缺少依赖关系而无法选择该条目）。

尽管菜单结构和条目的帮助文本应该足够自解释，但有一些主题需要额外的解释，这些解释在以下章节中进行了介绍。

### 6.1 交叉编译工具链
编译工具链是一组工具，允许为系统编译代码。它包括编译器（在我们的情况是gcc），二进制工具（如汇编器和链接器，在我们的情况下是binutils）和C标准库（例如GNU Libc，uClibc-ng）。

安装在开发站点上的系统肯定已经有一个编译工具链，您可以使用它来编译在您的系统上运行的应用程序。如果您使用的是个人电脑，您的编译工具链运行在x86处理器上，并为x86处理器生成代码。在大多数Linux系统下，编译工具链使用GNU libc（glibc）作为C标准库。这个编译工具链被称为“主机编译工具链”。它运行和您工作的机器被称为“主机系统”1。

编译工具链由您的发行版提供，Buildroot与此无关（除了使用它来构建交叉编译工具链和在开发主机上运行的其他工具）。

如上所述，随系统提供的编译工具链在主机系统上运行并为主机系统的处理器生成代码。由于嵌入式系统使用了不同的处理器，您需要一个交叉编译工具链 - 一个在主机系统上运行但为目标系统（和目标处理器）生成代码的编译工具链。例如，如果您的主机系统使用x86，而目标系统使用ARM，那么主机上的常规编译工具链将在x86上运行并为x86生成代码，而交叉编译工具链将在x86上运行并为ARM生成代码。

Buildroot为交叉编译工具链提供了两种解决方案：
- 内部工具链后端，在配置界面中称为 `Buildroot toolchain` 。
- 外部工具链后端，在配置界面中称为 `External toolchain` 。

在这两个解决方案之间的选择是通过 `Toolchain` 菜单中的 `Toolchain Type` 选项来完成的。一旦选择了其中一个解决方案，就会出现许多配置选项，它们在以下部分中有详细说明。

#### 6.1.1 内部工具链后端
内部工具链后端是Buildroot在构建目标嵌入式系统的用户空间应用程序和库之前，通过自身构建交叉编译工具链的后端。

该后端支持多个C库：uClibc-ng、glibc和musl。

选择此后端后，会出现一些选项。其中最重要的许：
- 更改用于构建工具链的Linux内核头文件的版本。这个项目值得一些解释。在构建交叉编译工具链的过程中，也在构建C库。该库提供用户空间应用程序与Linux内核之间的接口。为了知道如何与Linux内核进行“通信”，C库需要访问 `Linux kernel headers` （即内核的.h文件），这些文件定义了用户空间和内核之间的接口（系统调用、数据结构等）。由于此接口向后兼容，用于构建工具链的Linux内核头文件的版本不需要完全匹配您打算在嵌入式系统上运行的Linux内核的版本。它们只需要具有与您打算运行的Linux内核版本相等或更旧版本。如果使用的内核头文件比您在嵌入式系统上运行的Linux内核更新，则C库可能使用您的Linux内核不提供的接口。
- 更改GCC编译器、binutils和C库的版本。
- 选择一些工具链选项（仅适用于uClibc）：工具链是否应具有RPC支持（主要用于NFS）、宽字符支持、区域设置支持（用于国际化）、C++支持或线程支持。根据您选择的选项，Buildroot菜单中可见的用户空间应用程序和库的数量将发化：许多应用程序和库需要启用某些工具链选项。大多数软件包在需要启用某个特定工具链选项以启用这些软件包时会显示注释。如果需要，您可以通过运行make uclibc-menuconfig来进一步细化uClibc配置。但请注意，Buildroot中的所有软件包都是针对Buildroot中捆绑的默认uClibc配置进行测试的：如果您通过从uClibc中删除功能来偏离此配置，则某些软件包可能无法。

值得注意的是，每当修改其中一个选项时，链和系统都必须重新构建。请参阅第8.2节。

此后端的优点：
- 与Buildroot完全集
- 快速，只构建必要的部分

此后端的缺点：
- 在执行make clean时需要重新构建工具链，这需要时间。如果您试图缩短构建时间，请考虑使用外部工具链后端。

#### 6.1.2 外部工具链后端
外部工具链后端允许使用现有的预构建交叉编译工具链。Buildroot已经了解一些知名的交叉编译工具链（来自ARM的Linaro和Sourcery CodeBench，以及x86-64、PowerPC和MIPS），并且能够自动下载它们，或者可以指定一个自定义工具链，可以通过下载或本地安装获得。

然后，您有三种解决方案来使用外部工具链：

- 使用预定义的外部工具链配置文件，让Buildroot下载、提取和安装工具链。Buildroot已经了解一些CodeSourcery和Linaro工具链。只需在可用的工具链中选择工具链配置文件即可。这绝对是最的解决方案。

- 使用预定义的外部工具链配置文件，但是不让Buildroot下载和提取工具链，而是告诉Buildroot您的系统上已经安装了工具链的位置。只需在可用的工具链中选择工具链配置文件，取消选择自动下载工具链，并在工具链路径文本框中填写您的交叉编译工具链的路径。

- 使用完全自定义的外部工具链。这对于使用cstool-NG或Buildroot本身生成的工具链特有用。要做到这一点，选择工具链列表中的自定义工具链解决方案。您需要填写工具链路径、工具链前缀和外部工具链C库选项。然后，您需要告诉Buildroot您的外部工具链支持的内容。如果您的外部工具链使用g，您只需告诉它是否支持C++以及是否具有内置的RPC支持。如果您的外部工具链使用uClibc库，则需要告root它是否支持RPC、宽字符、区域设置、程序调用、线程和C++。在执行开始时，Buildroot会告诉您所选选项是否与工具链配置不匹配。

我们的外部工具链支持已经通过了来自CodeSourcery和Linaro的工具链、crosstool-NG生成的链以及Buildroot自身生成的工具链的测试。一般来说，所有支持sysroot功能的工具链都应该可以工作。如果不能工作，请随时与开发人联系。

我们不支持由OpenEmbedded或Yocto生成的工具链或SDK，因为这些工具链不是纯粹的工具链（即只有编译器、binutils、C和C++库）。相反，这些工具链附带了一套非常庞大的预编译库和程序。因此，Buildroot无法导入工具链的sysroot，因为它将包含数百兆字节的通常由Buildroot构建的预编译库。

我们也不支持使用发行版工具链（即由您的发行版安装的gcc/binutils/C库）作为构建目标软件的工具链。这是因为您的发行版工具链不是一个“纯粹”的工具链（即只有C/C++库），所以我们无法将其正确地导入Buildroot构建环境中。因此，即使您正在为x86或x86_64目标构建系统，您也必须使用Buildroot或crosstool-NG生成交叉编译工具链。

如果您想为您的项目生成一个自定义工具链，可以在Buildroot中用作外部工具链，建议使用Buildroot本身（参见第6.1.3节）或crosstool-NG来构建它。

此后端的优点：
- 允许使用知名且经过充分测试的交叉编译工具链。
- 避免了交叉编译工具链构建时间，这在嵌入式Linux系统的整体构建时间中通常非常重要。

此后端的缺点：
- 如果您预构建的外部工具链存在错误，可能很难从工具链供应那里获得修复，除非您使用Buildroot或Crosstool-NG自己构建外部工具链。

#### 6.1.3 用 buildroot 构建外部工具链
Buildroot内部工具链选项可用于创建外部工具链构建内部工具链，并将其打包以供Buildroot本身（或其他项目）重用的一系列步骤。

创建一个新root配置，具体步骤如下：
- 选择适合目标CPU架构的 `Target options`
- 在 `Toolchain` 菜单，保持默认的 `Buildroot toolchain` 作为 `Toolchain type` ，并根据需要配置您的工具链
- 在 `System configuration` 菜单中，选择 `None` 作为 `Init system` ，选择 `none` 作为 `/bin/sh`
- 在 `Target packages` 菜单中，禁用 `BusyBox`
- 在 `Filesystem images` 菜单中，禁用 `tar the root filesystem`

然后，我们可以触发构建，并要求 Buildroot 生成一个 SDK 。这将方便地为我们生成一个 tarball ，其中包含我们的工具链：
    
    make sdk

将在 `$(O)/images` 中生成 SDK tarball，名称类似于`arm-buildroot-linux-uclibcgnueabi_sdk-buildroot.tar.gz`。
保存此tarball，因为它现在是您可以在其他Buildroot项目中作为外部工具链重用的工具链。
在其他Buildroot项目中，在 `Toolchain` 菜单中：
• 将 `Toolchain type` 设置为 `External toolchain`
• 将 `Toolchain` 设置为 `Custom toolchain`
• 将 `Toolchain origin` 为要 `Toolchain to be downloaded and installed`
• 将 `Toolchain URL` 设置为 `file:///path/to/your/tarball.tar.gz`

##### 6.1.3.1 外部工具链包装器
在使用外部工具链时，Buildroot会生成一个包装程序，该程序会根据配置透明地传递适当的选项给外部工具链程序。如果您需要调试此包装器以检查传递的确切参数，您可以将环境变量 `BR2_DEBUG_WRAPPER` 设置为以下之一：
- 0、空或未设置：无调试
- 1：在一行上跟踪所有参数
- 2：每行跟踪一个参数

### 6.2 /dev 管理
在Linux系统上，`/dev` 目录包含特殊文件，称为设备文件(device files)，允许用户空间应用程序访问由Linux内核管理的硬件设备。如果没有这些设备文件，即使Linux内核正确识别了硬件设备，您的用户空间应用程序也无法使用这些硬件设备。

在 `System configuration, /dev management` 中，Buildroot提供了四种不同的解决方案来处理/dev目录：

- 第一种解决方案是使用设备表进行静态管理(`Static using device table`)。这是Linux中处理设备文件的旧的经典方式。使用此方法，设备文件会持久地存储在根文件系统中（即它们在重新启动后仍然存在），并且没有任何自动创建和删除这些设备文件的机制，当硬件设备被添加或从系统中移除时。因此，Buildroot使用设备表创建一组标准的设备文件，其中默认的设备表存储在Buildroot源代码中的 `system/device_table_dev.txt` 中。当 Buildroot 生成最终的根文件系统映像时，会处理此文件，并且设备文件在 `output/target` 目录中不可见。 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 选项允许更改 Buildroot 使用的默认设备表，或添加附加的设备表，以便Buildroot在构建过程中创建附加的设备文件。因此，如果您使用此方法，并且您的系统中缺少设备文件，您可以创建一个 `board///device_table_dev.txt` 文件，其中包含您附加设备文件的描述，然后您可以将 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 设置为 `system/device_table_dev.txt board///device_table_dev.txt` 。有关设备表文件格式的更多详细信息，请参阅第25章。
