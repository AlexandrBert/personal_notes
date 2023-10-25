# I 开始

## Chapter 1、关于 buildroot
Buildroot是一个简化和自动化为嵌入式系统构建完整Linux系统的工具，它使用交叉编译技术。

为了实现这个目的，Buildroot能够生成交叉编译工具链，根文件系统，Linux内核镜像以及引导加载程序等目标。Buildroot可以独立使用这些选项中的任何组合(例如，您可以使用现有的交叉编译工具链，仅使用Buildroot构建根文件系统)。

Buildroot对于从事嵌入式系统开发的人来说很有用。嵌入式系统通常使用不是PC上普遍使用的x86处理器，可能是PowerPC处理器，MIPS处理器，ARM处理器等。

Buildroot支持许多处理器及其变体;它还为几款现成的开发板提供了默认配置。此外，许多第三方项目都基于Buildroot开发其BSP或SDK。

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
"https://buildroot.org/downloads/Vagrantfile"，"Vagrantfile");
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
- 将 `Toolchain type` 设置为 `External toolchain`
- 将 `Toolchain` 设置为 `Custom toolchain`
- 将 `Toolchain origin` 为要 `Toolchain to be downloaded and installed`
- 将 `Toolchain URL` 设置为 `file:///path/to/your/tarball.tar.gz`

##### 6.1.3.1 外部工具链包装器
在使用外部工具链时，Buildroot会生成一个包装程序，该程序会根据配置透明地传递适当的选项给外部工具链程序。如果您需要调试此包装器以检查传递的确切参数，您可以将环境变量 `BR2_DEBUG_WRAPPER` 设置为以下之一：
- 0、空或未设置：无调试
- 1：在一行上跟踪所有参数
- 2：每行跟踪一个参数

### 6.2 /dev 管理
在Linux系统上，`/dev` 目录包含特殊文件，称为设备文件(device files)，允许用户空间应用程序访问由Linux内核管理的硬件设备。如果没有这些设备文件，即使Linux内核正确识别了硬件设备，您的用户空间应用程序也无法使用这些硬件设备。

在 `System configuration， /dev management` 中， `Buildroot` 提供了四种不同的解决方案来处理/dev目录：

- 第一种解决方案是使用设备表进行静态管理(`Static using device table`)。这是Linux中处理设备文件的旧的经典方式。使用此方法，设备文件会持久地存储在根文件系统中（即它们在重新启动后仍然存在），并且没有任何自动创建和删除这些设备文件的机制，当硬件设备被添加或从系统中移除时。因此，Buildroot使用设备表创建一组标准的设备文件，其中默认的设备表存储在 `Buildroot` 源代码中的 `system/device_table_dev.txt` 中。当 `Buildroot` 生成最终的根文件系统映像时，会处理此文件，并且设备文件在 `output/target` 目录中不可见。 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 选项允许更改 `Buildroot` 使用的默认设备表，或添加附加的设备表，以便 `Buildroot` 在构建过程中创建附加的设备文件。因此，如果您使用此方法，并且您的系统中缺少设备文件，您可以创建一个 `board///device_table_dev.txt` 文件，其中包含您附加设备文件的描述，然后您可以将 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 设置为 `system/device_table_dev.txt board///device_table_dev.txt` 。有关设备表文件格式的更多详细信息，请参阅第25章。

- 第二种解决方案是仅使用动态的 `devtmpfs` 。 `devtmpfs` 是一个虚拟文件系统，它被内嵌在 Linux 内核中，从内核2.6.32开始引入(如果您使用较旧的内核，则无法使用此选项)。当它挂载在 `/dev` 上时，这个虚拟文件系统会自动使设备文件在添加或删除系统中的硬件设备时出现和消失。这个文件系统在重启后不是持久的:它是由内核动态填充的。使用 `devtmpfs` 需要启用以下内核配置选项: `CONFIG_DEVTMPFS` 和 `CONFIG_DEVTMPFS_MOUNT` 。当 `Buildroot` 负责为您的嵌入式设备构建 Linux 内核时，它会确保启用这两个选项。但是，如果您在 `Buildroot` 外部构建Linux内核，那么启用这两个选项就是您的责任(如果您未能启用它们，您的 `Buildroot` 系统将无法启动)。

- 第三种解决方案是使用动态的 `devtmpfs+mdev` 。这种方法也依赖于上述详细介绍的 `devtmpfs` 虚拟文件系统(所以内核配置中必须启用 `CONFIG_DEVTMPFS` 和 `CONFIG_DEVTMPFS_MOUNT` 这两个选项)，但在其上添加了 `mdev` 用户空间实用程序。 `mdev` 是 `BusyBox` 的一部分程序，内核将在设备添加或删除时调用它。通过 `/etc/mdev.conf` 配置文件，可以配置 `mdev` ，例如为设备文件设置特定的权限或所有权，或者在设备出现或消失时调用脚本或应用程序等。简而言之，它允许用户空间响应设备添加和删除事件。例如， `mdev` 可以自动加载当设备出现在系统上时需要的内核模块。如果设备需要固件， `mdev` 还负责将固件内容推送到内核。 `mdev` 是 `udev` 的一个轻量级实现(具有较少的功能)。有关 `mdev` 和其配置文件的语法的更多详细信息，请参阅 `http://git.busybox.net/-busybox/tree/docs/mdev.txt` 。

- 第四种解决方案是使用动态的 `devtmpfs+eudev` 。这种方法也依赖于上面详细介绍的 `devtmpfs` 虚拟文件系统，但在其上添加了 `eudev` 用户空间守护进程。 `eudev` 是一个后台运行的守护进程，它会被内核调用来响应系统中设备的添加或删除。它是 `mdev` 更重量级的解决方案，但提供了更高的灵活性。 `eudev` 是 `udev` 的独立版本， `udev` 原来是大多数桌面 Linux 发行版使用的用户空间守护进程，现在它成为 `Systemd` 的一部分。有关详细信息，请参阅http://en.wikipedia.org/wiki/Udev。

Buildroot开发人员的建议是从仅使用动态 `devtmpfs` 的解决方案开始，直到您需要用户空间被通知设备添加/删除，或者需要固件，此时使用动态 `devtmpfs+mdev` 通常是一个很好的解决方案。
需要注意的是，如果选择 `systemd` 作为 init 系统， `/dev` 管理将由 `systemd` 提供的 `udev` 程序进行。

### 6.3 init 系统
`init` 程序是内核启动的第一个用户空间程序(它的PID号是1)，它负责启动用户空间服务和程序(例如:Web服务器，图形应用程序，其他网络服务器等)。

`Buildroot` 允许使用三种不同类型的 `init` 系统，可以从 系统配置->初始化系统(`System configuration， Init system:`)中选择:

- 第一种解决方案是 `BusyBox` 。除了许多程序外， `BusyBox` 还实现了一个基本的 `init` 程序，对大多数嵌入式系统来说已经足够。启用 `BR2_INIT_BUSYBOX` 将确保 `BusyBox` 构建和安装其 `init` 程序。这是 `Buildroot` 的默认解决方案。`BusyBox init` 程序将在引导时读取 `/etc/inittab` 文件以知道下一个操作。此文件的语法可以在 `http://git.busybox.net/busybox/tree/examples/inittab` 找到(请注意，`BusyBox inittab` 语法是特殊的:不要使用互联网上的任何 `inittab` 文档来学习 `BusyBox inittab` )`。Buildroot` 默认的 `inittab` 存储在 `system/skeleton/etc/inittab` 。除了挂载几个重要的文件系统外，默认 `inittab` 的主要工作是启动 `/etc/init.d/rcS shell` 脚本，并启动 `getty` 程序(提供登录提示)。

- 第二种解决方案是 `systemV` 。这种解决方案使用传统的 `sysvinit` 程序，它被打包在 `Buildroot` 的 `package/sysvinit` 包中。这曾是大多数桌面 Linux 发行版使用的解决方案，直到它们转向更现代的替代方案如 `Upstart` 或 `Systemd` 。 `sysvinit` 也使用 `inittab` 文件(语法与 `BusyBox` 版本略有不同)。与此 `init` 解决方案一起安装的默认 `inittab` 位于 `package/sysvinit/inittab` 。

- 第三种解决方案是 `systemd` 。 `systemd` 是 Linux 新的一代 `init` 系统。它比传统的 init 程序功能更强大:支持高度并行化、使用 `socket` 和 `D-Bus` 激活启动服务、支持按需启动守护进程、使用 Linux 控制组跟踪进程状态等。 `systemd` 对相对复杂的嵌入式系统很有用，例如需要 `D-Bus` 和服务间通信的系统。需要注意的是， `systemd` 带来了大量依赖，如 `dbus、udev` 等。有关 `systemd` 的更多详细信息，请参阅 `http://www.freedesktop.org/wiki/Software/systemd` 。

Buildroot 开发人员建议使用 BusyBox init ，因为它对大多数嵌入式系统来说已经足够。对更复杂的情况下可以使用 systemd 。


## Chapter 7、其他组件的配置
修改下列任何组件之前，请确保您已经配置好Buildroot本身，并启用了对应的包。

**BusyBox**
- 如果您已经有 BusyBox 配置文件，可以直接在 Buildroot 配置中指定这个文件，使用 `BR2_PACKAGE_BUSYBOX_CONFIG` 。否则， Buildroot 将从默认的 BusyBox 配置文件开始
- 要对配置进行后续更改，使用 `make busybox-menuconfig` 打开 BusyBox 配置编辑器。
- 也可以通过环境变量指定BusyBox配置文件，但不建议这样做。有关更多详细信息，请参阅第8.6节。

**uClibc**
- uClibc的配置方式与BusyBox相同。指定现有配置文件的配置变量是 `BR2_UCLIBC_CONFIG` 。打开配置编辑器的命令是 `make uclibc-menuconfig` 。

**Linux Kernel**
- 如果您已经有内核配置文件，可以直接在 Buildroot 配置中指定这个文件，使用 `BR2_LINUX_KERNEL_USE_CUSTOM_CONFIG` 。
- 如果还没有内核配置文件，可以指定一个 `defconfig` 开始，使用 `BR2_LINUX_KERNEL_USE_DEFCONFIG` ，或者指定一个空文件作为自定义配置文件，使用 `BR2_LINUX_KERNEL_USE_CUSTOM_CONFIG` 。
- 要对配置进行后续更改，使用 `make linux-menuconfig` 打开 Linux 配置编辑器。

**Barebox**
-  Barebox 的配置方式与 Linux 内核相同。对应的配置变量是 `BR2_TARGET_BAREBOX_USE_CUSTOM_CONFIG` 和 `BR2_TARGET_BAREBOX_USE_DEFCONFIG` 。打开配置编辑器使用 `make barebox-menuconfig` 。

**U-Boot**
- U-Boot(版本2015.04或更高)的配置方式与 Linux 内核相同。对应的配置变量是 `BR2_TARGET_UBOOT_USE_CUSTOM_CONFIG` 和 `BR2_TARGET_UBOOT_USE_DEFCONFIG` 。打开配置编辑器使用 `make uboot-menuconfig` 。


## Chapter 8、Buildroot 的一般用法
### 8.1 make提示
这是利用Buildroot工作的一些提示汇总。

**显示 make 执行的所有命令:**

    $ make V=1 <目标>

**显示带defconfig的板列表:**

    $ make list-defconfigs

**显示所有可用目标:**

    $ make help

不是所有的目标都总是可用的，配置文件中的一些设置可能会隐藏某些目标:
- busybox-menuconfig 只在启用 busybox 时工作;
- linux-menuconfig 和 linux-savedefconfig 只在启用 linux 时工作;
- uclibc-menuconfig 只在选择内部工具链后端的 uClibc C 库时可用;
- barebox-menuconfig 和 barebox-savedefconfig 只在启用 barebox 引导程序时工作。
- uboot-menuconfig 和 uboot-savedefconfig 只在启用 U-Boot 引导程序且设置 uboot 构建系统为 Kconfig 时工作。

**Cleaning**: 当任何架构或工具链配置选项更改时，需要显式清理。
删除所有构建产品(包括构建目录、主机、交叉编译和目标树、镜像以及工具链):

    $ make clean

**生成手册**: 当前手册源码位于 docs/manual 目录。要生成手册:

    $ make manual-clean
    $ make manual 
手册输出将生成在output/docs/manual。（注意：有部分工具需要编译手册 (see: Section 2.2).）

**重置Buildroot用于新的目标**: 要删除所有构建产品以及配置:

    $ make distclean
注意:如果启用 ccache ，运行 make clean 或 distclean 不会清空 Buildroot 使用的编译器缓存。有关删除它的详细信息，请参阅第8.13.3节。

**转储内部make变量**: 可以转储make知道的变量及其值:

    $ make -s printvars VARS='VARIABLE1 VARIABLE2' 
    VARIABLE1=value_of_variable
    VARIABLE2=value_of_variable

可以使用一些变量来调整输出:
- `VARS` 将限定列表仅包含匹配指定 make 模式的变量名称 - 必须设置否则不打印任何内容
- `QUOTED_VARS` 如果设置为 YES ，单引号引起值  
- `RAW_VARS` 如果设置为 YES ，将打印未展开的值

例如:
```bash
$ make -s printvars VARS=BUSYBOX_%DEPENDENCIES
BUSYBOX_DEPENDENCIES=skeleton toolchain
BUSYBOX_FINAL_ALL_DEPENDENCIES=skeleton toolchain
BUSYBOX_FINAL_DEPENDENCIES=skeleton toolchain
BUSYBOX_FINAL_PATCH_DEPENDENCIES=
BUSYBOX_RDEPENDENCIES=ncurses util-linux
```
```bash
$ make -s printvars VARS=BUSYBOX_%DEPENDENCIES QUOTED_VARS=YES
BUSYBOX_DEPENDENCIES='skeleton toolchain'
BUSYBOX_FINAL_ALL_DEPENDENCIES='skeleton toolchain'
BUSYBOX_FINAL_DEPENDENCIES='skeleton toolchain'
BUSYBOX_FINAL_PATCH_DEPENDENCIES=''
BUSYBOX_RDEPENDENCIES='ncurses util-linux'
```
```bash
$ make -s printvars VARS=BUSYBOX_%DEPENDENCIES RAW_VARS=YES
BUSYBOX_DEPENDENCIES=skeleton toolchain
BUSYBOX_FINAL_ALL_DEPENDENCIES=$(sort $(BUSYBOX_FINAL_DEPENDENCIES) $( ←-
BUSYBOX_FINAL_PATCH_DEPENDENCIES))
BUSYBOX_FINAL_DEPENDENCIES=$(sort $(BUSYBOX_DEPENDENCIES))
BUSYBOX_FINAL_PATCH_DEPENDENCIES=$(sort $(BUSYBOX_PATCH_DEPENDENCIES))
BUSYBOX_RDEPENDENCIES=ncurses util-linux
```
引用变量的值输出可以在shell脚本中重用，例如:
```bash
$ eval $(make -s printvars VARS=BUSYBOX_DEPENDENCIES QUOTED_VARS=YES) $ echo $BUSYBOX_DEPENDENCIES
skeleton toolchain
```


### 8.2 理解何时需要全面重建
Buildroot 不会试图检测系统配置通过 `make menuconfig、make xconfig` 或其他配置工具更改后系统的哪些部分需要重建。在某些情况下， Buildroot 应该重建整个系统，在某些情况下，只需要重建特定子集的包。但是，以完全可靠的方式检测这一点是非常困难的，所以 Buildroot 开发人员决定不尝试这样做。
相反，识别何时需要全面重建的责任在于用户。作为提示，这里有一些经验法则可以帮助您理解如何使用Buildroot :

- 当目标架构配置更改时，需要完全重建。例如更改体系结构变体、二进制格式或浮点策略都会影响整个系统。
- 当工具链配置更改时，通常需要完全重建。通常涉及更改编译器版本、C库类型或配置等基本配置项的变更都会影响整个系统。
- 当向配置中添加额外包时，不一定需要完全重建。 Buildroot 会检测此包从未构建过，并将其构建。但是，如果此包是一个可选库，可能被已经构建的包使用， Buildroot 不会自动重建这些包。您要么知道哪些包需要重建并手动重建它们，要么应该进行完全重建。例如，假设您使用 Buildroot 构建了包含 ctorrent 包但不包含 openssl 的系统。系统可以运行，但您意识到需要为 ctorrent 添加 SSL 支持，所以在 Buildroot 配置中启用 openssl 包并重新启动构建。 Buildroot 会检测 openssl 需要构建，并构建它，但不会检测到 ctorrent 需要重建以利用 openssl 添加 SSL 支持。您要么进行完全重建，要么重新构建 ctorrent 本身。
- 当从配置中删除包时， Buildroot 不会做任何特殊操作。它不会从目标根文件系统或工具链 sysroot 中删除此包安装的文件。需要完全重建才能删除此包。但是，通常您不必立即删除这个包:您可以等待下次午休重新从头开始构建。 
- 当更改包的子选项时，包不会自动重建。在这样做后，通常只重建这个包就足够了，除非启用的包子选项为已经构建的另一个包添加了一些有用功能。同样， Buildroot 不会跟踪包何时需要重建:一旦包构建完毕，除非明确指示，否则它永远不会重建。
- 当对根文件系统骨架做更改时，需要完全重建。但是，如果仅更改根文件系统覆盖层、后构建脚本或后镜像脚本，则无需完全重建:简单调用 make 即可考虑变更。
- 当 `FOO_DEPENDENCIES` 中列出的包被重建或删除时，包 foo 不会自动重建。例如，如果包 bar 被列在 `FOO_DEPENDENCIES` 中 `FOO_DEPENDENCIES=bar` ，更改 bar 包配置不会自动重建包 foo 。在这种情况下，您可能需要重建引用 bar 依赖的任何包，或者进行完全重建以确保 bar 依赖包最新。

总的来说，如果构建错误且不确定配置更改的潜在影响，最好进行完全重建。如果得到相同错误，则可以确定错误与部分重建无关，如果错误来自官方 Buildroot 的包，不要犹豫地报告问题! 随着对 Buildroot 的经验累积，您将逐步了解何时真正需要完全重建，并将节省更多时间。

参考实现完全重建的方法是:

    $ make clean all

### 8.3 理解如何重建包
Buildroot用户最常问的问题之一是如何重建给定包或者如何删除包而不需要从头开始全面重建。

Buildroot不支持在不从头开始全面重建的情况下删除包。这是因为Buildroot没有跟踪哪个包将什么文件安装在 `output/staging` 和 `output/target` 目录中，或者哪个包在没有其他包的情况下会有不同的编译方式。

从头重建单个包的最简单方法是删除其 `output/build` 目录。 Buildroot 将重新提取、重新配置、重新编译并重新安装这个包。您可以使用 `make <package>-dirclean` 命令让 Buildroot 执行此操作。

另一方面，如果您只想从编译步骤重新启动包的构建过程，可以运行 `make <package>-rebuild` 。它将重新启动编译和安装包，但不是从头开始:它基本上是在包内重新执行 `make` 和 `make install` ，所以它只会重建已更改的文件。

如果您想从配置步骤重新启动包的构建过程，可以运行 `make <package>-reconfigure` 。它将重新启动配置、编译和安装包。

虽然 `<package>-rebuild` 意味着` <package>-reinstall` ， `<package>-reconfigure` 意味着 `<package>-rebuild` ，但是这些目标以及 `<package>` 本身只作用于指定的包，不会触发重新创建根文件系统镜像。如果需要重新创建根文件系统，应额外运行 make 或 make all 。

内部， Buildroot 通过所谓的印记文件跟踪每个包各个构建步骤的完成情况。它们存储在包构建目录 `output/build/<package>-<version>/` 中，命名为 `.stamp_<step-name>` 。

上述命令简单地操纵这些印记文件，强制Buildroot重新启动包构建过程的特定一组步骤。

有关包特殊make目标的更多详细信息请参阅第8.13.5节。


### 8.4 离线构建 
如果您打算进行离线构建，并只想下载之前在配置器(menuconfig、nconfig、xconfig或gconfig)中选择的所有源代码，则执行:

    $ make source
现在您可以断开连接或将 dl 目录的内容复制到构建主机。

### 8.5 外部树构建
默认情况下， Buildroot 构建的所有内容都存储在源码树下的 output 目录中。

Buildroot 还支持类似 Linux 内核的外部树构建语法。使用时，在 make 命令行添加O=<目录>:

    $ make O=/tmp/build menuconfig
或者:

    $ cd /tmp/build; make O=$PWD -C path/to/buildroot menuconfig

所有输出文件都将位于 `/tmp/build` 下。如果O路径不存在，Buildroot将创建它。

注意: O 路径可以是绝对路径或相对路径，但如果作为相对路径传递，它相对于主 Buildroot 源代码目录进行解释，而不是当前工作目录。

使用外部树构建时，Buildroot 的 `.config` 和临时文件也存储在输出目录中。这意味着您可以安全地在相同源代码树下并行运行多个构建，只要它们使用唯一的输出目录。

为方便使用，Buildroot 在输出目录生成一个 Makefile 包装器-所以后续调用，不再需要传递 `O=<...>` 和 `-C <...>` ，在输出目录简单运行:

    $ make <target>


### 8.6 环境变量
Buildroot还支持通过传递给make或设置在环境中的一些环境变量:
- `HOSTCXX` ，用于主机C++编译器
- `HOSTCC` ，用于主机C编译器  
- `UCLIBC_CONFIG_FILE=<path/to/.config>` ，uClibc 配置文件的路径，用于编译内部工具链中的uClibc。  
注意 uClibc 配置文件也可以通过配置界面设置，通过Buildroot的.config文件设置是推荐的方法。
- `UCLIBC_CONFIG_FILE=<path/to/.config>` ，BusyBox 配置文件的路径。  
注意BusyBox配置文件也可以通过配置界面设置，通过Buildroot的.config文件设置是推荐的方法。
- `BR2_CCACHE_DIR` 覆盖 Buildroot 存储 ccache 缓存文件的目录。
- `BR2_DL_DIR` 覆盖 Buildroot 存储/获取下载文件的目录。  
注意下载目录也可以通过配置界面设置，通过Buildroot的.config文件设置。第8.13.4节中有更多关于如何设置下载目录的详细信息。
- `BR2_GRAPH_ALT` ，如果设置并非空，使用替代颜色方案绘制构建时图。
- `BR2_GRAPH_OUT` 设置生成图的文件类型，pdf(默认)或png。
- `BR2_GRAPH_DEPS_OPTS` 传递额外选项给依赖关系图，第8.9节中接受的选项。  
- `BR2_GRAPH_DOT_OPTS` 直接作为选项传递给dot实用程序绘制依赖关系图。
- `BR2_GRAPH_SIZE_OPTS` 传递额外选项给大小图，第8.11节中接受的选项。

例如使用位于顶级目录和 $HOME 中的配置文件:

    $ make UCLIBC_CONFIG_FILE=uClibc.config BUSYBOX_CONFIG_FILE=$HOME/bb.config
如果想使用其他于默认的gcc或g++编译主机助手二进制文件:

    $ make HOSTCXX=g++-4.3-HEAD HOSTCC=gcc-4.3-HEAD


### 8.7 有效处理文件系统镜像
文件系统镜像大小取决于选择的文件系统、包数量以及是否预留了空间等因素，可能会很大。然而，文件系统镜像中的某些位置可能为空(例如一长串零)；这样的文件称为稀疏文件。

大多数工具都可以有效处理稀疏文件，仅存储或写入稀疏文件中非空部分的内容。

例如:
- tar接受-S选项告诉它仅存储稀疏文件的非零块:
  - `tar cf archive.tar -S [files...]` 将稀疏文件有效存储在 tar 包中
  - `tar xf archive.tar -S` 将从 tar 包有效提取稀疏文件
- cp 接受 --sparse=WHEN 选项( WHEN 取 auto、never或always ):
  - `cp --sparse=always source.file dest.file` 将 dest.file 设置为稀疏文件(如果source.file有长串零)

其他工具可能有类似选项，请查询其man手册。

您可以使用稀疏文件如果需要存储(例如传输到另一台机器)或发送(例如给QA团队)文件系统镜像。

但是，使用 dd 的稀疏模式将文件系统镜像刷入设备可能会导致文件系统损坏(例如ext2的块位图被破坏;或者文件系统中的稀疏文件在读回时可能不是全零)。仅在处理构建机上的文件时使用稀疏文件，不应将其传输到实际设备上。

### 8.8 关于包的详细信息
Buildroot可以生成描述当前配置下启用包及其依赖关系、许可证和其他元数据的JSON概述。通过使用show-info目标可以生成:

    make show-info
Buildroot 还可以使用 pkg-stats 目标生成关于包的 HTML 和 JSON 详细信息，包括是否存在影响当前配置包的已知 CVE(安全漏洞)，以及是否有更新的上游版本。

    make pkg-stats

### 8.9 绘制包之间的依赖关系图 
Buildroot的职责之一是了解包之间的依赖关系，并确保它们按正确顺序构建。这些依赖关系有时非常复杂，对于给定系统，通常很难理解Buildroot为什么带入某个包。

为了帮助理解依赖关系，从而更好地了解嵌入式Linux系统各组件的作用，Buildroot可以生成依赖关系图。
要生成整个已编译系统的依赖关系图，简单运行:

    make graph-depends
生成的图位于output/graphs/graph-depends.pdf。

如果系统非常大，依赖关系图可能过于复杂难以阅读。所以可以生成给定包的依赖关系图:

    make <pkg>-graph-depends 
生成的图位于output/graph/<pkg>-graph-depends.pdf。

注意依赖关系图使用Graphviz项目的dot工具生成，您必须在系统中安装此工具才能使用此功能。在大多数发行版中它作为graphviz软件包提供。

默认情况下，依赖关系图使用PDF格式生成。但是通过设置 `BR2_GRAPH_OUT` 环境变量，可以切换到其他格式，如PNG、PostScript或SVG。dot工具的-T选项支持的所有格式都支持。

    BR2_GRAPH_OUT=svg make graph-depends

可以通过设置BR2_GRAPH_DEPS_OPTS环境变量控制graph-depends行为。
支持的选项有:
- --depth N， -d N，限制依赖深度到N层。默认0表示无限制。
- --stop-on PKG， -s PKG，在包PKG停止图。PKG可以是实际包名、通配符、关键字virtual(停止在虚拟包)或host(停止在主机包)。PKG仍在图上，但其依赖不绘制。
- --exclude PKG， -x PKG，同--stop-on，但也从图中排除PKG。
- --transitive，--no-transitive，绘制(或不绘制)传递性依赖。默认不绘制传递性依赖。
- --colors R，T，H，用逗号分隔的颜色绘制根包(R)、目标包(T)和主机包(H)。默认:lightblue，grey，gainsboro
> BR2_GRAPH_DEPS_OPTS='-d 3 --no-transitive --colors=red，green，blue' make graph-depends

### 8.10 绘制构建持续时间的图表
当系统的构建时间很长时，有时候能够了解哪些软件包的构建时间最长是很有用的，以便查看是否可以采取措施加快构建速度。为了帮助进行构建时间分析，Buildroot会收集每个软件包每个步骤的构建时间，并允许从这些数据中生成图表。

在构建完成后生成构建时间图表，运行以下命令：

    make graph-build

这将在 `output/graphs` 目录下生成一组文件：
- build.hist-build.pdf ，按构建顺序排列的每个软件包的构建时间直方图。
- build.hist-duration.pdf ，按持续时间排序的每个软件包的构建时间直方图（最长的排在前面）。
- build.hist-name.pdf ，按软件包名称排序的每个软件包的构建时间直方图。
- build.pie-packages.pdf ，每个软件包的构建时间的饼图。
- build.pie-steps.pdf ，软件包构建过程中每个步骤的总时间的饼图。

这个graph-build目标需要安装Python的Matplotlib和Numpy库（大多数发行版上-matplotlib和python-numpy），如果使用的是Python版本低于2.7，则还需要安装argparse模块（大多数发行版上是python-argparse）。

默认情况下，图表的输出格式是PDF，但可以使用BR2_GRAPH_OUT环境变量选择不同的格式。唯一支持的其他格式是PNG：

    BR2_GRAPH_OUT=png make graph-build


### 8.11 绘制软件包对文件系统大小的贡献的图表
当目标系统增长时，有时候了解每个Buildroot软件包对整个根文件系统大小的贡献有多大是很有用的。为了帮助进行这样的分析，Buildroot会收集每个软件包安装的文件的数据，并使用这些数据生成一个图表和CSV文件，详细说明不同软件包的大小贡献。

在构建完成后生成这些数据，运行以下命令：

    make graph-size

这将生成：
- output/graphs/graph-size.pdf ，每个软件包对整个根文件系统大小的贡献的饼图。
- output/graphs/package-size-stats.csv ，一个CSV文件，给出每个软件包对整个根文件系统大小的贡献。
- output/graphs/file-size-stats.csv ，一个CSV文件，给出每个安装文件对所属软件包和整个文件系统大小的贡献。

这个graph-size目标需要安装Python的Matplotlib库（大多数发行版上是python-matplotlib），如果使用的是Python版本低于2.7，则还需要安装argparse模块（大多数发行版上是python-argparse）。

与持续时间图表一样，支持 `BR2_GRAPH_OUT` 环境变量来调整输出文件格式。有关此环境变量的详细信息，请参见第8.9节。

此外，还可以设置环境变量 `BR2_GRAPH_SIZE_OPTS` 来进一步控制生成的图表。接受的选项有：
- --size-limit X，-l X，将所有个别贡献低于X百分比的软件包分组到一个标记为“Others”的条目中。默认情况下，X=0.01，这意味着每个贡献少于1%的软件包都被分到“Others”下。接受的值范围为[0.0..1.0]。
- --iec，--binary，--si，--decimal，使用IEC（二进制，1024的幂）或SI（十进制，1000的幂；默认）前缀。
- --biggest-first，按大小递减顺序排序软件包，而不是按大小递增顺序排序。

注意：收集的文件系统大小数据只有在完全清除重建之后才有意义。在使用 `make graph-size` 之前，请确保运行 `make clean all` 。

要比较两个不同的Buildroot编译的根文件系统大小，例如在调整配置或切换到另一个Buildroot版本后，请使用 `size-stats-compare` 脚本。它接受两个 `file-size-stats.csv` 文件（由make graph-size生成）作为输入。有关此脚本的更多详细信息，请参考其帮助文本：

    utils/size-stats-compare -h


### 8.12 顶层并行构建
注意：本节介绍的是一个非常实验性的功能，即使在一些非常规情况下也可能出现故障。请自行承担风险。

Buildroot一直能够在软件包的基础上使用并行构建：Buildroot使用 make -jN（或非基于make的构建系统的等效调用）构建每个软件包。并行度默认为CPU数量+1，但可以使用 `BR2_JLEVEL` 配置选项进行调整。

直到2020.02，Buildroot仍然以串行方式构建软件包：每个软件包一个接一个地构建，没有在软件包之间并行化构建。从2020.02开始，Buildroot实验性地支持顶层并行构建，通过并行构建没有依赖关系的软件包，可以节省大量构建时间。但是，该功能被标实验性的，并且已知在某些情况下无法正常工作。

要使用顶层并行构建，必须：
1. 在Buildroot配置中启用选项 `BR2_PER_PACKAGE_DIRECTORIES`
2. 在启动Buildroot构建时使用 `make -jN `

在内部， `BR2_PER_PACKAGE_DIRECTORIES` 将启用一种称为每个软件包（`per-package directories`）的机制，它将产生以下效果：
- 不再使用全局目标目录和全局主机目录，而是使用每个软件包的标和主机目录，分别位于 `$(O)/per-package/<pkg>/target/` 和 ` $(O)/per-package/<pkg>/host/` 。 这些文件夹将在构建开始时从软件包依赖项的相应文件夹中填充。因此，编译器和所有其他工具只能看到和访问由显式列出的依赖项安装的文件。
- 在构建结束时，将填充全局目标和主机目录，位于 `$(O)/target` 和 `(O)/host` 中。这意味着在构建过程中，这些文件夹将为空，只有在构建的最后阶段它们才会被填充。


### 8.13 高级用法
#### 8.13.1 
在Buildroot之外使用生成的工具链 您可能希望为目标平台编译自己的程序或其他未打包在Buildroot中的软件。为了做到这一点，您可以使用Buildroot生成的工具链。

Buildroot生成的工具链默认位于 `output/host/` 。使用它的最简单方法是将 `output/host/bin/` 添加到您的PATH环境变量中，然后使用 ARCH-linux-gcc、ARCH-linux-objdump、ARCH-linux-ld等命令。

另外，Buildroot还可以通过运行make sdk命令将所有选定软件包的工具链和开发文件作为SDK导出。这将生成一个tarball，其中包含主机目录output/host/的内容，命名为_sdk-buildroot.tar.gz（可以通过设置环境变量BR2_SDK_PREFIX进行覆盖），位于output/images/目录中。然后，可以将此tarball分发给应用程序开发人员，当他们想要开发尚未打包为Buildroot软件包的应用程序时使用。

在提取SDK tarball后，用户必须运行relocate-sdk.sh脚本（位于SDK的顶级目录），以确保所有路径都更新为新位置。 另外，如果您只想准备SDK而不生成tarball（例如，因为您将只移动主机目录，或者将自己生成tarball），Buildroot还允许您只使用make prepare-sdk来准备SDK，而不实际生成tarball。

为了方便起见，通过选择选项BR2_PACKAGE_HOST_ENVIRONMENT_SETUP，您可以在output/host/中（因此也在您的SDK中）安装一个environment-setup脚本。可以使用. your/sdk/path/environment-setup命令来源化此脚本，以导出一些环境变量，以帮助使用Buildroot SDK交叉编译项目：PATH将包含SDK二进制文件，标准autotools变量将定义为适当的值，CONFIGURE_FLAGS将包含基本的，用于交叉编译autotools项目。它还提供一些有用的命。但请注意，一旦源化此脚本，境仅为交叉编译设置，不再适用于本机编译。

#### 8.13.2 在Buildroot中使用gdb
Buildroot允许进行交叉调试，其中调试器在构建机上运行，并与目标上的gdbserver通信以控制程序的执行。 要实现这一点：
- 如果您使用的是内部工具链（由Buildroot构建），您必须启用BR2_PACKAGE_HOST_GDB、BR2_PACKAGE_GDB和BR2_PACKAGE_GDB_SERVER。这确保同时构建交叉gdb和gdbserver，并将gdbserver安装到目标上。
- 如果您使用的是外部工具链，您应该启用BR2_TOOLCHAIN_EXTERNAL_GDB_SERVER_COPY，它将外部工具链中包含的gdbserver复制到目标上。如果您的外部工具链没有交叉gdb或gdbserver，也可以让Buildroot构建它们，方法是启用与内部工具链后端相同的选项。

现在，要开始调试名为foo的程序，您应该在目标上运行以下命令：

    gdbserver :2345 foo
这将导致gdbserver在TCP5上监听来自交叉gdb的连接。

然后，在主机上，您应该使用以下命令行启动交叉gdb：

    <buildroot>/output/host/bin/<tuple>-gdb -ix <buildroot>/output/staging/usr/share/buildroot/
    gdbinit foo

当然，foo必须在当前目录中可用，并带有调试符号。通常，您从构建foo的目录中启动此命令（是从output/target/中启动，因为该目录中的二进制文件已被剥离）。

`/output/staging/usr/share/buildroot/gdbinit` 文件将告诉交叉gdb如何找到目标的库。 最后，要从交叉gdb连接到目标：

    (gdb) target remote <target ip address>:2345

#### 8.13.3 在Buildroot中使用ccache
ccache是编译器缓存。它存储每个编译过程产生的对象文件，并能够通过使用预存对象文件跳过相同源文件(使用相同编译器和相同参数)的后续编译。对于从零开始几次进行几乎相同的构建，它可以很好地加速构建过程。
Buildroot集成了ccache支持。只需在构建选项中启用编译器缓存即可。这将自动构建ccache并在每个主机和目标编译中使用它。

缓存位于BR2_CCACHE_DIR配置选项定义的目录中，默认为 `$HOME/.buildroot-ccache` 。这个默认位置位于Buildroot输出目录外，所以不同的Buildroot构建可以共享它。如果想清除缓存，只需删除这个目录。
可以通过运行make ccache-stats获取缓存统计信息(其大小、命中数、未命中数等)。

make目标ccache-options和CCACHE_OPTIONS变量提供对ccache更通用的访问。例如:

    # set cache limit size
    make CCACHE_OPTIONS="--max-size=5G" ccache-options
    # zero statistics counters
    make CCACHE_OPTIONS="--zero-stats" ccache-options

ccache对源文件和编译器选项生成哈希值。如果编译器选项不同，缓存的对象文件将不会使用。然而，许多编译器选项包含指向交叉编译目录的绝对路径。因此，在不同输出目录下构建会导致许多未命中。

为避免此问题，Buildroot提供Use relative paths选项(BR2_CCACHE_USE_BASEDIR)。它将所有指向输出目录内部的绝对路径重写为相对路径。因此改变输出目录不再导致未命中。

相对路径的缺点是对象文件中的路径也变成相对路径。例如，调试器在未cd到输出目录前无法找到文件。

有关在不同目录下编译的详细信息，请参阅ccache手册中的“Compiling in different directories”部分。

在Buildroot使用BR2_CCACHE=y选项启用ccache时:
- ccache在Buildroot自身构建中使用
- ccache在Buildroot外构建时(如直接调用交叉编译器或使用SDK)不使用

可以通过BR2_USE_CCACHE环境变量覆盖此行为:设置为1时启用ccache(Buildroot构建默认)，未设置或设置不同值时禁用ccache。

#### 8.13.4 下载包位置  
Buildroot下载的各种tar包都存储在BR2_DL_DIR中，默认为dl目录。如果要保存一个已知与相关tar包兼容的完整Buildroot版本，可以复制这个目录。这样就可以使用完全相同版本重新生成工具链和目标文件系统。

如果维护多个Buildroot树，最好使用共享下载位置。可以通过设置BR2_DL_DIR环境变量指向一个目录实现此目的。如果设置了这个变量，则覆盖Buildroot配置中的BR2_DL_DIR值。应添加以下行到<~/.bashrc>中:

    export BR2_DL_DIR=<shared download location>
下载位置也可以通过BR2_DL_DIR选项在.config文件中设置。与.config文件中的大多数选项不同，.config文件中的这个值会被BR2_DL_DIR环境变量覆盖。

#### 8.13.5 包特定的make目标
运行 make <package> 构建和安装该特定包及其依赖。

对于依赖Buildroot基础架构的包，有许多可以单独如下调用的特殊make目标:

    make <package>-<target>

包构建目标(按执行顺序):

|命令/目标 |说明|
|---|---|
|source |获取源码(下载tarball，克隆源代码仓库等) |
|depends |构建和安装构建该包所需的所有依赖|
|extract |将源码放入包构建目录(解压tarball，复制源码等)|
|patch |应用补丁(如果有)|
|configure |运行配置命令(如果有)|
|build |运行编译命令|
|install-staging |目标包:在交叉编译目录安装(如果需要)|
|install-target |目标包:在目标目录安装(如果需要)  |
|install |目标包:运行前两个安装命令|
|host |包:在主机目录安装|

此外还有一些其他有用的make目标:
|命令/目标 |说明|
|---|---|
|show-depends |显示构建该包第一个顺序依赖|
|show-recursive-depends |递归显示构建该包所需的所有依赖 |
|show-rdepends |显示该包直接依赖的第一个反向依赖(直接依赖它的包)|
|show-recursive-rdepends |递归显示该包的所有反向依赖(直接或间接依赖它的包)|
|graph-depends |生成该包在当前Buildroot配置下的依赖关系图，详见本节关于依赖关系图的内容|
|graph-rdepends |生成该包的反向依赖关系图 |
|dirclean |删除整个包构建目录|
|reinstall |重新运行安装命令|
|rebuild |重新运行编译命令 - 只在使用OVERRIDE_SRCDIR功能或者直接在构建目录修改文件时有意义|
|reconfigure |重新运行配置命令，然后重新编译 - 也只在使用OVERRIDE_SRCDIR功能或者直接在构建目录修改文件时有意义|

#### 8.13.6 在开发过程中使用Buildroot
Buildroot正常操作是下载一个 tarball ，解压它，配置、编译和安装tarball内的软件组件。源代码被解压到 `output/build/<package>-<version>` 这个临时目录:每次 `make clean` 都会完全删除这个目录，在下次 make 调用时重新创建。即使源代码来自 Git 或 Subversion 仓库，Buildroot也会从中生成一个tarball，然后进行正常与tarball一样的操作。

这种行为对于主要使用Buildroot作为集成工具来构建和集成嵌入式Linux系统的组件来说是很好的。但是，如果在系统的某些组件开发过程中使用Buildroot，这种行为就不太方便了:开发者希望能对一个包的源代码做小修改，然后使用Buildroot快速重新构建系统。

直接在 `output/build/<package>-<version>` 修改源代码不是一个很好的解决方案，因为这个目录在make clean时会被删除。

因此，Buildroot提供了一个特定机制来解决这个用例: `<pkg>_OVERRIDE_SRCDIR` 机制。Buildroot读取一个覆盖文件，允许用户告诉Buildroot某些包的源代码位置。

覆盖文件的默认位置是 `$(CONFIG_DIR)/local.mk` ，通过 `BR2_PACKAGE_OVERRIDE_FILE` 配置选项定义。 `$(CONFIG_DIR)` 是 Buildroot 的 .config 文件位置，所以默认 local.mk 和 .config 文件并存，即:
- 对于内嵌树构建(不使用O=)，local.mk 和 .config 在 Buildroot 源代码顶层目录
- 对于外部树构建(使用O=)， local.mk 和 .config 在外部目录

如果需要其他位置，也可以通过 `BR2_PACKAGE_OVERRIDE_FILE` 配置选项指定。
在这个覆盖文件中，Buildroot期望找到如下格式的行:

    <pkg1>_OVERRIDE_SRCDIR = /pkg1源代码路径
    <pkg2>_OVERRIDE_SRCDIR = /pkg2源代码路径

例如:

    LINUX_OVERRIDE_SRCDIR = /home/bob/linux/  
    BUSYBOX_OVERRIDE_SRCDIR = /home/bob/busybox/

当Buildroot找到某个包定义了 `<pkg>_OVERRIDE_SRCDIR` ，它将不再尝试下载、解压和修补这个包，而是直接使用指定目录下的源代码。 `make clean` 也不会清理这个目录。这允许指向使用版本控制的自己的目录。Buildroot使用rsync将源代码从指定目录复制到 `output/build/<package>-custom/` 。

最好与 `make <pkg>-rebuild` 和 `make <pkg>-reconfigure` 目标一起使用。make <pkg>-rebuild all将只同步修改的文件，然后重新构建这个包。

这样开发者就可以在 `/home/bob/linux` 做修改，然后运行 `make linux-rebuild` 完成快速构建:

    make linux-rebuild all
    
几秒钟就可以在 `output/images` 得到更新后的Linux内核镜像。同样，可以在 `/home/bob/busybox` 做BusyBox源代码修改，然后:

    make busybox-rebuild all
output/images中的根文件系统镜像就包含了更新后的BusyBox。

大项目源代码树通常包含数百上千个不需要构建但会减慢rsync复制速度的文件。可以选择定义<pkg>_OVERRIDE_SRCDIR_RSYNC_EXCLUSIONS跳过从源代码树同步某些文件。例如在webkitgtk包上工作时:

    WEBKITGTK_OVERRIDE_SRCDIR = /home/bob/WebKit
    WEBKITGTK_OVERRIDE_SRCDIR_RSYNC_EXCLUSIONS = \
        --exclude JSTests --exclude ManualTests --exclude PerformanceTests \ 
        --exclude WebDriverTests --exclude WebKitBuild --exclude WebKitLibraries \
        --exclude WebKit.xcworkspace --exclude Websites --exclude Examples

默认Buildroot跳过VCS版本控制元数据同步(如.git .svn目录)。但有些包希望这些目录在构建时可用，例如自动获取精确提交哈希作为版本信息。要取消此过滤可以添加这些目录:

    LINUX_OVERRIDE_SRCDIR_RSYNC_EXCLUSIONS = --include .git



## Chapter 9、 项目专用定制
对给定项目可能需要进行的典型操作:
- 配置Buildroot(包括构建选项、工具链、引导程序、内核、包和文件系统镜像类型选择)
- 配置其他组件，如Linux内核和BusyBox 
- 自定义生成的目标文件系统
    - 添加或覆写目标文件系统文件(使用BR2_ROOTFS_OVERLAY)
    - 修改或删除目标文件系统文件(使用BR2_ROOTFS_POST_BUILD_SCRIPT)  
    - 在生成文件系统镜像前运行任意命令(使用BR2_ROOTFS_POST_BUILD_SCRIPT)
    - 设置文件权限和所有者(使用BR2_ROOTFS_DEVICE_TABLE)
    - 添加自定义设备节点(使用BR2_ROOTFS_STATIC_DEVICE_TABLE)
- 添加自定义用户帐户(使用BR2_ROOTFS_USERS_TABLES)
- 生成文件系统镜像后运行任意命令(使用BR2_ROOTFS_POST_IMAGE_SCRIPT)
- 为某些包添加项目专用补丁(使用BR2_GLOBAL_PATCH_DIR)
- 添加项目专用包

关于这样的项目专用定制，请仔细考虑哪些变更确实项目专用，哪些变更也对其他项目开发者有用。强烈建议和鼓励将改进、包和板支持上游到官方Buildroot项目。当然，有时不可能或不可取上游，因为变更过于专用或专有。

本章描述如何在Buildroot中进行这样的项目专用定制，以及如何存储定制内容以便在运行make clean后以可重复方式构建相同镜像。遵循推荐策略，甚至可以使用同一个Buildroot树构建多个不同项目!

### 9.1 推荐目录结构
定制Buildroot项目时，需要存储一些项目专用文件。这些文件可以放任何位置，但Buildroot开发者推荐以下目录结构:

可以选择这个结构是否放在Buildroot树内，还是使用br2-external树放外部。两种方式都可以，取决于个人选择。
```
+-- board/
| +-- <company>/
| +-- <boardname>/
| +-- linux.config
| +-- busybox.config
| +-- <other configuration files>
| +-- post_build.sh
| +-- post_image.sh
| +-- rootfs_overlay/
| | +-- etc/
| | +-- <some files>
| +-- patches/
| +-- foo/
| | +-- <some patches>
| +-- libbar/
| +-- <some other patches> |
+-- configs/
| +-- <boardname>_defconfig
|
+-- package/
| +-- <company>/
| +-- Config.in (if not using a br2-external tree)
| +-- <company>.mk (if not using a br2-external tree)
| +-- package1/
| | +-- Config.in
| | +-- package1.mk
| +-- package2/
| +-- Config.in
| +-- package2.mk
|
+-- Config.in (if using a br2-external tree)
+-- external.mk (if using a br2-external tree)
+-- external.desc (if using a br2-external tree)
```
上面显示的文件细节将在本章后面给出。

注意:如果选择将这个结构放在Buildroot树外但使用br2-external树， <company> 和可能的 <boardname> 组件可能是多余的，可以省略。

#### 9.1.1 实现分层定制
对于有几个相关项目但部分需要相同定制的用户来说，使用分层定制方法是很常见的，如本节所述。

Buildroot提供的大多数定制方法，如后置脚本和根文件系统覆盖层，都可以接受空格分隔的多项列表。指定的多项总是从左到右顺序处理。通过创建一个定制项用于通用定制，另一个定制项用于真正项目专用定制，可以避免不必要的重复。每个层面通常用一个单独的目录表示，位于 board/<company>/ 下。根据项目不同，甚至可以引入更多层面。

例如有两个定制层common和fooboard的目录结构:
```
+-- board/
    +-- <company>/
        +-- common/
        | +-- post_build.sh
        | +-- rootfs_overlay/
        | | +-- ...
        | +-- patches/
        |   +-- ...
        |
        +-- fooboard/
            +-- linux.config
            +-- busybox.config
            +-- <other configuration files>
            +-- post_build.sh
            +-- rootfs_overlay/
            | +-- ...
            +-- patches/
                +-- ...
```
例如，如果用户将BR2_GLOBAL_PATCH_DIR配置选项设置为:

    BR2_GLOBAL_PATCH_DIR="board/<company>/common/patches board/<company>/fooboard/patches"

那么首先会应用common层中的补丁，然后再应用fooboard层中的补丁。

### 9.2 将定制内容保持在Buildroot外部
如9.1节中简要提到，可以将项目专用定制放在以下两个位置:
- 直接放在Buildroot树内，通常使用版本控制系统的分支来维护，这样升级到新Buildroot版本就很容易。
- 放在Buildroot树外，使用br2-external机制。这个机制允许将包recipes、板支持和配置文件保持在Buildroot树外，同时在构建逻辑中很好地集成。我们称这个位置为br2-external树。本节将介绍如何使用br2-external机制以及在br2-external树中应提供什么内容。

可以通过设置BR2_EXTERNAL变量来告诉Buildroot使用一个或多个br2-external树。它可以传给任何Buildroot构建。自动保存在输出目录下隐藏的.br2-external.mk文件中。这样每次构建就不必传BR2_EXTERNAL了。但随时可以通过传新的路径值来改变，也可以通过传空值来删除。 

BR2_EXTERNAL路径可以是绝对路径也可以是相对路径。如果是相对路径，它相对于Buildroot源代码目录的，而不是输出目录。

如果使用旧版本br2-external树，需要转换后才能在Buildroot 2016.11及更高版本使用。具体见27.2节。

一些例子:
    
    buildroot/ $ make BR2_EXTERNAL=/path/to/foo menuconfig

从现在起，将使用 /path/to/foobr2 外部树中的定义：

    buildroot/ $ make
    buildroot/ $ make legal-info

我们可以随时切换到另一个 br2 外部树：

    buildroot/ $ make BR2_EXTERNAL=/where/we/have/bar xconfig

我们还可以使用多个 br2 外部树：

    buildroot/ $ make BR2_EXTERNAL=/path/to/foo:/where/we/have/bar menuconfig

或者不使用任何 br2 外部树：
    
    buildroot/ $ make BR2_EXTERNAL= xconfig


#### 9.2.1 外部树的布局
br2-external 树必须包含至少以下三个文件，下章将对它们进行描述:
- external.desc
- external.mk 
- Config.in

除了这些强制性文件外，br2-external 树中还可以包含其他可选内容，比如 `configs/` 或 `provides/` 目录。下文同样对它们进行描述。

本章最后还描述了一个完整的 br2-external 树布局示例。

##### 9.2.1.1 external.desc 文件
该文件描述 br2-external 树:为该 br2-external 树指定名称和描述。

该文件采用基于行的格式，每行由关键字开头，后跟冒号和一个或多个空格，再跟该关键字的值。目前只识别两个关键字:
- name，强制，为该 br2-external 树指定名称。名称只能使用ASCII字符集中的[A-Za-z0-9_]字符;其它任何字符都禁止使用。Buildroot会设置 `BR2_EXTERNAL_$(NAME)_PATH` 变量，指定 br2-external 树的绝对路径，这样您就可以使用它来引用您的br2-external树。这个变量既在Kconfig中可用，用于源代码Kconfig文件(见下文)，也在Makefile中可用，用于包含其他Makefile或引用br2-external树中的其他文件(如数据文件)。  
注意:由于可以同时使用多个br2-external树，Buildroot会使用这个名称为每个树生成变量。这个名称用来标识您的br2-external树，所以请尽量取一个真正描述您br2-external树的名称，以使其相对唯一，避免与其他br2-external树的名称冲突，特别是如果您计划与第三方共享br2-external树，或者使用来自第三方的br2-external树。

- desc，可选，为该br2-external树提供简短描述。应限于单行，格式较为自由(见下文)，用于显示br2-external树相关信息(如配置列表上方或菜单配置中的提示);因此，描述应相对简短(40字符左右就可以了)。描述存储在BR2_EXTERNAL_$(NAME)_DESC变量中。

例如名称及对应的BR2_EXTERNAL_$(NAME)_PATH变量:
- FOO → BR2_EXTERNAL_FOO_PATH
- BAR_42 → BR2_EXTERNAL_BAR_42_PATH

以下示例假设名称设置为BAR_42。

注:BR2_EXTERNAL_$(NAME)_PATH和BR2_EXTERNAL_$(NAME)_DESC变量既在Kconfig文件也在Makefile中可用。它们也会导出到环境中，因此在后构建、后镜像和伪根脚本中也可用。

##### 9.2.1.2 Config.in 和 external.mk 文件
这两个文件(各自可以为空)可以用于定义软件包recipes(即类似Buildroot内置软件包的foo/Config.in和foo/foo.mk)或其他自定义配置选项或make逻辑。

Buildroot会自动包含每个br2-external树中的Config.in，使其出现在顶层配置菜单中，并包含每个br2-external树中的external.mk，将其与其他make逻辑一起包含。

主要用途是存储软件包recipes。推荐的做法是编写类似以下格式的Config.in文件:

    source "$BR2_EXTERNAL_BAR_42_PATH/package/package1/Config.in"
    source "$BR2_EXTERNAL_BAR_42_PATH/package/package2/Config.in"

随后，有一个 external.mk 的文件如下：

    include $(sort $(wildcard $(BR2_EXTERNAL_BAR_42_PATH)/package/*/*.mk))

然后在 `$(BR2_EXTERNAL_BAR_42_PATH)/package/package1` 和 `$(BR2_EXTERNAL_BAR_42_PATH)/package/package2` 创建正常的 Buildroot 软件包 recipes ，如第18章所解释。或者，您也可以将软件包分组到名为 <boardname> 的子目录中，相应调整上述路径。

您也可以在Config.in中定义自定义配置选项，在external.mk中定义自定义make逻辑。

##### 9.2.1.3 configs/目录 
可以在br2-external树的configs子目录中存储Buildroot defconfig文件。Buildroot会自动在make list-defconfigs输出中显示它们，并允许通过正常的make <名称>_defconfig命令加载它们。它们会出现在make list-defconfigs输出下方带有br2-external树名称的“External configs”标签下。

注意:如果一个defconfig文件存在于多个br2-external树中，则使用最后一个br2-external树中的文件。因此可以覆盖Buildroot或其他br2-external树打包的defconfig文件。

##### 9.2.1.4 provides/目录
对于一些软件包，Buildroot会提供在API兼容的软件包之间选择两个(或更多)实现版本的选择。例如，可以选择libjpeg或者jpeg-turbo;可以选择openssl或者libressl;可以选择预配置的工具链......
br2-external可以扩展这些选择，通过提供一组定义这些替代方案的文件:
- provides/toolchains.in定义预配置的工具链，它们将在工具链选择中列出;
- provides/jpeg.in定义libjpeg替代实现;
- provides/openssl.in定义openssl替代实现;
- provides/skeleton.in 定义骨架(skeleton)替代实现;
- provides/init.in定义init系统替代实现，可以用于选择默认的init系统骨架。

##### 9.2.1.5 自由形式内容
可以在这里存储所有板级特定的配置文件，如内核配置、根文件系统覆盖层或者Buildroot允许设置位置的任何其他配置文件(通过使用BR2_EXTERNAL_$(NAME)_PATH变量)。例如，可以如下设置全局补丁目录、根文件系统覆盖层和内核配置文件的路径(例如通过运行make menuconfig并填写这些选项):

    BR2_GLOBAL_PATCH_DIR=$(BR2_EXTERNAL_BAR_42_PATH)/patches/
    BR2_ROOTFS_OVERLAY=$(BR2_EXTERNAL_BAR_42_PATH)/board/<boardname>/overlay/  
    BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE=$(BR2_EXTERNAL_BAR_42_PATH)/board/<boardname>/kernel.config

##### 9.2.1.6 额外的Linux内核扩展
可以通过将它们存储在br2-external树根目录下的linux/目录中来添加额外的Linux内核扩展(参见第18.22.2节)。

##### 9.2.1.7 示例布局
下面是一个使用所有br2-external功能的示例布局(仅为了说明br2-external树，对于相关文件显示了假设内容;这些内容完全是为了说明目的而虚构的):
```
/path/to/br2-ext-tree/
|- external.desc
|   |name: BAR_42
|   |desc: Example br2-external tree
|   `----
|
|- Config.in
|   |source "$BR2_EXTERNAL_BAR_42_PATH/toolchain/toolchain-external-mine/Config.in. ←-
    options"
|   |source "$BR2_EXTERNAL_BAR_42_PATH/package/pkg-1/Config.in"
|   |source "$BR2_EXTERNAL_BAR_42_PATH/package/pkg-2/Config.in"
|   |source "$BR2_EXTERNAL_BAR_42_PATH/package/my-jpeg/Config.in"
|   |
|   |config BAR_42_FLASH_ADDR
|   |   hex "my-board flash address"
|   |   default 0x10AD
|   `----
|
|- external.mk
|   |include $(sort $(wildcard $(BR2_EXTERNAL_BAR_42_PATH)/package/*/*.mk))
|   |include $(sort $(wildcard $(BR2_EXTERNAL_BAR_42_PATH)/toolchain/*/*.mk))
|   |
|   |flash-my-board:
|   |    $(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/flash-image \
|   |    --image $(BINARIES_DIR)/image.bin \
|   |    --address $(BAR_42_FLASH_ADDR) 
|  `----
|
|- package/pkg-1/Config.in
|   |config BR2_PACKAGE_PKG_1
|   |   bool "pkg-1"
|   |   help
|   |   Some help about pkg-1
|   `----
|- package/pkg-1/pkg-1.hash
|- package/pkg-1/pkg-1.mk
|   |PKG_1_VERSION = 1.2.3
|   |PKG_1_SITE = /some/where/to/get/pkg-1
|   |PKG_1_LICENSE = blabla
|   |
|   |define PKG_1_INSTALL_INIT_SYSV
|   |   $(INSTALL) -D -m 0755 $(PKG_1_PKGDIR)/S99my-daemon \
|   |   $(TARGET_DIR)/etc/init.d/S99my-daemon
|   |endef
|   |
|   |$(eval $(autotools-package))
|   `----
|- package/pkg-1/S99my-daemon
|
|- package/pkg-2/Config.in
|- package/pkg-2/pkg-2.hash
|- package/pkg-2/pkg-2.mk
|
|- provides/jpeg.in
|   |config BR2_PACKAGE_MY_JPEG
|   |   bool "my-jpeg" 
|   `----
|- package/my-jpeg/Config.in
|   |config BR2_PACKAGE_PROVIDES_JPEG
|   |default "my-jpeg" if BR2_PACKAGE_MY_JPEG
|   `----
|- package/my-jpeg/my-jpeg.mk
|   |# This is a normal package .mk file
|   |MY_JPEG_VERSION = 1.2.3
|   |MY_JPEG_SITE = https://example.net/some/place
|   |MY_JPEG_PROVIDES = jpeg
|   |$(eval $(autotools-package))
|   `----
|
|- provides/init.in
|   |config BR2_INIT_MINE
|   |   bool "my custom init"
|   |   select BR2_PACKAGE_MY_INIT
|   |   select BR2_PACKAGE_SKELETON_INIT_MINE if BR2_ROOTFS_SKELETON_DEFAULT
|   `----
|
|- provides/skeleton.in
|   |config BR2_ROOTFS_SKELETON_MINE
|   |   bool "my custom skeleton"
|   |   select BR2_PACKAGE_SKELETON_MINE
|   `----
|- package/skeleton-mine/Config.in
|   |config BR2_PACKAGE_SKELETON_MINE
|   |   bool
|   |   select BR2_PACKAGE_HAS_SKELETON
|   |
|   |config BR2_PACKAGE_PROVIDES_SKELETON
|   |   default "skeleton-mine" if BR2_PACKAGE_SKELETON_MINE
|   `----
|- package/skeleton-mine/skeleton-mine.mk
|   |SKELETON_MINE_ADD_TOOLCHAIN_DEPENDENCY = NO
|   |SKELETON_MINE_ADD_SKELETON_DEPENDENCY = NO
|   |SKELETON_MINE_PROVIDES = skeleton
|   |SKELETON_MINE_INSTALL_STAGING = YES
|   |$(eval $(generic-package))
|   `----
|
|- provides/toolchains.in
|   |config BR2_TOOLCHAIN_EXTERNAL_MINE
|   |   bool "my custom toolchain"
|   |   depends on BR2_some_arch
|   |   select BR2_INSTALL_LIBSTDCPP
|   `----
|- toolchain/toolchain-external-mine/Config.in.options
|   |if BR2_TOOLCHAIN_EXTERNAL_MINE
|   |config BR2_TOOLCHAIN_EXTERNAL_PREFIX
|   |   default "arch-mine-linux-gnu"
|   |config BR2_PACKAGE_PROVIDES_TOOLCHAIN_EXTERNAL
|   |   default "toolchain-external-mine"
|   |endif
|   `----
|- toolchain/toolchain-external-mine/toolchain-external-mine.mk
|   |TOOLCHAIN_EXTERNAL_MINE_SITE = https://example.net/some/place
|   |TOOLCHAIN_EXTERNAL_MINE_SOURCE = my-toolchain.tar.gz
|   |$(eval $(toolchain-external-package))
|   `----
|
|- linux/Config.ext.in
|   |config BR2_LINUX_KERNEL_EXT_EXAMPLE_DRIVER
|   |   bool "example-external-driver"
|   |   help
|   |   Example external driver
|   |---
|- linux/linux-ext-example-driver.mk
|
|- configs/my-board_defconfig
|   |BR2_GLOBAL_PATCH_DIR="$(BR2_EXTERNAL_BAR_42_PATH)/patches/"
|   |BR2_ROOTFS_OVERLAY="$(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/overlay/"
|   |BR2_ROOTFS_POST_IMAGE_SCRIPT="$(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/post- ←-
image.sh"
|   |BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE="$(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/ ←-
kernel.config" 
|   `----
|
|- patches/linux/0001-some-change.patch
|- patches/linux/0002-some-other-change.patch
|- patches/busybox/0001-fix-something.patch
|
|- board/my-board/kernel.config
|- board/my-board/overlay/var/www/index.html
|- board/my-board/overlay/var/www/my.css
|- board/my-board/flash-image
`- board/my-board/post-image.sh
    |#!/bin/sh
    |generate-my-binary-image \
    | --root ${BINARIES_DIR}/rootfs.tar \
    | --kernel ${BINARIES_DIR}/zImage \
    | --dtb ${BINARIES_DIR}/my-board.dtb \
    | --output ${BINARIES_DIR}/image.bin
    `----
```

br2-external树然后会在菜单配置中可见(展开布局):
```
External options --->
    *** Example br2-external tree (in /path/to/br2-ext-tree/)
    [ ] pkg-1
    [ ] pkg-2
    (0x10AD) my-board flash address
```

如果使用多个br2-external树，它看起来会像(展开布局，第二个名称为FOO_27但external.desc中没有desc字段):
```
External options --->
    Example br2-external tree --->
        *** Example br2-external tree (in /path/to/br2-ext-tree)
        [ ] pkg-1
        [ ] pkg-2
        (0x10AD) my-board flash address
    FOO_27 --->
        *** FOO_27 (in /path/to/another-br2-ext)
        [ ] foo
        [ ] bar
```

此外，jpeg提供商将在jpeg选择中可见:
```
Target packages --->
    Libraries --->
        Graphics --->
            [*] jpeg support
                jpeg variant () --->
                    ( ) jpeg
                    ( ) jpeg-turbo
                        *** jpeg from: Example br2-external tree ***
                    (X) my-jpeg
                        *** jpeg from: FOO_27 ***
                    ( ) another-jpeg
```

同样对于工具链:
```
Toolchain --->
    Toolchain () --->
        ( ) Custom toolchain
            *** Toolchains from: Example br2-external tree ***
        (X) my custom toolchain
```

注意toolchain/toolchain-external-mine/Config.in.options中的工具链选项不会出现在工具链菜单中。它们必须从br2-external的顶层Config.in明确包含，这样它们才会出现在外部选项菜单中。

### 9.3 保存Buildroot配置
可以使用make savedefconfig命令保存Buildroot配置。

这会通过删除默认值的配置选项来简化Buildroot配置。结果会保存到名为defconfig的文件中。如果想保存到其他位置，可以在Buildroot配置本身更改BR2_DEFCONFIG选项，或者使用make savedefconfig BR2_DEFCONFIG=<配置文件路径>命令。

建议保存此defconfig文件的位置是configs/<板名>_defconfig。如果遵循这个建议，配置会出现在make list-defconfigs输出中，并可以通过运行make <板名>_defconfig再次设置。

或者，也可以将文件复制到任何其他位置，并使用make defconfig BR2_DEFCONFIG=<配置文件路径>重新构建。

### 9.4 保存其他组件的配置 
如果修改了BusyBox、Linux内核、Barebox、U-Boot和uClibc的配置，也应保存这些组件的配置文件。对于这些每个组件，Buildroot都有一个配置选项用于指向输入配置文件，例如

    BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE。

要保存它们的配置，请将这些配置选项设置为要保存配置文件的路径，然后使用下面描述的辅助目标实际保存配置。

如第9.1节所述，建议的路径存储这些配置文件的位置是board/<company>/<板名>/foo.config。

在更改BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE等选项前，请确保已经创建了配置文件。否则，Buildroot会试图访问尚不存在的配置文件并失败。可以通过运行make linux-menuconfig等创建配置文件。

Buildroot提供了一些辅助目标来简化配置文件保存:
- make linux-update-defconfig会将Linux配置保存到BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE指定的路径。它会简化配置文件并删除默认值。但是，这只适用于2.6.33及更高版本的内核。对于早期内核，请使用make linux-update-config。
- make busybox-update-config会将Busybox配置保存到BR2_PACKAGE_BUSYBOX_CONFIG指定的路径。
- make uclibc-update-config会将uClibc配置保存到BR2_UCLIBC_CONFIG指定的路径。
- make barebox-update-defconfig会将Barebox配置保存到BR2_TARGET_BAREBOX_CUSTOM_CONFIG_FILE指定的路径。
- make uboot-update-defconfig会将U-Boot配置保存到BR2_TARGET_UBOOT_CUSTOM_CONFIG_FILE指定的路径。
- 对于at91bootstrap3，没有辅助目标，需要手动将配置文件复制到BR2_TARGET_AT91BOOTSTRAP3_CUSTOM_CONFIG路径。

### 9.5 自定义生成的目标文件系统
除了通过make *config更改配置外，还有一些其他方法可以自定义结果目标文件系统。

两个推荐的方法可以共存:根文件系统覆盖层和后构建脚本。

**根文件系统覆盖层(BR2_ROOTFS_OVERLAY)**
- 文件系统覆盖层是在目标文件系统构建完成后直接复制到目标文件系统上的文件树。要启用此功能，请将配置选项BR2_ROOTFS_OVERLAY(在系统配置菜单中)设置为覆盖层的根目录。
- 您甚至可以指定多个覆盖层，使用空格分隔。如果指定相对路径，它将相对于Buildroot树的根目录。版本控制系统的隐藏目录(如.git、.svn、.hg等)、名为.empty的文件以及以~结尾的文件都会从复制中排除。
- 当启用BR2_ROOTFS_MERGED_USR时，则覆盖层不得包含/bin、/lib或/sbin目录，因为Buildroot会将它们创建为指向/usr下相关文件夹的符号链接。在这种情况下，如果覆盖层包含任何程序或库，它们应放在/usr/bin、/usr/sbin和/usr/lib下。
- 如第9.1节所示，此覆盖层的推荐路径是board/<company>/<板名>/rootfs-overlay。

**后构建脚本(BR2_ROOTFS_POST_BUILD_SCRIPT)**
- 后构建脚本是在Buildroot构建所有选定软件后，但在组装根文件系统映像前调用的shell脚本。要启用此功能，请在配置选项BR2_ROOTFS_POST_BUILD_SCRIPT(在系统配置菜单中)指定一组以空格分隔的后构建脚本。如果指定相对路径，它将相对于Buildroot树的根目录。
- 使用后构建脚本，您可以从目标文件系统中删除或修改任何文件。然而，您应谨慎使用此功能。每当您发现某个软件包生成错误或不需要的文件时，最好修复该软件包，而不是使用一些后构建清理脚本来解决问题。
- 如第9.1节所示，此脚本的推荐路径是board/<company>/<板名>/post_build.sh。
- 后构建脚本在Buildroot主树作为当前工作目录运行。目标文件系统的路径作为第一个参数传递给每个脚本。如果配置选项BR2_ROOTFS_POST_SCRIPT_ARGS不为空，这些参数也将传递给脚本。所有脚本都将接收相同的一组参数集，无法向每个脚本传递不同的参数集。
此外，还可以使用以下环境变量:
    - BR2_CONFIG: Buildroot .config文件的路径
    - CONFIG_DIR: 包含.config文件的目录，因此也是用于in-tree和out-of-tree构建的顶层Buildroot Makefile的目录
    - HOST_DIR、STAGING_DIR、TARGET_DIR: 参见第18.6.2节
    - BUILD_DIR: 解压和构建软件包的目录  
    - BINARIES_DIR: 存储所有二进制文件的位置(即映像)
    - BASE_DIR: 基本输出目录

下面描述了三种其他自定义目标文件系统的方法，但它们不推荐使用:

**直接修改目标文件系统**
- 对于临时修改，可以直接修改目标文件系统，然后重新构建映像。目标文件系统位于output/target/下。进行修改后，运行make重建目标文件系统映像。
- 这种方法允许对目标文件系统进行任何操作，但如果需要使用make clean清理Buildroot树，这些修改将丢失。有几种情况下需要进行这样的清理，详见第8.2节。因此，这种解决方案仅用于快速测试:make clean命令后修改无法保存。一旦验证通过修改，应确保它们能够在make clean后持久存在，使用根文件系统覆盖层或后构建脚本。

**自定义目标骨架(BR2_ROOTFS_SKELETON_CUSTOM)**
- 根文件系统映像是基于目标骨架创建的，所有软件包都将文件安装到其上。骨架会在构建和安装任何软件包前拷贝到输出目录output/target下。默认目标骨架提供标准Unix文件系统布局以及一些基本的init脚本和配置文件。
- 如果默认骨架(位于system/skeleton下)不符合您的需求，通常会使用根文件系统覆盖层或后构建脚本来对其进行调整。但是，如果默认骨架与您需要的完全不同，使用自定义骨架可能更合适。
- 要启用此功能，请启用配置选项BR2_ROOTFS_SKELETON_CUSTOM，并将BR2_ROOTFS_SKELETON_CUSTOM_PATH设置为自定义骨架的路径。这两个选项都在系统配置菜单中可用。如果指定相对路径，它将相对于Buildroot树的根目录。
- 自定义骨架不需要包含/bin、/lib或/sbin目录，因为它们会在构建过程中自动创建。当启用BR2_ROOTFS_MERGED_USR时，则自定义骨架不得包含/bin、/lib或/sbin目录，因为Buildroot会将它们创建为指向/usr下相关文件夹的符号链接。在这种情况下，如果骨架包含任何程序或库，它们应放在/usr/bin、/usr/sbin和/usr/lib下。
- 这种方法不推荐，因为它复制整个骨架，从而无法利用Buildroot后续版本为默认骨架带来的修复或改进。

**后伪根脚本(BR2_ROOTFS_POST_FAKEROOT_SCRIPT)**
- 在聚合最终映像时，某些步骤需要root权限:在/dev下创建设备节点，设置文件和目录的权限或所有者等。为避免实际需要root权限，Buildroot使用伪根来模拟root权限。这不是完全取代root的替代方案，但对Buildroot需要的操作足够了。
- 后伪根脚本是在伪根阶段结束时，正准备调用文件系统映像生成器之前调用的shell脚本。因此，它们在伪根上下文中调用。
- 后伪根脚本在需要对文件系统进行通常只有root用户才能进行的微调时很有用。
- 注意:建议使用现有机制设置文件权限或在/dev下创建项(见9.5.1节)或创建用户(见9.6节)。
- 注意:与后构建脚本(上文)的区别在于，后构建脚本不在伪根上下文中调用。
- 注意:使用伪根不是真正成为root的完全替代方案。伪根只伪装文件访问权限和类型(常规、块或字符设备等)，以及uid/gid，这些都是内存中模拟的。

#### 9.5.1 设置文件权限和所有者，添加自定义设备节点
有时需要为文件或设备节点设置特定的权限或所有者。例如，某些文件可能需要由root拥有。由于后构建脚本不是以root权限运行，除非从脚本显式使用伪根，否则无法在那里进行此类更改。

相反，Buildroot提供了所谓的权限表支持。要使用此功能，请将配置选项BR2_ROOTFS_DEVICE_TABLE设置为权限表的空格分隔列表，权限表是遵循makedev语法的常规文本文件。

如果使用静态设备表(即不使用devtmpfs、mdev或(e)udev)，则可以使用相同语法在所谓的设备表中添加设备节点。要使用此功能，请将配置选项BR2_ROOTFS_STATIC_DEVICE_TABLE设置为设备表的空格分隔列表。
如第9.1节所示，这类文件的推荐位置是board/<company>/<板名>/。

需要注意的是，如果特定权限或设备节点与特定应用相关，则应在软件包的.mk文件中设置FOO_PERMISSIONS和FOO_DEVICES变量(参见第18.6.2节)。

### 9.6 添加自定义用户帐户
有时需要在目标系统中添加特定用户。为满足此要求，Buildroot提供了所谓的用户表支持。要使用此功能，请将配置选项BR2_ROOTFS_USERS_TABLES设置为用户表的空格分隔列表，用户表是遵循makeusers语法的常规文本文件。

如第9.1节所示，这类文件的推荐位置是board/<company>/<板名>/。

需要注意的是，如果自定义用户与特定应用相关，则应在软件包的.mk文件中设置FOO_USERS变量(参见第18.6.2节)。

### 9.7 图像创建后自定义 
虽然后构建脚本(第9.5节)在构建文件系统映像、内核和引导加载程序之前运行，但后图像脚本可以用于所有图像创建后执行某些特定操作。

例如，后图像脚本可以自动在NFS服务器导出的位置提取根文件系统tar包，或者创建专用固件映像将根文件系统和内核映像打包在一起，或者项目需要的任何其他自定义操作。

要启用此功能，请在配置选项BR2_ROOTFS_POST_IMAGE_SCRIPT(在系统配置菜单中)指定一组以空格分隔的后图像脚本。如果指定相对路径，它将相对于Buildroot树的根目录。

与后构建脚本类似，后图像脚本使用Buildroot主树作为当前工作目录运行。图像输出目录的路径作为第一个参数传递给每个脚本。如果配置选项BR2_ROOTFS_POST_SCRIPT_ARGS不为空，这些参数也将传递给脚本。所有脚本都将接收相同的参数集。

同样，脚本可以访问BR2_CONFIG、HOST_DIR、STAGING_DIR、TARGET_DIR、BUILD_DIR、BINARIES_DIR、CONFIG_DIR和BASE_DIR环境变量。

后图像脚本将以执行Buildroot的用户身份运行，通常不是root用户。所以脚本中需要root权限的任何操作都需要特殊处理(使用伪根或sudo)。

### 9.8 添加项目特定补丁
对软件包应用额外补丁有时很有用 - 除Buildroot提供的补丁外。这可能用于支持项目特定功能，例如，或在新体系结构上工作时。

BR2_GLOBAL_PATCH_DIR配置选项可以用于指定一个或多个包含软件包补丁的目录的空格分隔列表。

对于特定版本<packageversion>的特定软件包<packagename>，从BR2_GLOBAL_PATCH_DIR应用补丁如下:
1. 对于BR2_GLOBAL_PATCH_DIR中的每个目录- <global-patch-dir>-如果存在<package-patch-dir>将确定如下:
   - 如果存在<global-patch-dir>/<packagename>/<packageversion>/
   - 否则，如果存在<global-patch-dir>/<packagename>
2. 然后从<package-patch-dir>应用补丁:
   - 如果软件包目录中存在series文件，则根据series文件应用补丁;
   - 否则，应用名称匹配*.patch的补丁文件，按字母顺序。所以为了确保正确顺序，建议命名补丁文件为:<number>-<description>.patch。

有关软件包如何应用补丁的详细信息，请参阅第19.2节。

BR2_GLOBAL_PATCH_DIR是指定任何Buildroot软件包自定义补丁目录的首选方法。它也应取代U-Boot和Barebox等软件包可用的自定义补丁目录选项。通过这种方式，用户可以从一个顶层目录管理补丁。

BR2_LINUX_KERNEL_PATCH是指定内核补丁的例外情况。BR2_LINUX_KERNEL_PATCH应用于从URL获取的内核补丁。需要注意的是，BR2_LINUX_KERNEL_PATCH指定的内核补丁是在BR2_GLOBAL_PATCH_DIR中的补丁之后应用，因为它是从Linux软件包的后补丁钩子中完成的。

### 9.9 添加项目特定软件包
通常，任何新软件包都应直接添加到软件包目录中，并提交到Buildroot上游项目。

Buildroot如何一般添加软件包在第18章中有详细说明，这里不再重复。但是，您的项目可能需要一些专有软件包无法上游。本节将解释如何将此类项目特定软件包保存在项目特定目录中。

如第9.1节所示，项目特定软件包的推荐位置是package/<company>/。如果使用br2-external树功能(参见第9.2节)，则推荐位置是将它们放在br2-external树下名为package/的子目录中。

但是，Buildroot不知道此位置的软件包，除非进行额外步骤。如第18章所述，Buildroot软件包基本上由两个文件组成:.mk文件(描述如何构建软件包)和Config.in文件(描述此软件包的配置选项)。

Buildroot会自动包含软件包目录第一级子目录下的.mk文件(使用pattern package/*/*.mk)。如果要包含更深子目录下的.mk文件(如package/<company>/package1/)，则只需在第一级子目录下添加一个.mk文件来包含这些额外的.mk文件。因此，创建文件package/<company>/<company>.mk，内容如下(假设下package/<company>/只有一个额外级别):

    include $(sort $(wildcard package/<company>/*/*.mk))
对于Config.in文件，创建文件package/<company>/Config.in包含所有软件包的Config.in文件。由于kconfig源命令不支持通配符，必须提供详尽列表。例如:

    source "package/<company>/package1/Config.in"
    source "package/<company>/package2/Config.in"
从package/Config.in包含此新文件package/<company>/Config.in，最好放在company特定菜单中以便于与未来Buildroot版本合并。

如果使用br2-external树，请参考第9.2节填写这些文件。

### 9.10 快速指南:存储项目特定自定义
本章前面描述了不同的项目特定自定义方法。本节将总结所有内容，提供按步骤指导存储项目特定自定义内容:
1. make menuconfig 配置工具链、软件包和内核。
2. make linux-menuconfig 更新内核配置，其他配置如busybox、uclibc等也类似。 
3. mkdir -p board/<制造商>/<板名>
4. 将以下选项设置为board/<制造商>/<板名>/<软件包>.config(如果相关):
   - BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE
   - BR2_PACKAGE_BUSYBOX_CONFIG
   - BR2_UCLIBC_CONFIG
   - BR2_TARGET_AT91BOOTSTRAP3_CUSTOM_CONFIG_FILE
   - BR2_TARGET_BAREBOX_CUSTOM_CONFIG_FILE 
   - BR2_TARGET_UBOOT_CUSTOM_CONFIG_FILE
5. 写入配置文件:
   - make linux-update-defconfig
   - make busybox-update-config
   - make uclibc-update-config
   - cp <输出>/build/at91bootstrap3-*/.config board/<制造商>/<板名>/at91bootstrap3.config
   - make barebox-update-defconfig
   - make uboot-update-defconfig
6. 创建board/<制造商>/<板名>/rootfs-overlay/添加需要的附加文件，设置BR2_ROOTFS_OVERLAY。
7. 创建post-build脚本board/<制造商>/<板名>/post_build.sh，设置BR2_ROOTFS_POST_BUILD_SCRIPT。  
8. 如果需要设置设备节点或权限，创建board/<制造商>/<板名>/device_table.txt并添加到BR2_ROOTFS_DEVICE_TABLE。
9. 如果需要创建用户，创建board/<制造商>/<板名>/users_table.txt并添加到BR2_ROOTFS_USERS_TABLES。
10. 设置BR2_GLOBAL_PATCH_DIR添加补丁。
11. 内核也有BR2_LINUX_KERNEL_PATCH从URL获取补丁。
12. 如果需要添加专有软件包，创建package/<制造商>放置软件包。
13. make savedefconfig保存配置。
14. cp defconfig configs/<板名>_defconfig。


## Chapter 10、 集成主题
本章讨论在系统层面如何集成各种内容。Buildroot高度可配置，这里讨论的几乎所有内容都可以通过根文件系统覆盖层或自定义骨架配置进行更改或覆盖。

### 10.1 Systemd
本章描述Buildroot集成Systemd所采取的决定，以及如何实现各种使用场景。

#### 10.1.1 DBus守护进程
Systemd需要一个DBus守护进程。有两种选择:传统的dbus(BR2_PACKAGE_DBUS)和bus1的dbus-broker(BR2_PACKAGE_DBUS_BROKER)。必须选择其中一个。如果配置中包含两者，dbus-broker将被用作系统总线，但传统的dbus守护进程仍然被安装，可以作为会话总线使用。它的工具(如dbus-send)也可以使用(systemd本身有busctl作为替代)。此外，传统的dbus包是提供libdbus的唯一包，libdbus被许多包用作DBus集成库。

无论选择dbus还是dbus-broker，守护进程都以用户dbus运行。DBus配置文件对两种情况也是相同的。
为确保只启动一个守护进程作为系统总线，当选择dbus-broker时，dbus软件包的systemd激活文件(dbus.socket和multi-user.target.wants中的dbus.service链接)将被删除。

### 10.2 在Buildroot中使用SELinux
SELinux是一个Linux内核安全模块，强制执行访问控制策略。除了传统的文件权限和访问控制列表外，SELinux允许为用户或进程写入访问特定功能或资源(文件、套接字等)的规则。
SELinux有三种操作模式:
- 禁用:不应用策略
- 允许模式:应用策略，但非授权操作只会记录日志。这种模式常用于排查SELinux问题。
- 强制模式:应用策略，非授权操作会被拒绝
在Buildroot中，操作模式由BR2_PACKAGE_REFPOLICY_POLICY_STATE_*配置选项控制。Linux内核也有影响SELinux启用的各种配置选项(参见Linux内核源码中的security/selinux/Kconfig)。
默认情况下，Buildroot使用refpolicy项目提供的SELinux策略，通过BR2_PACKAGE_REFPOLICY启用。

#### 10.2.1 启用SELinux支持
要在Buildroot生成的系统中正确支持SELinux，必须启用以下配置选项:
- BR2_PACKAGE_LIBSELINUX
- BR2_PACKAGE_REFPOLICY
此外，文件系统映像格式必须支持扩展属性。

#### 10.2.2 调整SELinux策略
SELinux refpolicy包含可以在构建时启用或禁用的模块。每个模块提供一组SELinux规则。在Buildroot中，默认禁用非基本模块，提供以下几种方式启用此类模块:
- 软件包可以使用<软件包名称>_SELINUX_MODULES变量在refpolicy中启用模块列表。
- 软件包可以通过将模块(.fc、.if和.te文件)放在package/<软件包名称>/selinux/下提供额外的SELinux模块。
- 可以通过BR2_REFPOLICY_EXTRA_MODULES_DIRS配置选项指定的目录添加额外SELinux模块。
- 如果在BR2_REFPOLICY_EXTRA_MODULES_DEPENDENCIES配置选项中列出，也可以在refpolicy中启用额外模块。

Buildroot还允许完全覆盖refpolicy，这允许提供专门为给定系统设计的完整自定义策略。采用这种方式时，所有上述机制都被禁用:不会向策略添加任何额外的SELinux模块，构建到最终二进制策略中的所有可用模块都将被启用。自定义策略必须基于官方refpolicy进行分支。

要完全覆盖refpolicy，必须设置以下配置变量:
- BR2_PACKAGE_REFPOLICY_CUSTOM_GIT 
- BR2_PACKAGE_REFPOLICY_CUSTOM_REPO_URL
- BR2_PACKAGE_REFPOLICY_CUSTOM_REPO_VERSION

## Chapter 11、常见问题与故障排除
### 11.1 启动后挂起在Starting network...
如果启动过程似乎在以下消息(消息可能不完全相同，取决于选择的软件包列表)后挂起:
```
Freeing init memory: 3972K  
Initializing random number generator... done.
Starting network...
Starting dropbear sshd: generating rsa key... generating dsa key... OK
```

这意味着系统正在运行，但没有在串行控制台启动shell。要在串行控制台启动shell，需要进入Buildroot配置，在系统配置中，修改Run a getty(登录提示) after boot，并在getty选项子菜单中设置适当的端口和波特率。这将自动调整生成系统的/etc/inittab文件，使shell在正确的串行端口启动。

### 11.2 为什么目标上没有编译器?
从Buildroot-2012.11版本开始决定停止支持目标上的本机编译器，因为:
- 这个功能既没有维护也没有测试，经常出问题;
- 这个功能只适用于Buildroot工具链;
- Buildroot主要面向资源有限的小型或非常小型目标硬件(CPU、内存、存储)，本地编译在目标上没有太大意义;
- Buildroot旨在简化交叉编译，使目标本地编译不再必要。
如果您的目标实际上需要编译器，那么Buildroot不适合您的目的。在这种情况下，您需要真正的发行版，可以选择:
- openembedded
- yocto 
- Debian
- Fedora
- openSUSE ARM
- Arch Linux ARM
- ...

### 11.3 为什么目标上没有开发文件?
由于目标上没有可用编译器(参见第11.2节)，带头文件或静态库浪费空间没有意义。

因此，从Buildroot-2012.11版本开始，这些文件始终从目标中删除。

### 11.4 为什么目标上没有文档? 
由于Buildroot主要面向资源有限的小型或非常小型目标硬件(CPU、内存、存储)，带文档数据浪费空间没有意义。

如果您的目标实际上需要文档数据，那么Buildroot不适合您的目的，应该查找真正的发行版(参见第11.2节)。

### 11.5 为什么某些软件包在Buildroot配置菜单中不可见?
如果软件包存在于Buildroot树中，但在配置菜单中不可见，很可能是因为软件包的一些依赖未满足。

要了解软件包的依赖关系，请在配置菜单中搜索软件包符号(参见第8.1节)。然后您可能需要递归启用几个选项(对应未满足的依赖关系)，最后才能选择该软件包。

如果软件包由于一些未满足的工具链选项而不可见，则应该进行全重建(第8.1节有更多解释)。

### 11.6 为什么不使用目标目录作为chroot目录?
不使用目标目录作为chroot目录有很多原因，其中包括:
- 目标目录中的文件所有者、模式和权限设置不正确;
- 目标目录中没有创建设备节点。

出于这些原因，通过chroot使用目标目录作为新的根目录运行命令很可能会失败。

如果要在chroot或作为NFS根运行目标文件系统，请使用images/生成的tar包并将其提取为根。

### 11.7 为什么Buildroot不生成二进制包(.deb、.ipkg等)?
Buildroot列表上经常讨论的一个主题是“包管理”。总结来说，想法是追踪Buildroot软件包安装了哪些文件，目的是:
- 当软件包从菜单配置中取消选择时，能够删除该软件包安装的文件;
- 能够生成二进制包(ipk等格式)，允许在不重新生成根文件系统映像的情况下安装到目标上。

通常认为这很容易实现:只需追踪软件包安装了什么，取消选择时删除。但是其实比这复杂得多:

 - 问题不仅涉及目标/目录，还涉及主机/<元组>/sysroot中的系统根目录以及主机/目录本身。所有这些目录下由各种软件包安装的文件都必须进行跟踪。
- 当软件包从配置中取消选择时，仅删除它安装的文件是不足够的。还必须删除所有反向依赖(即依赖它的软件包)，并重新构建这些软件包。例如，软件包A可选地依赖OpenSSL库。两者都被选择，Buildroot被构建。软件包A使用OpenSSL构建带加密支持。之后取消选择OpenSSL，但软件包A保留(由于OpenSSL是可选依赖，这是可能的)。如果仅删除OpenSSL文件，则软件包A安装的文件会损坏:它使用一个不再存在于目标上的库。这在技术上是可行的，但会给Buildroot增加很多复杂性，这与我们努力保持的简单性背道而驰。
- 除了上述问题，可选依赖本身可能Buildroot不知道。例如，软件包A版本1.0从未使用OpenSSL，但版本2.0如果可用会自动使用OpenSSL。如果Buildroot的.mk文件没有更新考虑这一点，则软件包A不会成为OpenSSL的反向依赖，OpenSSL删除时也不会删除和重新构建软件包A。当然，.mk文件应修复此可选依赖，但在此期间可能出现不可重复的行为。
- 也要允许menuconfig中的更改应用于输出目录，而无需从头重新构建 everything。但是，这很难可靠实现:子选项更改会如何处理，是否需要检测并从头重新构建软件包以及其潜在的反向依赖关系等。目前，Buildroot所做的是清晰简单的，其行为非常可靠且支持用户也很容易。如果menuconfig中的配置更改在下次make后应用，那么它必须在所有情况下都正确有效工作，而不是有一些奇怪的边缘案例。风险是收到类似“我启用了A、B和C软件包，然后make，然后禁用C启用D然后make，然后重新启用C启用E然后构建失败”的错误报告。或者更糟的是“我做了一些配置，然后构建，然后做一些更改，构建，再做一些更改，构建，再做一些更改，构建，现在失败了，但我不记得做了哪些更改和顺序”。这将无法支持。

出于所有这些原因，得出结论是追踪安装文件以便在取消选择软件包时删除它们，或者生成二进制软件包仓库，这是一件非常难以可靠实现的事情，它会给Buildroot带来很多复杂性。

在这个问题上，Buildroot开发人员提出以下立场:
- Buildroot致力于使生成根文件系统变得容易(顺便说一下，这也是它的名字)。我们想让Buildroot擅长的就是构建根文件系统。
- Buildroot不打算成为发行版(或者说发行版生成器)。大多数Buildroot开发人员认为这不是我们应该追求的目标。我们认为有其他工具更适合生成发行版，比如OpenEmbedded或OpenWrt。 
- 我们倾向于把Buildroot推向一个方向，使其生成完整根文件系统变得更容易(当然，除此之外!)。这就是Buildroot在众多工具中的亮点之一。
- 对于大多数嵌入式Linux系统来说，二进制软件包不是必需的，可能还有害处。使用二进制软件包意味着系统可以部分升级，这会产生大量可能的软件包版本组合，这些组合应在将升级部署到嵌入式设备前进行测试。相反，通过一次性升级整个根文件系统映像完成系统升级，可以保证部署到嵌入式系统的确实是经过测试和验证的映像。

### 11.8 如何加快构建过程?
由于Buildroot通常涉及全面重建整个系统，这个过程可能很长，下面提供一些提示可以帮助减少构建时间:
- 使用预编译外部工具链，而不是默认内部工具链。使用预编译的Linaro工具链(在ARM上)或Sourcery CodeBench工具链(对ARM、x86、x86-64、MIPS等)，每次完全重建可以节省工具链构建时间，大约15-20分钟。暂时使用外部工具链不会阻止您之后切换回内部工具链(提供更高级别定制)。
- 使用ccache编译器缓存(参见第8.13.3节)。
- 了解只重建您真正关心的少数软件包(参见第8.3节)，但要注意有时完全重建是必需的(参见第8.2节)。
- 确保不使用虚拟机运行Buildroot的Linux系统。大多数虚拟机技术都会显著影响I/O性能，这对构建源代码很重要。
- 确保仅使用本地文件:不要试图通过NFS进行构建，这会显著降低构建速度。Buildroot下载文件夹本地可用也有助于加快速度。
- 购买新硬件。SSD和大量RAM对加速构建很关键。
- 试验顶层并行构建，参见第8.12节。

## Chapter 12、 已知问题:
- 如果通过BR2_TARGET_LDFLAGS传递额外链接器选项包含$符号，则不可能。例如以下配置会导致错误:
BR2_TARGET_LDFLAGS="-Wl，-rpath=’$ORIGIN/../lib’" 
- libffi软件包不支持SuperH 2和ARMv7-M架构。
- 使用Sourcery CodeBench 2012.09版本的SuperH 4编译器，prboom软件包会触发编译器错误。

## Chapter 13、合法通知和许可证
### 13.1 遵守开源许可证
Buildroot生成的所有产品(工具链、根文件系统、内核、引导加载程序)都包含开源软件，根据各种许可证发布。

使用开源软件给您带来了构建丰富嵌入式系统的自由，可以从广泛的软件包中选择，但也带来一些义务，您必须了解并遵守。一些许可证要求您在产品文档中发布许可证文本。其他许可证要求您将软件源代码重新分发给收到您产品的人。

每个软件包都记录了具体要求，遵守这些要求是您(或法律部门)的责任。为了方便您，Buildroot可以收集您可能需要的一些材料。配置Buildroot后，运行:

    make legal-info 

 Buildroot将在输出目录下的legal-info/子目录收集合法相关材料。您可以找到:

- 摘要文件（README文件），总结了生成的材料，并包含了Buildroot无法产生的材料的警告。
- buildroot.config：这是Buildroot的配置文件，通常使用make menuconfig生成，并且在重建构建时是必需的。
- 所有软件包的源代码；这些源代码分别保存在目标软件包的sources/子目录和主机软件包的host-sources/子目录中。未保存设置<PKG>_REDISTRIBUTE = NO的软件包的源代码。还保存了应用的补丁，以及一个名为series的文件，列出了补丁的应用顺序。补丁的许可与修改的文件相同。注意：Buildroot还会对基于autotools的软件包的Libtool脚本应用额外的补丁。这些补丁可以在Buildroot源代码的support/libtool目录中找到，由于技术限制，不会与软件包源代码一起保存。您可能需要手动收集它们。
- 清单文件（主机和目标软件包各一个），列出了已配置的软件包、它们的版本、许可证和相关信息。Buildroot中可能没有定义某些信息；这些项目标记为“未知”。
- 所有软件包的许可证文本，分别保存在目标软件包的licenses/子目录和主机软件包的host-licenses/子目录中。如果Buildroot中未定义许可证文件，则不会生成该文件，并在README中指示警告。

请注意，legal-info功能的目的是产生与软件包许可证合规有关的所有材料。Buildroot不试图产生您必须公开的确切材料。由于技术限制，Buildroot无法产生某些材料，README会给出提示。

请注意，Buildroot法律信息功能的目的是生成与软件包许可证合规有关的所有材料。Buildroot不试图生成您必须公开提供的确切材料。当然，生成的材料比严格合规需要的更多。例如，它为BSD样式许可证下的软件包生成源代码，您无需重新分发源代码。

此外，由于技术限制，Buildroot无法生成您可能需要的一些材料，例如一些外部工具链的源代码以及Buildroot源代码本身。当您运行make legal-info时，Buildroot在README文件中会生成警告，告知无法保存的相关材料。

最后，请记住make legal-info的输出基于每个软件包recipe中的声明语句。Buildroot开发人员会尽最大努力保持这些声明语句尽可能准确，尽他们所知。但是，这些声明语句并不一定完全准确或详尽。您(或法务部门)必须在使用输出作为合规递送前检查make legal-info的输出。请参阅Buildroot发行版根目录下COPYING文件中的免责条款(第11和12条)。

### 13.2 遵守Buildroot许可证
Buildroot本身是一个开源软件，根据GNU通用公共许可证第2版或（根据您的选择）任何更新版本发布，但以下详细介绍的软件包补丁除外。然而，作为一个构建系统，Buildroot通常不是最终产品的一部分：如果您为设备开发根文件系统、内核、引导加载程序或工具链，则Buildroot的代码仅出现在开发机器上，而不是设备存储中。

尽管如此，Buildroot开发人员普遍认为，当发布包含GPL许可的软件的产品时，您应该与其他软件包的源代码一起发布Buildroot源代码。这是因为GNU GPL将可执行作品的“完整源代码”定义为“它包含的所有模块的所有源代码，以及任何相关的接口定义文件，加上用于控制可执行文件的编译和安装的脚本”。Buildroot是用于控制可执行文件的编译和安装的脚本的一部分，因此被认为是必须重新分发的材料的一部分。

请记住，这仅是Buildroot开发人员的意见，如有任何疑问，请咨询您的法律部门或律师。

#### 13.2.1 软件包的补丁
Buildroot还捆绑了补丁文件，这些补丁文件应用于各种软件包的源代码。这些补丁不受Buildroot许可证的覆盖。相反，它们受到应用补丁的软件的许可证的约束。当所述软件在多个许可证下可用时，Buildroot补丁仅在公开可访问的许可证下提供。详细技术信息请参见第19章。


## Chapter 14、 Buildroot 之外的
### 14.1 启动生成的镜像
#### 14.1.1 NFS 引导
要实现NFS引导,请在文件系统镜像菜单中启用tar根文件系统。

构建完成后,只需运行以下命令来设置NFS根目录:

    sudo tar -xavf /path/to/output_dir/rootfs.tar -C /path/to/nfs_root_dir 

记住在/etc/exports中添加此路径。

然后,您可以从目标设备执行NFS引导。

#### 14.1.2 实时CD
要构建实时CD镜像,请在文件系统镜像菜单中启用iso镜像选项。请注意,此选项仅在 x86 和 x86-64 体系结构上可用,如果您使用 Buildroot 构建内核。

您可以使用IsoLinux、Grub或Grub 2作为引导程序构建实时CD镜像,但只有IsoLinux支持使此镜像既可以作为实时CD也可以作为实时U盘使用(通过Build hybrid image选项)。

您可以使用QEMU测试您的实时CD镜像:

    qemu-system-i386 -cdrom output/images/rootfs.iso9660

或者如果它是混合ISO,可以将其用作硬盘镜像:

    qemu-system-i386 -hda output/images/rootfs.iso9660

它可以使用dd轻松刻录到U盘:

    dd if=output/images/rootfs.iso9660 of=/dev/sdb


### 14.2 chroot
如果您要在生成的镜像中chroot,则应了解几点:
- 您应该从tar根文件系统镜像设置新的根目录;
- 选择的目标体系结构要兼容您的主机,或者您应使用一些qemu-*二进制文件并正确设置它们的binfmt属性,才能在主机上运行为目标构建的二进制文件;
- Buildroot当前不提供为此目的正确构建和设置的host-qemu和binfmt。




-------------
-------------

# III 进阶指导

## Chapter 15、Buildroot 的工作原理
如上所述,Buildroot本质上是一个包含Makefile的集合,它可以下载、配置和使用正确选项编译软件。它还包括各种软件包的补丁 - 主要是那些参与交叉编译工具链(gcc、binutils和uClibc)的软件包。

每个软件包基本上对应一个Makefile,它使用.mk扩展名。Makefile被分成许多不同部分。

- toolchain/目录包含所有与交叉编译工具链相关的软件的Makefile和相关文件:binutils、gcc、gdb、内核头文件和uClibc。
- arch/目录包含Buildroot支持的所有处理器体系结构的定义。
- package/目录包含Buildroot可以编译并添加到目标根文件系统的所有用户空间工具和库的Makefile和相关文件。每个包对应一个子目录。
- linux/目录包含内核的Makefile和相关文件。
- boot/目录包含Buildroot支持的引导程序的Makefile和相关文件。
- system/目录包含系统集成支持,例如目标文件系统骨架和初始化系统选择。
- fs/目录包含与生成目标根文件系统镜像相关的软件的Makefile和相关文件。

每个目录至少包含两个文件:
- something.mk是下载、配置、编译和安装包something的Makefile。
- Config.in是配置工具描述文件的一部分。它描述与该包相关的选项。
主Makefile执行以下步骤(在配置完成后):
- 在输出目录(默认为output/,也可以使用O=指定其他值)中创建所有输出目录:staging、target、build等。
- 生成工具链目标。对于内置工具链,这意味着生成交叉编译工具链。对于外部工具链,这意味着检查外部工具链的功能并将其导入到Buildroot环境中。
- 生成TARGETS变量中列出的所有目标。这个变量由所有单个组件的Makefile填充。生成这些目标将触发用户空间包(库、程序)、内核和引导程序的编译,以及根文件系统镜像的生成,这取决于配置。


## Chapter 16、 翻译:代码风格
总体来说,这些代码风格规则旨在帮助您向Buildroot添加新文件或重构现有文件。

如果您稍微修改一些现有文件,那么重要的是保持整个文件的一致性,所以您可以:
- 遵循该文件中可能已过时的代码风格;
- 或者完全重构它,以使其符合这些规则。

### 16.1 Config.in文件
Config.in文件包含Buildroot中几乎所有可配置项的条目。

一个条目遵循以下模式:
```
config BR2_PACKAGE_LIBFOO
    bool "libfoo"
    depends on BR2_PACKAGE_LIBBAZ
    select BR2_PACKAGE_LIBBAR
    help
        This is a comment that explains what libfoo is. The help text
        should be wrapped.

    http://foosoftware.org/libfoo/
```
- bool、depends on、select和help行使用一个制表符缩进。
- 帮助文本本身使用一个制表符和两个空格缩进。
- 帮助文本应该换行适应72列,其中制表符计为8个字符,所以文本本身为62个字符。

Config.in文件是Buildroot中使用的配置工具Kconfig的输入。有关Kconfig语言的更多详细信息,请参阅http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt。

### 16.2 .mk文件
- 标题(Header):文件从标题开始。它包含模块名称,最好使用小写,括在由80个井号组成的分隔符之间。标题后必须有一个空行:
```
################################################################################
#
# libfoo
#
################################################################################
```

- 分配:使用前后跟一个空格的=:
```
LIBFOO_VERSION = 1.0
LIBFOO_CONF_OPTS += --without-python-support
```
不要对齐=符号。

- 缩进:只使用制表符: 
```
define LIBFOO_REMOVE_DOC
    $(RM) -r $(TARGET_DIR)/usr/share/libfoo/doc \
        $(TARGET_DIR)/usr/share/man/man3/libfoo*
endef
```
注意:define块中的命令应始终使用制表符开始,以便make将其识别为命令。
- 可选依赖:
  - 优先使用多行语法。  
    YES:
    ```
    ifeq ($(BR2_PACKAGE_PYTHON3),y)
    LIBFOO_CONF_OPTS += --with-python-support
    LIBFOO_DEPENDENCIES += python3
    else
    LIBFOO_CONF_OPTS += --without-python-support
    endif
    ```
    NO:
    ```
    LIBFOO_CONF_OPTS += --with$(if $(BR2_PACKAGE_PYTHON3),,out)-python-support
    LIBFOO_DEPENDENCIES += $(if $(BR2_PACKAGE_PYTHON3),python3,)
    ```
  - 将配置选项和依赖关系保持在一起。

- 可选钩子(HOOK):将钩子定义和赋值保持在一个if块中。  
    YES:
    ```
    ifneq ($(BR2_LIBFOO_INSTALL_DATA),y)
    define LIBFOO_REMOVE_DATA
        $(RM) -r $(TARGET_DIR)/usr/share/libfoo/data
    endef
    LIBFOO_POST_INSTALL_TARGET_HOOKS += LIBFOO_REMOVE_DATA
    endif
    ```

    NO:
    ```
    define LIBFOO_REMOVE_DATA
        $(RM) -r $(TARGET_DIR)/usr/share/libfoo/data
    endef

    ifneq ($(BR2_LIBFOO_INSTALL_DATA),y)
    LIBFOO_POST_INSTALL_TARGET_HOOKS += LIBFOO_REMOVE_DATA
    endif
    ```


### 16.3 genimage.cfg文件
genimage.cfg文件包含genimage实用程序用于创建最终.img文件的输出镜像布局。
```
image efi-part.vfat {
    vfat {
        file EFI {
            image = "efi-part/EFI"
        }
        file Image {
            image = "Image"
        }
    }

    size = 32M
}

image sdimage.img {
    hdimage {
    }

    partition u-boot {
        image = "efi-part.vfat"
        offset = 8K
    }

    partition root {
        image = "rootfs.ext2"
        size = 512M
    }
}
```


- 每个部分(如hdimage、vfat等)、分区必须使用一个制表符缩进。
- 每个文件或其他子节点必须使用两个制表符缩进。
- 每个节点(部分、分区、文件、子节点)名称必须在同一行使用一个左花括号,而右花括号必须在新行且后跟一个新行,除最后一个节点外。选项(如option size =)也一样。
- 每个选项(如image、offset、size)等号赋值必须与其前后各有一个空格。
- 文件名至少应以genimage前缀开头并使用.cfg扩展名以便识别。 
- 允许的offset和size选项单位有:G、M、K(不用k)。如果无法用上述单位精确表示字节数,则使用0x十六进制前缀,或者直接使用字节数。在注释中分别使用GB、MB、KB(不用kb)替换G、M、K。
- 对于ChatMindAi分区,partition-type-uuid值必须是U(代表EFI系统分区,genimage扩展为c12a7328-f81f-11d2-ba4b-00a0c93ec93b)、F(FAT分区,扩展为ebd0a0a2-b9e5-4433-87c0-68b6b72699c7)或L(根文件系统或其他文件系统,扩展为0fc63daf-8483-4772-8e79-3d69d8477de4)。尽管L是genimage的默认值,但我们优先在genimage.cfg文件中明确指定它。最后,这些缩写应不使用双引号,例如partition-type-uuid = U。如果指定了明确的GUID,应使用小写字母。

genimage.cfg文件是Buildroot用于生成最终镜像文件的genimage工具的输入。有关genimage语言的更多详细信息,请参考https://github.com/pengutronix/genimage/blob/master/README.rst。


### 16.4 文档
文档使用asciidoc格式。

有关asciidoc语法的更多详细信息,请参阅https://asciidoc-py.github.io/userguide.html。

### 16.5 支持脚本 
support/和utils/目录中的一些脚本使用Python编写,应遵循Python代码的PEP8风格指南。


## Chapter 17、 为特定板卡添加支持
Buildroot 包含了对几个公开可用硬件板卡的基本配置,这样这些板卡的用户就可以轻松构建一个知道可以工作的系统。您也可以向 Buildroot 添加其他板卡的支持。

要做到这一点,您需要创建一个普通的 Buildroot 配置,可以为该硬件构建一个基本系统:内部工具链、内核、引导加载程序、文件系统和一个简单的仅包含 BusyBox 的用户空间。不应选择任何特定软件包:配置应尽可能简单,仅构建一个工作的基于 BusyBox 的基本系统用于目标平台。当然,您可以为内部项目使用更复杂的配置,但 Buildroot 项目仅会集成基本的板卡配置。因为软件包选择高度依赖于应用。

一旦您有一个知道可以工作的配置,运行 make savedefconfig。这将在 Buildroot 源代码树的根目录生成一个最小的 defconfig 文件。将这个文件移动到 configs/ 目录下,并重命名为 `<板卡名称>_defconfig`。 

如果配置较为复杂,可以手动重新格式化它,并用注释将其分成几个部分,典型的部分包括:架构、工具链选项(通常只是 Linux 头文件版本)、固件、引导加载程序、内核和文件系统。

应始终使用固定的版本或提交哈希来设置不同组件,而不是“最新”版本。例如,设置 BR2_LINUX_KERNEL_CUSTOM_VERSION=y 并将 BR2_LINUX_KERNEL_CUSTOM_VERSION_VALUE 设置为您测试过的内核版本。

建议尽可能使用 Linux 内核和引导加载程序的上游版本,并尽可能使用内核和引导加载程序的默认配置。如果它们不适用于您的板卡,或者没有默认配置,我们鼓励您向对应上游项目提交修复。

不过,在此期间,您可能希望存储特定于目标平台的内核或引导加载程序配置或补丁。为此,请创建目录 board/<制造商> 和子目录 board/<制造商>/<板卡名称>。然后可以在这些目录中存储您的补丁和配置,并从主 Buildroot 配置中引用它们。请参阅第 9 章了解更多细节。

在提交新板卡补丁之前,建议使用最新版本的 gitlab-CI Docker 容器进行测试构建。操作如下:

    $ make <板卡名称>_defconfig 
    $ make

默认情况下,Buildroot 开发人员使用 gitlab.com 注册表上官方托管的镜像,对大多数使用场景来说应该很方便。如果仍然想构建自己的 Docker 镜像,可以从官方镜像作为 Dockerfile 的 FROM 指令:

    FROM registry.gitlab.com/buildroot.org/buildroot/base:YYYYMMDD.HHMM
    RUN ...
    COPY ...

当前版本 YYYYMMDD.HHMM 可以在 Buildroot 源代码树顶部的 .gitlab-ci.yml 文件中找到;所有过去版本都在上述注册表中列出。


## Chapter 18、 添加Buildroot新软件包
本节介绍如何将新软件包(用户空间库或应用程序)集成到Buildroot中。它还展示了如何集成现有软件包,这对修复问题或调整其配置很重要。

添加新软件包时,务必在各种条件下进行测试(见第18.25.3节),并检查代码风格(见第18.25.2节)。

### 18.1 软件包目录
首先,在软件包目录下为您的软件创建一个目录,例如libfoo。

一些软件包已经根据主题在子目录中进行分组:x11r7、qt5和gstreamer。如果您的软件包适合这些类别中的一个,那么请在这些目录下创建软件包目录。但是,不鼓励创建新的子目录。

### 18.2 配置文件
要使软件包在配置工具中显示,需要在软件包目录下创建Config文件。有两种类型:Config.in和Config.in.host。

#### 18.2.1 Config.in文件
对于目标上的软件包,请创建名为Config.in的文件。这个文件将包含与我们的libfoo软件相关的选项描述,这些选项将在配置工具中使用和显示。它基本应包含:

```
config BR2_PACKAGE_LIBFOO
    bool "libfoo"  
    help
        This is a comment that explains what libfoo is. The help text
        should be wrapped.

        http://foosoftware.org/libfoo/
```
bool行,help行和其他元数据信息 about 配置选项必须与一个制表符对齐。帮助文本本身应该与一个制表符和两个空格对齐,行应换行以适应72列,其中制表符计为8个字符,所以文本本身为62个字符。帮助文本必须在空行后面提到项目的上游URL。

作为Buildroot的一项约定,属性顺序如下:
1. 选项类型:bool、string等带有提示的 
2. 如果需要,默认值
3. 任何依赖目标的depends on形式的依赖
4. 任何依赖工具链的depends on形式的依赖 
5. 任何依赖其他软件包的depends on形式的依赖
6. 任何select形式的依赖
7. help关键词和帮助文本

您可以在if BR2_PACKAGE_LIBFOO...endif语句中添加其他子选项来配置软件中的特定内容。您可以查看其他软件包的示例。Config.in文件语法与内核Kconfig文件相同。此语法的文档可在http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt找到。

最后,您必须将新的libfoo/Config.in添加到package/Config.in(如果决定将软件包放入现有类别中的一个,则放在相应子目录)。包含的文件按类别字母排序,不应包含任何除软件包名称外的内容。

    source "package/libfoo/Config.in"

#### 18.2.2 Config.in.host文件
一些软件包也需要为主机系统构建。这里有两种选择:
- 主机软件包仅需要满足一个或多个目标软件包的构建时依赖。在这种情况下,请将host-foo添加到目标软件包的BAR_DEPENDENCIES变量中。不应创建Config.in.host文件。
- 主机软件包应该允许用户从配置菜单明确选择。在这种情况下,为该主机软件包创建Config.in.host文件:
```
config BR2_PACKAGE_HOST_FOO
    bool "host foo"
    help
        This is a comment that explains what foo for the host is.

    http://foosoftware.org/foo/
```
Config.in文件同样适用的编码风格和选项。

最后,您必须将新的libfoo/Config.in.host添加到package/Config.in.host。包含的文件按字母顺序排序,不应包含除软件包名称外的任何内容。

    source "package/foo/Config.in.host"

主机软件包随后将从主机实用程序菜单中可用。


#### 18.2.3选择depends on或select翻译:
您软件包的Config.in文件也必须确保依赖项被启用。通常,Buildroot使用以下规则:
- 对库依赖使用select类型的依赖。这些依赖通常不是显而易见的,因此使用kconfig系统确保依赖项被选择是有意义的。例如,libgtk2软件包使用select BR2_PACKAGE_LIBGLIB2来确保启用这个库。select关键字使用反向语义表达依赖。
- 当用户真的需要了解依赖时,使用depends on类型的依赖。通常,Buildroot会对目标架构、MMU支持和工具链选项(参见第18.2.4节)这样的依赖使用这种依赖类型,或者对“大”东西如X.org系统的依赖使用它。depends on关键字使用正向语义表达依赖。

注意:kconfig语言当前的问题是,这两种依赖语义内在上没有链接。因此,可能会选择一个软件包,但其中一个依赖/需求没有满足。

下面一个例子说明了select和depends on的使用。注意,这两种依赖类型只对相同类型的依赖是传递的。
```
config BR2_PACKAGE_RRDTOOL
    bool "rrdtool"
    depends on BR2_USE_WCHAR
    select BR2_PACKAGE_FREETYPE
    select BR2_PACKAGE_LIBART
    select BR2_PACKAGE_LIBPNG
    select BR2_PACKAGE_ZLIB
    help
        RRDtool is the OpenSource industry standard, high performance
        data logging and graphing system for time series data.

        http://oss.oetiker.ch/rrdtool/
comment "rrdtool needs a toolchain w/ wchar"
    depends on !BR2_USE_WCHAR
```

请注意,这两种依赖类型仅对相同类型的依赖是传递性的。

这意味着在下面的例子中:
```
config BR2_PACKAGE_A
    bool "Package A"

config BR2_PACKAGE_B
    bool "Package B"
    depends on BR2_PACKAGE_A

config BR2_PACKAGE_C
    bool "Package C"
    depends on BR2_PACKAGE_B

config BR2_PACKAGE_D
    bool "Package D"
    select BR2_PACKAGE_B

config BR2_PACKAGE_E
    bool "Package E"
    select BR2_PACKAGE_D
```

- 选择软件包C仅在软件包B被选择的情况下可见,软件包B的选择又只在软件包A被选择时可见。
- 选择软件包E将选择软件包D,软件包D将选择软件包B,但它不会检查软件包B的依赖,所以不会选择软件包A。
- 由于软件包B被选择但软件包A没有被选择,这违反了软件包B对软件包A的依赖。因此,在这样的情况下,依赖关系必须显式添加传递性:
```
config BR2_PACKAGE_D
    bool "Package D"
    depends on BR2_PACKAGE_A
    select BR2_PACKAGE_B

config BR2_PACKAGE_E
    bool "Package E"
    depends on BR2_PACKAGE_A
    select BR2_PACKAGE_D
```

总体来说,对于库依赖,应优先考虑select类型依赖。

请注意,这样的依赖可以确保依赖选项也被启用,但不一定保证依赖项在您的软件包之前被构建。为此,依赖也需要在软件包的.mk文件中表达。

有关格式的其他细节,请参考代码风格。

#### 18.2.4 目标依赖和交叉编译工具链的选项
许多软件包依赖于工具链的某些选项:C库的选择,C++支持,线程支持,RPC支持,宽字符支持或动态库支持。一些软件包只能在某些目标体系结构上构建,或者如果处理器中有MMU支持。

这些依赖关系必须通过Config.in文件中的适当depends on语句来表达。此外,对于工具链选项的依赖,如果该选项未启用,则应显示一个注释,以便用户了解为什么该软件包不可用。对目标体系结构或MMU支持的依赖不应在注释中显式显示:由于用户可能无法自由选择其他目标,显式显示这些依赖关系没有太大意义。

注释只应在工具链选项依赖满足时才可见。这意味着软件包的所有其他依赖(包括对目标体系结构和MMU支持的依赖)都必须在注释定义中重复一次。为了保持清晰,这些非工具链选项的depends on语句应与工具链选项的depends on语句分开。如果在同一文件(通常是主软件包)中存在对配置选项的依赖,最好使用全局if...endif结构,而不是在注释和其他配置选项上重复depends on语句。

软件包foo的依赖注释的一般格式是:
    
    foo needs a toolchain w/ featA, featB, featC

例如:

    mpd needs a toolchain w/ C++, threads, wchar

或者:

    crda needs a toolchain w/ threads

注意：注释文本故意保持简洁,以便它可以适应80字符终端。

本节后面将列出不同的目标和工具链选项,对应的配置符号以及注释文本中的依赖说明。
- 目标体系结构
  - 依赖符号:BR2_powerpc,BR2_mips等(见arch/Config.in)
  - 注释字符串:不添加注释

- MMU支持
  - 依赖符号:BR2_USE_MMU 
  - 注释字符串:不添加注释

- Gcc _sync* 内置函数用于原子操作。它有1字节,2字节,4字节和8字节版本。由于不同体系结构支持不同大小的原子操作,所以每个大小都有一个依赖符号:
  - 依赖符号:BR2_TOOLCHAIN_HAS_SYNC_1 对于1字节, BR2_TOOLCHAIN_HAS_SYNC_2 对于2字节, BR2_TOOLCH对于4字节, BR2_TOOLCHAIN_HAS_SYNC_8 对于8字节。 
  - 注释字符串:无需添加注释
- Gcc _atomic* 内置函数用于原子操作。
  - 依赖符号:BR2_TOOLCHAIN_HAS_ATOMIC。
  - 注释字符串:无需添加注释
- 内核头文件
  - 依赖符号:BR2_TOOLCHAIN_HEADERS_AT_LEAST_X_Y, (用适当的版本替换X_Y,参见toolchain/C)
  - 注释字符串:头文件版本>= X.Y 和/或 <= X.Y(用适当的版本替换X.Y)
- GCC版本
  - 依赖符号:BR2_TOOLCHAIN_GCC_AT_LEAST_X_Y,(用适当的版本替换X_Y,参见toolchain/Config.in)
  - 注释字符串:gcc版本>= X.Y 和/或 <= X.Y(用适当的版本替换X.Y)  
- 宿主GCC版本
  - 依赖符号:BR2_HOST_GCC_AT_LEAST_X_Y,(用适当的版本替换X_Y,参见Config.in)
  - 注释字符串:无需添加注释
  - 注意,通常不是包本身需要最小宿主GCC版本,而是它依赖的宿主包。
- C库
  - 依赖符号:BR2_TOOLCHAIN_USES_GLIBC, BR2_TOOLCHAIN_USES_MUSL, BR2_TOOLCHAIN_USES_UCLIB
  - 注释字符串:对于C库,使用不同的注释文本,如:需要glibc工具链,或者需要带C++的glibc工具链。
- C++支持 
  - 依赖符号:BR2_INSTALL_LIBSTDCPP
  - 注释字符串:C++
- D支持
  - 依赖符号:BR2_TOOLCHAIN_HAS_DLANG  
  - 注释字符串:Dlang
- Fortran支持
  - 依赖符号:BR2_TOOLCHAIN_HAS_FORTRAN
  - 注释字符串:Fortran
- 线程支持 
  - 依赖符号:BR2_TOOLCHAIN_HAS_THREADS
  - 注释字符串:线程(除非也需要BR2_TOOLCHAIN_HAS_THREADS_NPTL,这种情况下仅指定NPTL就足够了)
- NPTL线程支持
    - 依赖符号:BR2_TOOLCHAIN_HAS_THREADS_NPTL
    - 注释字符串:NPTL
- RPC支持 
  - 依赖符号:BR2_TOOLCHAIN_HAS_NATIVE_RPC
  - 注释字符串:RPC
- wchar支持
  - 依赖符号:BR2_USE_WCHAR
  - 注释字符串:wchar
- 动态库
  - 依赖符号:!BR2_STATIC_LIBS
  - 注释字符串:动态库


#### 18.2.5 对Linux内核的依赖
某些包需要Buildroot构建Linux内核,通常是内核模块或固件。Config.in文件中应添加注释来表达这个依赖,与工具链选项依赖类似。格式如下:

    foo needs a Linux kernel to be built

如果同时依赖工具链选项和Linux内核,格式如下: 

    foo needs a toolchain w/ featA, featB, featC and a Linux kernel to be built


#### 18.2.6 对udev/dev管理的依赖
如果一个包需要udev设备管理,它应依赖符号BR2_PACKAGE_HAS_UDEV,并添加以下注释:

    foo needs udev /dev management

如果同时依赖工具链选项和udev设备管理,格式如下:

    foo needs udev /dev management and a toolchain w/ featA, featB, featC


#### 18.2.7 对虚拟包提供的功能依赖
某些功能可以由多个包提供,如openGL库。

有关虚拟包的更多信息,请参阅第18.12节。


### 18.3 .mk文件
最后,这是最难的部分。创建名为libfoo.mk的文件。它描述了如何下载、配置、构建、安装该包等。

根据包类型,需要用不同的方式编写.mk文件,使用不同的基础设施:
- 普通包的Makefile(不使用autotools或CMake):基于类似autotools包使用的基础设施,但开发者需要做更多工作。它指定了配置、编译和安装过程。这种基础设施必须用于不使用autotools作为构建系统的所有包。未来可能会为其他构建系统编写其他专业基础设施。我们通过教程和参考文档进行介绍。
- 基于autotools的Makefile(autoconf, automake等):我们提供了专门的基础设施,因为autotools是很常见的构建系统。这种基础设施必须用于依赖于autotools构建系统的新包。我们通过教程和参考文档进行介绍。
- 基于CMake的Makefile:我们提供了专门的基础设施,因为CMake正在成为越来越常见的构建系统,并且有标准化的行为。这种基础设施必须用于依赖于CMake的新包。我们通过教程和参考文档进行介绍。  
- Python模块的Makefile:我们有专门的基础设施用于使用distutils, flit, pep517或setuptools机制的Python模块。我们通过教程和参考文档进行介绍。
- Lua模块的Makefile:我们有专门的基础设施用于通过LuaRocks网站提供的Lua模块。我们通过教程和参考文档进行介绍。

关于格式细节,请参阅写作规则。

### 18.4 .hash文件 
如果可能,您必须添加第三个文件libfoo.hash,包含libfoo包下载文件的哈希值。不添加.hash文件的唯一原因是下载方式使哈希检查不可能。

如果一个包有版本选择,那么哈希文件可以存储在名为版本号的子目录中,例如package/libfoo/1.2.3/libfoo.hash。这在不同版本具有不同许可条款但存储在同一个文件中的情况下尤其重要。否则,哈希文件应保留在包目录中。

该文件中的哈希值用于验证下载文件和许可证文件的完整性。

该文件的格式为每个需要检查哈希值的文件一行,每行包含以下三个字段,用两个空格分隔:
- 哈希类型,选择以下一种:
  - md5
  - sha1 
  - sha224
  - sha256 
  - sha384
  - sha512
- 文件的哈希值:
  - 对于md5,32个十六进制字符
  - 对于sha1,40个十六进制字符
  - 对于sha224,56个十六进制字符
  - 对于sha256,64个十六进制字符
  - 对于sha384,96个十六进制字符
  - 对于sha512,128个十六进制字符
- 文件的名称:
  - 对于源代码压缩包:文件名不包含任何目录组件的基名
  - 对于许可证文件:它在FOO_LICENSE_FILES中出现的路径

以#开头的行被视为注释,将被忽略。空行也将被忽略。

一个文件可以有多个哈希值,每个哈希值单独占一行。在这种情况下,所有哈希值都必须匹配。

注意:理想情况下,此文件中的哈希值应与上游发布的哈希值匹配,例如在他们的网站或电子邮件公告中。如果上游提供了多个哈希类型(例如sha1和sha512),最好在.hash文件中添加所有这些哈希值。如果上游没有提供任何哈希值,或者只提供了md5哈希值,那么自己计算至少一个强哈希值(优先选择sha256,但不是md5),并在哈希值上面添加一个注释行说明。

注意:许可证文件的哈希值用于检测版本提升时许可证的变化。哈希值在make legal-info目标运行期间进行检查。对于具有多个版本(如Qt5)的包,请在该包的子目录<packageversion>中创建哈希文件(另请参阅第19.2节)。

下面的例子定义了上游为主要的libfoo-1.2.3.tar.bz2源码包提供的sha1和sha256哈希值,上游提供的二进制blob的md5值和本地计算的sha256哈希值,下载补丁的sha256哈希值,以及没有哈希值的归档文件:
```
# Hashes from: http://www.foosoftware.org/download/libfoo-1.2.3.tar.bz2.{sha1,sha256}:
sha1 486fb55c3efa71148fe07895fd713ea3a5ae343a libfoo-1.2.3.tar.bz2
sha256 efc8103cc3bcb06bda6a781532d12701eb081ad83e8f90004b39ab81b65d4369 libfoo-1.2.3.tar.bz2

# md5 from: http://www.foosoftware.org/download/libfoo-1.2.3.tar.bz2.md5, sha256 locally computed:
md5 2d608f3c318c6b7557d551a5a09314f03452f1a1 libfoo-data.bin
sha256 01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b libfoo-data.bin

# Locally computed:
sha256 ff52101fb90bbfc3fe9475e425688c660f46216d7e751c4bbdb1dc85cdccacb9 libfoo-fix-blabla.patch

# Hash for license files:
sha256 a45a845012742796534f7e91fe623262ccfb99460a2bd04015bd28d66fba95b8 COPYING
sha256 01b1f9f2c8ee648a7a596a1abe8aa4ed7899b1c9e5551bda06da6e422b04aa55 doc/COPYING.LGPL
```

如果存在.hash文件,并且它包含一个或多个下载文件的哈希值,则Buildroot计算的哈希值(下载后)必须与.hash文件中存储的哈希值匹配。如果一个或多个哈希值不匹配,Buildroot将视为错误,删除下载文件并中止。

如果.hash文件存在,但它不包含下载文件的哈希值,Buildroot也会视为错误并中止。但是,下载文件会留在下载目录中,因为这通常表示.hash文件有误但下载文件可能是正确的。

目前对从http/ftp服务器,Git仓库和使用scp复制的文件进行哈希值检查。对其他版本控制系统(如Subversion,CVS等)不进行检查,因为Buildroot目前在从这样的版本控制系统获取源代码时无法生成可重复的tar包。

只有对保证稳定的文件添加.hash文件中的哈希值。例如,由Github自动生成的补丁不保证稳定,因此其哈希值可能随时间变化。这样的补丁不应下载,而应本地添加到包文件夹中。

如果缺少.hash文件,则不进行任何检查。

### 18.5 SNNfoo启动脚本
提供系统守护进程的包通常需要在引导时以某种方式启动。Buildroot提供了对几种init系统的支持,部分被视为一级(参见第6.3节),而其他也可用但没有同样的集成级别。理想情况下,所有提供系统守护进程的包应提供BusyBox/SysV init的启动脚本和systemd单元文件。

为保持一致,启动脚本必须遵循参考示例package/busybox/S01syslogd中的样式和结构。下面给出了带注释的样例。systemd单元文件没有特定的编码风格,但如果一个包带有自己的单元文件,且与Buildroot兼容,则优先考虑该单元文件,而不是Buildroot专用的单元文件。

启动脚本的名称由SNN和守护进程名称组成。NN是启动顺序号,需要谨慎选择。例如,需要网络才能启动的程序不应该早于S40network启动。脚本按字母顺序启动,所以S01syslogd比S01watchdogd先启动,S02sysctl随后启动。

```
01: #!/bin/sh
02:
03: DAEMON="syslogd"
04: PIDFILE="/var/run/$DAEMON.pid"
05:
06: SYSLOGD_ARGS=""
07:
08: # shellcheck source=/dev/null
09: [ -r "/etc/default/$DAEMON" ] && . "/etc/default/$DAEMON"
10:
11: # BusyBox' syslogd does not create a pidfile, so pass "-n" in the command line
12: # and use "-m" to instruct start-stop-daemon to create one.
13: start() {
14:     printf 'Starting %s: ' "$DAEMON"
15:     # shellcheck disable=SC2086 # we need the word splitting
16:     start-stop-daemon -b -m -S -q -p "$PIDFILE" -x "/sbin/$DAEMON" \
17:         -- -n $SYSLOGD_ARGS
18:     status=$?
19:     if [ "$status" -eq 0 ]; then
20:         echo "OK"
21:     else
22:         echo "FAIL"
23:     fi
24:     return "$status"
25: }
26:
27: stop() {
28:     printf 'Stopping %s: ' "$DAEMON"
29:     start-stop-daemon -K -q -p "$PIDFILE"
30:     status=$?
31:     if [ "$status" -eq 0 ]; then
32:         rm -f "$PIDFILE"
33:         echo "OK"
34:     else
35:         echo "FAIL"
36:     fi
37:     return "$status"
38: }
39:
40: restart() {
41:     stop
42:     sleep 1
43:     start
44:     }
45:
46: case "$1" in
47:     start|stop|restart)
48:         "$1";;
49:     reload)
50:         # Restart, since there is no true "reload" feature.
51:         restart;;
52:     *)
53:     echo "Usage: $0 {start|stop|restart|reload}"
54:     exit 1
55: esac
```

注意:支持以某种方式重新加载配置(SIGHUP)的程序应提供类似stop()的reload()函数。start-stop-daemon支持-K -s HUP实现此功能。建议始终将-x "/sbin/$DAEMON"附加到所有start-stop-daemon命令,以确保信号设置到与$DAEMON匹配的PID。

启动脚本和单元文件都可以从/etc/default/foo中获取命令行参数,通常如果该文件不存在,除非守护进程需要某些站点特定的命令行参数才能启动,否则它不应阻止守护进程的启动。对于启动脚本,可以在FOO_ARGS="-s -o -m -e -args"中定义默认值,用户可以从/etc/default/foo覆盖此值。


### 18.6 针对具体构建系统的基础设施
我们所说的具有特定构建系统的包,是指所有构建系统不是标准的autotools或CMake的包。这通常包括基于手写Makefile或shell脚本的构建系统的包。
#### 18.6.1 普通包教程
```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_LICENSE = GPL-3.0+
11: LIBFOO_LICENSE_FILES = COPYING
12: LIBFOO_INSTALL_STAGING = YES
13: LIBFOO_CONFIG_SCRIPTS = libfoo-config
14: LIBFOO_DEPENDENCIES = host-libaaa libbbb
15:
16: define LIBFOO_BUILD_CMDS
17:     $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) all
18: endef
19:
20: define LIBFOO_INSTALL_STAGING_CMDS
21:     $(INSTALL) -D -m 0755 $(@D)/libfoo.a $(STAGING_DIR)/usr/lib/libfoo.a
22:     $(INSTALL) -D -m 0644 $(@D)/foo.h $(STAGING_DIR)/usr/include/foo.h
23:     $(INSTALL) -D -m 0755 $(@D)/libfoo.so* $(STAGING_DIR)/usr/lib
24: endef
25:
26: define LIBFOO_INSTALL_TARGET_CMDS
27:     $(INSTALL) -D -m 0755 $(@D)/libfoo.so* $(TARGET_DIR)/usr/lib
28:     $(INSTALL) -d -m 0755 $(TARGET_DIR)/etc/foo.d
29: endef
30:
31: define LIBFOO_USERS
32:     foo -1 libfoo -1 * - - - LibFoo daemon
33: endef
34:
35: define LIBFOO_DEVICES
36:     /dev/foo c 666 0 0 42 0 - - -
37: endef
38:
39: define LIBFOO_PERMISSIONS
40:     /bin/foo f 4755 foo libfoo - - - - -
41: endef
42:
43: $(eval $(generic-package))
```
7-11行定义了元数据信息:包版本(LIBFOO_VERSION)、包含该包的压缩包名称(LIBFOO_SOURCE)(推荐使用xz压缩包)、可以从中下载压缩包的互联网位置(LIBFOO_SITE)、许可证(LIBFOO_LICENSE)、包含许可证文本的文件(LIBFOO_LICENSE_FILES)。所有变量都必须以相同的前缀开头,这里是LIBFOO_。这个前缀总是包名称的大写版本(下面会解释包名称定义在哪里)。

12行指定这个包要在staging空间安装一些内容。这对库包来说经常需要,因为它们必须在staging空间安装头文件和其他开发文件。这将确保执行在LIBFOO_INSTALL_STAGING_CMDS变量中列出的命令。

13行指定需要修复在LIBFOO_INSTALL阶段安装的一些libfoo-config文件。这些*-config文件是位于$(STAGING_DIR)/usr/bin目录的可执行shell脚本,被其他第三方包执行以获取这个特定包的位置和链接选项。

问题是,默认这些*-config文件给出错误的宿主系统链接选项,不适用于交叉编译。

例如:-I/usr/include而不是-I$(STAGING_DIR)/usr/include或者:-L/usr/lib而不是-L$(STAGING_DIR)/usr/lib。

所以使用一些sed魔法修复这些脚本,使它们给出正确的选项。LIBFOO_CONFIG_SCRIPTS的参数是需要修复的shell脚本文件的名称,所有名称相对于$(STAGING_DIR)/usr/bin。如果需要可以给出多个名称。

此外,列在LIBFOO_CONFIG_SCRIPTS中的脚本从$(TARGET_DIR)/usr/bin删除,因为目标上不需要它们。

------------------------------------
**示例18.1** 配置脚本:divine包

divine包安装shell脚本$(STAGING_DIR)/usr/bin/divine-config。
所以它的修复应该是:

    DIVINE_CONFIG_SCRIPTS = divine-config

-----------------------------------
**示例18.2** 配置脚本:imagemagick包:
imagemagick包安装以下脚本:$(STAGING_DIR)/usr/bin/{Magick,Magick++,MagickCore,MagickWand,Wand}-config
所以它的修复应该是:

    IMAGEMAGICK_CONFIG_SCRIPTS = \
    Magick-config Magick++-config \
    MagickCore-config MagickWand-config Wand-config

----------------------------------

14行指定这个包依赖的包,使用小写包名表示,可以是目标包(没有host-前缀)或者宿主包(有host-前缀)。Buildroot将确保这些包在当前包配置前构建和安装。

16-29行定义了包在不同阶段的配置,编译和安装操作。LIBFOO_BUILD_CMDS告诉如何构建包。

LIBFOO_INSTALL_STAGING_CTELLS如何在staging空间安装。LIBFOO_INSTALL_TARGET_CMDS告诉如何在目标空间安装。

所有这些步骤都依赖于 $(@D) 变量,包含源码解压目录。

31-33行定义这个包使用的用户(如运行守护进程)。

35-37行定义设备节点文件。

39-41行定义特定文件权限。

最后,43行调用generic-package函数,根据前面定义的变量生成所有必需的Makefile代码使包正常工作。

#### 18.6.2 普通包参考
有两种通用目标。generic-package宏用于交叉编译目标包。host-generic-package宏用于本地编译宿主包。可以在单个.mk文件中调用它们两次:一次创建目标包规则,一次创建宿主包规则:

    $(eval $(generic-package))
    $(eval $(host-generic-package))

这在目标包编译需要安装一些宿主工具时可能很有用。如果包名是libfoo,那么目标包名也是libfoo,而宿主包名是host-libfoo。这些名称应在其他包的DEPENDENCIES变量中使用,如果它们依赖于libfoo或host-libfoo。

对generic-package和/或host-generic-package的调用必须放在.mk文件最后,在所有变量定义之后。如果有的话,host-generic-package调用必须放在generic-package调用之后。

对于目标包,generic-package使用以包名称大写开头的LIBFOO_*变量。host-generic-package使用HOST_LIBFOO_*变量。对于一些变量,如果没有HOST_LIBFOO_前缀的变量,则包基础设施会使用LIBFOO_前缀的对应变量。这是对可能在目标和宿主包中具有相同值的变量进行的。下面有详细说明。

在.mk文件中可以设置的变量列表(假设包名为libfoo)包括:
- LIBFOO_VERSION,必需,必须包含包版本。如果没有HOST_LIBFOO_VERSION,则假定与LIBFOO_VERSION相同。它也可以是版本控制系统直接获取的包的修订号或标记。例如:
    - 发布压缩包的版本:LIBFOO_VERSION = 0.1.2
    - git树的sha1:LIBFOO_VERSION = cb9d6aa9429e838f0e54faa3d455bcbab5eef057
    - git树的标签:LIBFOO_VERSION = v0.1.2  
        注意:使用分支名作为FOO_VERSION不受支持,因为它无法像人们期望的那样工作:
        1. 由于本地缓存,Buildroot不会重新获取仓库,所以期望能跟随远程仓库的人会很惊讶;
        2. 因为两个构建永远不能完全同时进行,远程仓库的分支任何时候都可能有新提交,两个使用相同Buildroot树和配置的用户可能获取不同源代码,从而导致构建不可重复,人们会很惊讶。

- LIBFOO_SOURCE可以包含包的压缩包名称,Buildroot将从LIBFOO_SITE下载这个压缩包。如果没有指定HOST_LIBFOO_SOURCE,则默认为LIBFOO_SOURCE。如果都没有指定,则假定为libfoo-$(LIBFOO_VERSION).tar.gz。例如:LIBFOO_SOURCE = foobar-$(LIBFOO_VERSION).tar.bz2

- LIBFOO_PATCH可以包含空格分隔的补丁文件名列表,Buildroot将下载并应用于源代码。如果包含://,则Buildroot将假定它是完整URL,从该位置下载补丁。否则,Buildroot将假定应从LIBFOO_SITE下载补丁。如果没有指定HOST_LIBFOO_PATCH,则默认为LIBFOO_PATCH。最后,LIBFOO_PATCH列出的补丁在Buildroot包目录内补丁先应用。

- LIBFOO_SITE提供包位置,可以是URL或本地文件系统路径。支持HTTP、FTP和SCP URL类型获取包压缩包。在这些情况下不包括尾随斜杠:Buildroot会在目录和文件名之间添加适当的斜杠。支持Git、Subversion、Mercurial和Bazaar URL类型直接从源代码管理系统获取包。有一个辅助函数可以更轻松从GitHub下载源码压缩包(参见18.25.4节了解详情)。文件系统路径可以指定压缩包或包含源代码的目录。有关获取方式的更多详细信息,请参阅下面的LIBFOO_SITE_METHOD。  
注意SCP URL应为scp://[user@]host:filepath格式,filepath相对于用户主目录,所以可能需要在前面加斜杠指定绝对路径,如scp://[user@]host:/absolutepath。SFTP URL也一样。
如果没有指定HOST_LIBFOO_SITE,则默认为LIBFOO_SITE。例如:

    LIBFOO_SITE=http://www.libfoosoftware.org/libfoo  
    LIBFOO_SITE=http://svn.xiph.org/trunk/Tremor  
    LIBFOO_SITE=/opt/software/libfoo.tar.gz  
    LIBFOO_SITE=$(TOPDIR)/../src/libfoo  

- LIBFOO_DL_OPTS包含传递给下载器的额外选项列表。用于需要服务器端检查用户登录和密码的文档下载,或使用代理。所有LIBFOO_SITE_METHOD支持的下载方法都支持;有效选项取决于下载方法(参考相关下载工具手册)。

- LIBFOO_EXTRA_DOWNLOADS包含额外需要下载的文件的空格分隔列表。如果包含://,Buildroot将假定它是完整URL,使用该URL下载文件。否则,Buildroot将假定文件位于LIBFOO_SITE。Buildroot不会对这些额外文件做任何操作,由包配方决定如何使用它们$(LIBFOO_DL_DIR)。

- LIBFOO_SITE_METHOD确定获取或复制源代码的方法。在许多情况下,Buildroot会从LIBFOO_SITE内容猜测方法,通常无需设置LIBFOO_SITE_METHOD。如果没有指定HOST_LIBFOO_SITE_METHOD,则默认为LIBFOO_SITE_METHOD的值。  
LIBFOO_SITE_METHOD可能的值包括:
    - wget用于正常的FTP/HTTP压缩包下载。LIBFOO_SITE开始于http://或ftp://默认为此值。
    - scp用于SSH scp下载压缩包。LIBFOO_SITE开始于scp://默认为此值。
    - sftp用于SSH sftp下载压缩包。LIBFOO_SITE开始于sftp://默认为此值。
    - svn从Subversion仓库检出源代码。LIBFOO_SITE开始于svn://默认为此值。http:// Subversion仓库URL必须指定LIBFOO_SITE_METHOD=svn。
    - cvs从CVS仓库获取源代码,匿名pserver模式默认。
    - git从Git仓库获取源代码。LIBFOO_SITE开始于git://默认为此值。
    - hg从Mercurial仓库获取源代码,必须指定LIBFOO_SITE_METHOD=hg。
    - bzr从Bazaar仓库获取源代码。LIBFOO_SITE开始于bzr://默认为此值。
    - file本地压缩包,LIBFOO_SITE指定本地文件名。
    - local本地源代码目录,LIBFOO_SITE指定目录路径。Buildroot将目录内容复制到包构建目录。

- LIBFOO_GIT_SUBMODULES可以设置为YES,以创建包含仓库中的git子模块的归档文件。这只适用于使用git下载的包(即LIBFOO_SITE_METHOD=git)。注意,我们尽量不使用包含捆绑库的git子模块,在这种情况下,我们更倾向于从它们自己的包中使用这些库。

- LIBFOO_GIT_LFS应设置为YES,如果Git仓库使用Git LFS存储大文件。这只适用于使用git下载的包(即LIBFOO_SITE_METHOD=git)。

- LIBFOO_STRIP_COMPONENTS是tar从文件名中提取时必须剥离的前导组件(目录)数。大多数包的压缩包有一个前导组件名为"<pkg-name>-<pkg-version>",因此Buildroot传递--strip-components=1给tar删除它。对于非标准包没有此组件或有多个前导组件需要删除,请设置此变量的值传递给tar。默认:1。

- LIBFOO_EXCLUDES是在提取归档时排除模式的空格分隔列表。该列表中的每个项都作为tar的--exclude选项传递。默认为空。

- LIBFOO_DEPENDENCIES列出当前目标包编译需要的依赖项(以包名表示)。这些依赖项保证在当前包配置开始前编译和安装。但是,这些依赖项的配置修改不会强制重新编译当前包。同样,HOST_LIBFOO_DEPENDENCIES列出当前宿主包的依赖项。

- LIBFOO_EXTRACT_DEPENDENCIES列出当前目标包提取需要的依赖项。这些依赖项保证在当前包提取步骤开始前编译和安装。这只在包基础设施内部使用,包通常不应直接使用。

- LIBFOO_PATCH_DEPENDENCIES列出当前包打补丁需要的依赖项。这些依赖项保证在当前包打补丁前提取和打补丁(但不一定构建)。同样,HOST_LIBFOO_PATCH_DEPENDENCIES列出当前宿主包的依赖项。这很少使用;通常你真正需要的是LIBFOO_DEPENDENCIES。

- LIBFOO_PROVIDES列出libfoo实现的所有虚拟包。参见18.12节。

- LIBFOO_INSTALL_STAGING可以设置为YES或NO(默认)。如果设置为YES,则执行LIBFOO_INSTALL_STA变量中的命令在staging目录安装包。

- LIBFOO_INSTALL_TARGET可以设置为YES(默认)或NO。如果设置为YES,则执行LIBFOO_INSTALL_TARGE变量中的命令在目标目录安装包。

- LIBFOO_INSTALL_IMAGES可以设置为YES或NO(默认)。如果设置为YES,则执行LIBFOO_INSTALL_IMAG变量中的命令在镜像目录安装包。

- LIBFOO_CONFIG_SCRIPTS列出需要特殊修复以支持交叉编译的$(STAGING_DIR)/usr/bin中的文件名称。可以使用空格分隔多个文件名称,所有名称相对于$(STAGING_DIR)/usr/bin。LIBFOO_CONFIG_SCRIPTS列出的文件也从$(TARGET_DIR)/usr/bin删除,因为目标上不需要它们。

- LIBFOO_DEVICES可选地列出Buildroot使用静态设备表创建的设备文件。使用makedevs语法。可以参考第25章找到此语法的一些文档。

- LIBFOO_PERMISSIONS可选地列出构建过程结束时需要做的权限更改。使用makedevs语法。可以参考第25章找到此语法的一些文档。

- LIBFOO_USERS可选地列出为这个包创建的用户,如果它安装了一个程序需要作为特定用户运行(例如作为守护进程或cron作业)。语法在精神上类似makedevs,描述在第26章。

- LIBFOO_LICENSE定义包的许可证(或许可证)。此名称将出现在make legal-info产生的清单文件中。如果许可证出现在SPDX许可证列表中,请使用SPDX短标识符使清单文件统一。否则,用精确和简洁的方式描述许可证,避免模糊名称如BSD实际上是一组许可证。此变量是可选的。如果未定义,未知将出现在此包的许可证字段中。  
此变量的预期格式必须遵循以下规则:
    - 如果包的不同部分根据不同的许可证发布,请使用逗号分隔许可证(例如LIBFOO_LICENSE=GPL-2.0+,LGPL-2.1+)。如果清楚区分哪个组件根据哪个许可证许可,请在括号中注释许可证(例如LIBFOO_LICENSE=GPL-2.0+(programs),LGPL-2.1+(libraries))。
    - 如果一些许可证取决于子选项是否启用,请使用逗号将有条件许可证附加(例如:FOO_LICENSE+=,GPL-2.0+(programs));基础设施将内部删除前面的空格。 
    - 如果包是双重许可的,请使用或关键字分隔许可证(例如LIBFOO_LICENSE=AFL-2.1或GPL-2.0+)。

- LIBFOO_LICENSE_FILES是包含包发布许可证的压缩包中的文件列表,空格分隔。make legal-info将所有这些文件复制到legal-info目录。参见第13章了解更多信息。此变量是可选的。如果未定义,将产生警告提示您,未保存将出现在此包的许可文件字段中。

- LIBFOO_ACTUAL_SOURCE_TARBALL仅适用于LIBFOO_SITE/LIBFOO_SOURCE对指向实际不包含源代码而包含二进制代码的归档的包。这是非常少见的情况,仅知道适用于预编译的外部工具链,但理论上也可能适用于其他包。在这种情况下,通常有单独的压缩包包含实际源代码。设置LIBFOO_ACTUAL_SOURCE_TARBALL为实际源代码归档的名称,Buildroot将下载并在运行make legal-info收集相关法律材料时使用它。注意此文件不会在常规构建中下载,也不会通过make source下载。

- LIBFOO_ACTUAL_SOURCE_SITE提供实际源码压缩包的位置。默认值为LIBFOO_SITE,所以如果二进制和源码归档位于同一目录,则无需设置此变量。如果未设置LIBFOO_ACTUAL_SOURCE_T,则没有设置LIBFOO_ACTUAL_SOURCE_SITE的意义。

- LIBFOO_REDISTRIBUTE可以设置为YES(默认)或NO,表示是否允许重新分发包源代码。对非开源包设置为NO:Buildroot将不会保存此包的源代码收集legal-info时。

- LIBFOO_IGNORE_CVES是空格分隔的CVE列表,告诉Buildroot CVE跟踪工具哪些CVE应该忽略此包。通常用于CVE通过包补丁修复,或因某种原因不影响Buildroot包时使用。必须始终用Makefile注释前面添加CVE。
例如:
    ```
    # 0001-fix-cve-2020-12345.patch
    LIBFOO_IGNORE_CVES += CVE-2020-12345
    # only when built with libbaz, which Buildroot doesn't support
    LIBFOO_IGNORE_CVES += CVE-2020-54321
    ```

- LIBFOO_CPE_ID_*变量集允许包定义其CPE标识符。可用变量包括:

- LIBFOO_CPE_ID_PREFIX,指定CPE标识符的前缀,即前三个字段。未定义时默认值为cpe:2.3:a。

- LIBFOO_CPE_ID_VENDOR,指定CPE标识符的供应商部分。未定义时默认值为<pkgname>_project。

- LIBFOO_CPE_ID_PRODUCT,指定CPE标识符的产品部分。未定义时默认值为<pkgname>。

- LIBFOO_CPE_ID_VERSION,指定CPE标识符的版本部分。未定义时默认值为$(LIBFOO_VERSION)。

- LIBFOO_CPE_ID_UPDATE指定CPE标识符的更新部分。未定义时默认值为*。  
如果定义了这些变量中的任何一个,则通用包基础设施将假定包提供有效的CPE信息。在这种情况下,通用包基础设施将定义LIBFOO_CPE_ID。  
对于宿主包,如果未定义其LIBFOO_CPE_ID_*变量,它将继承对应目标包的这些变量值。

定义这些变量的推荐方式是使用以下语法:  
```
LIBFOO_VERSION = 2.32
```

现在,定义应在构建过程不同阶段执行什么的变量:

- LIBFOO_EXTRACT_CMDS列出提取包时需要执行的操作。通常不需要,因为tar包自动由Buildroot处理。但是,如果包使用非标准归档格式(如ZIP或RAR文件),或者tar包组织方式非标准,此变量允许覆盖包基础设施的默认行为。
- LIBFOO_CONFIGURE_CMDS列出编译前需要执行的配置操作。
- LIBFOO_BUILD_CMDS列出编译时需要执行的操作。
- HOST_LIBFOO_INSTALL_CMDS列出安装宿主包时需要执行的操作。包必须将文件安装到$(HOST_DIR)目录。
- LIBFOO_INSTALL_TARGET_CMDS列出安装目标包到目标目录时需要执行的操作。只需安装运行包所需的文件。
- LIBFOO_INSTALL_STAGING_CMDS列出安装目标包到staging目录时需要执行的操作。所有开发文件都应安装。
- LIBFOO_INSTALL_IMAGES_CMDS列出安装包到镜像目录时需要执行的操作。只能放置不属于TARGET_DIR但必需引导板的二进制镜像。
- LIBFOO_INSTALL_INIT_XXX列出安装init脚本的操作,用于不同的init系统。
- LIBFOO_HELP_CMDS列出打印帮助信息的操作,包含在make help输出中。
- LIBFOO_LINUX_CONFIG_FIXUPS列出构建和使用此包所需的内核配置选项。

推荐定义这些变量的方式是:
```
define LIBFOO_CONFIGURE_CMDS
    action 1
    action 2
    action 3
endef
```

在操作定义中,可以使用以下变量:
- $(LIBFOO_PKGDIR)包含libfoo.mk和Config.in文件所在的目录路径。用于安装打包在Buildroot中的文件,如运行时配置文件、启动画面等。
- $(@D),包含解压缩包源代码的目录。 
- $(LIBFOO_DL_DIR)包含Buildroot为libfoo下载的所有文件存储的目录路径。
- $(TARGET_CC)、$(TARGET_LD)等获取交叉编译工具
- $(TARGET_CROSS)获取交叉编译工具链前缀
- 当然还有$(HOST_DIR)、$(STAGING_DIR)和$(TARGET_DIR)变量正确安装包。除非使用按包目录支持,否则它们指向全局主机、staging和目标目录;使用按包目录支持时,它们指向当前包的主机、staging和目标目录。从包角度没有区别:它应简单使用HOST_DIR、STAGING_DIR和TARGET_DIR。第8.12节有更多按包目录支持细节。

最后,也可以使用钩子。第18.23节有更多信息。


### 18.7 autotools基包基础设施
#### 18.7.1 autotools包教程
首先,看看如何为基于autotools的包编写.mk文件,以一个例子:
```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_INSTALL_STAGING = YES
11: LIBFOO_INSTALL_TARGET = NO
12: LIBFOO_CONF_OPTS = --disable-shared
13: LIBFOO_DEPENDENCIES = libglib2 host-pkgconf
14:
15: $(eval $(autotools-package))
```
第7行声明了包的版本号。

第8-9行声明了压缩包名称(推荐使用xz压缩包)和Web上的压缩包位置。Buildroot将自动从这个位置下载压缩包。

第10行告诉Buildroot将包安装到staging目录。位于output/staging/的staging目录是安装所有包(包括开发文件等)的目录。默认情况下,包不会安装到staging目录,因为通常只需要库安装到staging目录:它们的开发文件需要用于编译依赖它们的其他库或应用程序。默认情况下,启用staging安装时,使用make install命令安装包。

第11行告诉Buildroot不将包安装到目标目录。这个目录将成为运行在目标上的根文件系统。对于纯静态库来说,无需将它们安装到目标目录,因为它们在运行时不会使用。默认情况下启用目标安装;几乎不需要设置此变量为NO。默认情况下,使用make install命令安装包。

第12行告诉Buildroot传递自定义配置选项,在配置和构建包前传递给./configure脚本。

第13行声明依赖关系,以便它们在包构建过程开始前构建。

最后,第15行调用autotools-package宏,生成实际允许构建包的Makefile规则。


#### 18.7.2 autotools包基础设施参考
autotools包基础设施的主要宏是autotools-package。它类似于通用包宏。也可以使用主机autotools包宏实现主机和目标包。

就像通用基础设施一样,autotools基础设施通过在调用autotools-package宏之前定义一些变量来工作。
首先,通用基础设施中存在的所有包元数据信息变量也存在于autotools基础设施中:LIBFOO_VERSION、LIBFOO_SOURCE、LIBFOO_PATCH、LIBFOO_SITE、LIBFOO_SUBDIR、LIBFOO_DEPENDENCIES、LIBFOO_INSTALL_STAGING、LIBFOO_INSTALL_TARGET。

autotools基础设施也可以定义一些特定变量。许多变量只在特定情况下有用,所以典型包只会使用其中一些:
- LIBFOO_SUBDIR可以包含包内包含配置脚本的子目录的名称。如果主配置脚本不在tarball提取的树的根目录中,则这很有用。如果未指定HOST_LIBFOO_SUBDIR,则默认为LIBFOO_SUBDIR。
- LIBFOO_CONF_ENV用于指定传递给配置脚本的额外环境变量。默认为空。
- LIBFOO_CONF_OPTS用于指定传递给配置脚本的额外配置选项。默认为空。
- LIBFOO_MAKE用于指定替代的make命令。当在配置中启用并行构建(使用BR2_JLEVEL)但对于给定的包应禁用此功能时,这通常很有用。默认设置为$(MAKE)。如果包不支持并行构建,则应设置为LIBFOO_MAKE=$(MAKE1)。
- LIBFOO_MAKE_ENV用于指定传递给构建步骤中的make的额外环境变量。这些变量在make命令之前传递。默认为空。
- LIBFOO_MAKE_OPTS用于指定传递给构建步骤中的make的额外变量。这些变量在make命令之后传递。默认为空。
- LIBFOO_AUTORECONF指示是否应重新配置包(即是否应通过重新运行autoconf、automake、libtool等重新生成配置脚本和Makefile.in文件)。有效值为YES和NO。默认值为NO。
- LIBFOO_AUTORECONF_ENV用于指定传递给autoreconf程序的额外环境变量。这些变量在autoreconf命令的环境中传递。默认为空。
- LIBFOO_AUTORECONF_OPTS用于指定传递给autoreconf程序的额外选项。仅在LIBFOO_AUTORECONF=YES时有效。默认为空。
- LIBFOO_AUTOPOINT指示是否应自动设置包(即是否需要复制I18N基础设施)。仅在LIBFOO_AUTORECONF=YES时有效。有效值为YES和NO。默认值为NO。
- LIBFOO_LIBTOOL_PATCH指示是否应应用修复libtool交叉编译问题的Buildroot补丁。有效值为YES和NO。默认值为YES
- LIBFOO_INSTALL_STAGING_OPTS包含用于将包安装到staging目录的make选项。默认值为DESTDIR=$(STAGING_DIR) install,对大多数autotools包正确。仍可覆盖。
- LIBFOO_INSTALL_TARGET_OPTS包含用于将包安装到目标目录的make选项。默认值为DESTDIR=$(TARGET_DIR) install。对大多数autotools包正确,但仍可在需要时覆盖。

使用autotools基础设施,已经定义了构建和安装包所需的所有步骤,它们通常可以很好地支持基于autotools的大多数包。但是,在需要时,仍然可以自定义任何特定步骤:
- 添加后操作钩子(提取、修补、配置、构建或安装后)。详见18.23节。 
- 覆盖其中一个步骤。例如,即使使用autotools基础设施,如果包的.mk文件定义了自己的LIBFOO_CONFIGURE_CMDS变量,也会使用它而不是默认的autotools配置步骤。但是,只应在特定情况下使用此方法。一般情况下不要使用。

### 18.8 CMake基包基础设施
#### 18.8.1 cmake-package教程
首先看一个CMake包的.mk文件示例:
```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_INSTALL_STAGING = YES
11: LIBFOO_INSTALL_TARGET = NO
12: LIBFOO_CONF_OPTS = -DBUILD_DEMOS=ON
13: LIBFOO_DEPENDENCIES = libglib2 host-pkgconf
14:
15: $(eval $(cmake-package))
```
第7行声明了包的版本号。

第8-9行声明了压缩包名称(推荐使用xz压缩包)和Web上的压缩包位置。Buildroot将自动从这个位置下载压缩包。

第10行告诉Buildroot将包安装到staging目录。位于output/staging/的staging目录是安装所有包(包括开发文件等)的目录。默认情况下,包不会安装到staging目录,因为通常只需要库安装到staging目录:它们的开发文件需要用于编译依赖它们的其他库或应用程序。默认情况下,启用staging安装时,使用make install命令安装包。

第11行告诉Buildroot不将包安装到目标目录。这个目录将成为运行在目标上的根文件系统。对于纯静态库来说,无需将它们安装到目标目录,因为它们在运行时不会使用。默认情况下启用目标安装;几乎不需要设置此变量为NO。默认情况下,使用make install命令安装包。

第12行告诉Buildroot在配置包时传递自定义选项给CMake。

第13行声明依赖关系,以便它们在包构建过程开始前构建。

最后,第15行调用cmake-package宏,生成实际允许构建包的Makefile规则。

#### 18.8.2 CMake包基础设施参考
CMake包基础设施的主要宏是cmake-package。它类似于通用包宏generic-package。

也可以使用主机CMake包宏host-cmake-package实现主机和目标包的能力。

就像通用基础设施一样,CMake基础设施通过在调用cmake-package宏之前定义一些变量来工作。

首先,通用基础设施中存在的所有包元数据信息变量也存在于CMake基础设施中:
LIBFOO_VERSION、LIBFOO_SOURCE、LIBFOO_PATCH、LIBFOO_SITE、LIBFOO_SUBDIR、LIBFOO_DEPENDENCIES、
LIBFOO_INSTALL_STAGING、LIBFOO_INSTALL_TARGET。

CMake基础设施也可以定义一些特定变量。许多变量只在特定情况下有用,所以典型包只会使用其中一些。
- LIBFOO_SUBDIR可以包含主CMakeLists.txt文件的子目录名称。
- LIBFOO_CONF_ENV指定传递给CMake的额外环境变量。
- LIBFOO_CONF_OPTS指定传递给CMake的额外配置选项。  
cmake-package基础设施会设置一些常用的CMake选项,所以通常无需在包的*.mk文件中设置,除非要覆盖它们。
    - CMAKE_BUILD_TYPE由BR2_ENABLE_RUNTIME_DEBUG驱动;
    - CMAKE_INSTALL_PREFIX; 
    - BUILD_SHARED_LIBS由BR2_STATIC_LIBS驱动;
    - BUILD_DOC、BUILD_DOCS被禁用;
    - BUILD_EXAMPLE、BUILD_EXAMPLES被禁用;
    - BUILD_TEST、BUILD_TESTS、BUILD_TESTING被禁用。
- LIBFOO_SUPPORTS_IN_SOURCE_BUILD=NO应当设置为包无法在源目录内构建但需要单独的构建目录。
- LIBFOO_MAKE用于指定替代的make命令。默认为$(MAKE)。如果不支持并行构建,应设置为LIBFOO_MAKE=$(MAKE1)。
- LIBFOO_MAKE_ENV指定传递给make的额外环境变量。这些变量在make命令之前传递。默认为空。
- LIBFOO_MAKE_OPTS指定传递给make的额外变量。这些变量在make命令之后传递。默认为空。
- LIBFOO_INSTALL_OPTS包含安装到主机目录的make选项。默认为install,对大多数CMake包正确。
- LIBFOO_INSTALL_STAGING_OPTS包含安装到staging目录的make选项。默认为DESTDIR=$(STAGING_DIR) install/fast,对大多数CMake包正确。但都可以覆盖。
- LIBFOO_INSTALL_TARGET_OPTS包含安装到目标目录的make选项。默认为DESTDIR=$(TARGET_DIR) install/fast。对大多数CMake包正确,但仍可在需要时覆盖。

使用CMake基础设施,已经定义了构建和安装包所需的所有步骤,它们通常可以很好地支持基于CMake的大多数包。但是,在需要时,仍然可以自定义任何特定步骤:
- 添加后操作钩子(提取、修补、配置、构建或安装后)。详见18.23节。
- 覆盖其中一个步骤。例如,即使使用CMake基础设施,如果包的.mk文件定义了自己的LIBFOO_CONFIGURE_CMDS变量,也会使用它而不是默认的CMake配置步骤。但是,只应在特定情况下使用此方法。一般情况下不要使用。


### 18.9 Python包基础设施
此基础设施适用于使用标准Python setuptools或pep517机制作为构建系统的Python包,通常通过使用setup.py脚本或pyproject.toml文件识别。
#### 18.9.1 python-package教程
首先看一个Python包的.mk文件示例:
```
01: ################################################################################
02: #
03: # python-foo
04: #
05: ################################################################################
06:
07: PYTHON_FOO_VERSION = 1.0
08: PYTHON_FOO_SOURCE = python-foo-$(PYTHON_FOO_VERSION).tar.xz
09: PYTHON_FOO_SITE = http://www.foosoftware.org/download
10: PYTHON_FOO_LICENSE = BSD-3-Clause
11: PYTHON_FOO_LICENSE_FILES = LICENSE
12: PYTHON_FOO_ENV = SOME_VAR=1
13: PYTHON_FOO_DEPENDENCIES = libmad
14: PYTHON_FOO_SETUP_TYPE = distutils
15:
16: $(eval $(python-package))
```
第7行声明了包的版本号。

第8-9行声明了压缩包名称(推荐使用xz压缩包)和Web上的压缩包位置。Buildroot将自动从这个位置下载压缩包。

第10-11行提供了包的许可详情(第10行是许可证,第11行是包含许可文本的文件)。

第12行告诉Buildroot在配置包时将自定义选项传递给Python setup.py脚本。

第13行声明依赖关系,以便它们在包构建过程开始前构建。

第14行声明了使用的具体Python构建系统。在此例中使用的是Python的distutils构建系统。

支持的四种构建系统有distutils、flit、pep517和setuptools。

最后,第16行调用python-package宏,生成实际允许构建包的Makefile规则。

