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

默认情况下，Buildroot不支持顶层并行构建，因此不需要运行 make -jN 。但是，顶层并行构建有实验性支持，请参阅第8.12节。

make命令通常会执行以下步骤：

- 下载源文件（如果需要）；
- 配置、构建和安装交叉编译工具链，或者简单地导入外部工具链；
- 配置、构建和安装选定的目标软件包；
- 构建内核映像 Kernel（如果选择的话）；
- 构建引加载程序映像 Boodloader（如果选择的话）；
- 在选定的格式中创建根文件系统 rootfs 。

Buildroot的输出存储在一个单独的目录 output/ 中。该目录包含几个子目录：
- images/ 存储所有的映像（内核映像、引导加载程序和根文件系统映像）。这些是您需要放在目标系统上的文件。
- build/ 构建所有组件的地方（包括Buildroot在主机上需要的工具和为目标编译的软件包）。该目录包含每个组件的一个子目录。
- host/ 包含为主机构建的工具和目标工具链的 sysroot 。前者是为主机编译的工具的安装，这些工具对于Buildroot的正确执行是必需的，包括交叉编译工具链。后者是类似于根文件系统层次结构的层次结构。它包含所有用户空间软件包的头文件和库，这些软件包提供和安装其他软件包使用的库。然而，该目录不打算成为目标的根文件系统：它包含许多开发文件、未剥离的二进制文件和库，使其对于嵌入式系统来说太大了。这些开发文件用于为依赖于其他库的目标编译库和应用程序。
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

如上所述，随系统提供的编译工具链在主机系统上运行并为主机系统的处理器生成代码。由于嵌入式系统使用了不同的处理器，您需要一个交叉编译工具链 —— 一个在主机系统上运行但为目标系统（和目标处理器）生成代码的编译工具链。例如，如果您的主机系统使用x86，而目标系统使用ARM，那么主机上的常规编译工具链将在x86上运行并为x86生成代码，而交叉编译工具链将在x86上运行并为ARM生成代码。

Buildroot为交叉编译工具链提供了两种解决方案：
- 内部工具链后端，在配置界面中称为 `Buildroot toolchain` 。
- 外部工具链后端，在配置界面中称为 `External toolchain` 。

在这两个解决方案之间的选择是通过 `Toolchain` 菜单中的 `Toolchain Type` 选项来完成的。一旦选择了其中一个解决方案，就会出现许多配置选项，它们在以下部分中有详细说明。

#### 6.1.1 内部工具链后端
内部工具链后端是Buildroot在构建目标嵌入式系统的用户空间应用程序和库之前，通过自身构建交叉编译工具链的后端。

该后端支持多个C库：uClibc-ng、glibc和musl。

选择此后端后，会出现一些选项。其中最重要的是：
- 更改用于构建工具链的Linux内核头文件的版本。这个项目值得一些解释。在构建交叉编译工具链的过程中，也在构建C库。该库提供用户空间应用程序与Linux内核之间的接口。为了知道如何与Linux内核进行“通信”，C库需要访问 `Linux kernel headers` （即内核的.h文件），这些文件定义了用户空间和内核之间的接口（系统调用、数据结构等）。由于此接口向后兼容，用于构建工具链的Linux内核头文件的版本不需要完全匹配您打算在嵌入式系统上运行的Linux内核的版本。它们只需要具有与您打算运行的Linux内核版本相等或更旧版本。如果使用的内核头文件比您在嵌入式系统上运行的Linux内核更新，则C库可能使用您的Linux内核不提供的接口。
- 更改GCC编译器、binutils和C库的版本。
- 选择多个工具链选项（仅适用于uClibc）：工具链是否应具有RPC支持（主要用于NFS）、宽字符（wide-char）支持、区域设置支持（用于国际化）、C++支持或线程支持。根据您选择的选项，Buildroot菜单中可见的用户空间应用程序和库的数量将发化：许多应用程序和库需要启用某些工具链选项。大多数软件包在需要启用某个特定工具链选项以启用这些软件包时会显示注释。如果需要，您可以通过运行make  `uclibc-menuconfig` 来进一步细化uClibc配置。但请注意，Buildroot中的所有软件包都是针对Buildroot 中捆绑的默认 uClibc 配置进行测试的：如果您通过从 uClibc 中删除功能来偏离此配置，则某些软件包可能无法。

值得注意的是，每当修改其中一个选项时，链和系统都必须重新构建。请参阅第8.2节。

此后端的优点：
- 与Buildroot完全集
- 快速，只构建必要的部分

此后端的缺点：
- 在执行make clean时需要重新构建工具链，这需要时间。如果您试图缩短构建时间，请考虑使用外部工具链后端。

#### 6.1.2 外部工具链后端
外部工具链后端允许使用现有的预构建交叉编译工具链。Buildroot已经了解一些知名的交叉编译工具链（来自ARM的Linaro和Sourcery CodeBench，以及x86-64、PowerPC和MIPS），并且能够自动下载它们，或者可以指定一个自定义工具链，可以通过下载或本地安装获得。

然后，您有三种解决方案来使用外部工具链：

- 使用预定义的外部工具链配置文件，让 Buildroot 下载、提取和安装工具链。 Buildroot 已经了解一些 [CodeSourcery](https://www.plm.automation.siemens.com/global/en/products/embedded-software/sourcery-codebench-lite-downloads.html) 和 [Linaro](https://www.linaro.org/) 工具链。只需在可用的工具链中选择工具链配置文件即可。这绝对是最的解决方案。

- 使用预定义的外部工具链配置文件，但是不让 Buildroot 下载和提取工具链，而是告诉 Buildroot 您的系统上已经安装了工具链的位置。只需在可用的工具链中选择工具链配置文件，取消选择自动下载工具链，并在工具链路径文本框中填写您的交叉编译工具链的路径。

- 使用完全自定义的外部工具链。这对于使用 cstool-NG 或 Buildroot 本身生成的工具链特有用。要做到这一点，选择工具链列表中的自定义工具链解决方案。您需要填写工具链路径、工具链前缀和外部工具链C库选项。然后，您需要告诉 Buildroot 您的外部工具链支持的内容。如果您的外部工具链使用g，您只需告诉它是否支持 C++ 以及是否具有内置的 RPC 支持。如果您的外部工具链使用 uClibc 库，则需要告 root 它是否支持 RPC 、宽字符、区域设置、程序调用、线程和C++。在执行开始时， Buildroot 会告诉您所选选项是否与工具链配置不匹配。

我们的外部工具链支持已经通过了来自 CodeSourcery 和 Linaro 的工具链、 crosstool-NG 生成的链以及Buildroot自身生成的工具链的测试。一般来说，所有支持 sysroot 功能的工具链都应该可以工作。如果不能工作，请随时与开发人联系。

我们不支持由 OpenEmbedded 或 Yocto 生成的工具链或 SDK ，因为这些工具链不是纯粹的工具链（即只有编译器、binutils、C和C++库）。相反，这些工具链附带了一套非常庞大的预编译库和程序。因此，Buildroot 无法导入工具链的 sysroot ，因为它将包含数百兆字节的通常由Buildroot构建的预编译库。

我们也不支持使用发行版工具链（即由您的发行版安装的 gcc/binutils/C库）作为构建目标软件的工具链。这是因为您的发行版工具链不是一个“纯粹”的工具链（即只有C/C++库），所以我们无法将其正确地导入 Buildroot 构建环境中。因此，即使您正在为 x86 或 x86_64 目标构建系统，您也必须使用Buildroot或 crosstool-NG 生成交叉编译工具链。

如果您想为您的项目生成一个自定义工具链，可以在Buildroot中用作外部工具链，建议使用Buildroot本身（参见第6.1.3节）或 crosstool-NG 来构建它。

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

- 第一种解决方案是使用设备表进行静态管理(`Static using device table`)。这是Linux中处理设备文件的旧的经典方式。使用此方法，设备文件会持久地存储在根文件系统中（即它们在重新启动后仍然存在），并且没有任何自动创建和删除这些设备文件的机制，当硬件设备被添加或从系统中移除时。因此，Buildroot使用设备表创建一组标准的设备文件，其中默认的设备表存储在 `Buildroot` 源代码中的 `system/device_table_dev.txt` 中。当 `Buildroot` 生成最终的根文件系统映像时，会处理此文件，并且设备文件在 `output/target` 目录中不可见。 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 选项允许更改 `Buildroot` 使用的默认设备表，或添加附加的设备表，以便 `Buildroot` 在构建过程中创建附加的设备文件。因此，如果您使用此方法，并且您的系统中缺少设备文件，您可以创建一个 `board/<yourcompany>/<yourproject>/device_table_dev.txt` 文件，其中包含您附加设备文件的描述，然后您可以将 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 设置为 `system/device_table_dev.txt board/<yourcompany>/<yourproject>/device_table_dev.txt` 。有关设备表文件格式的更多详细信息，请参阅第25章。

- 第二种解决方案是仅使用动态的 `devtmpfs` 。 `devtmpfs` 是一个虚拟文件系统，它被内嵌在 Linux 内核中，从内核2.6.32开始引入(如果您使用较旧的内核，则无法使用此选项)。当它挂载在 `/dev` 上时，这个虚拟文件系统会自动使设备文件在添加或删除系统中的硬件设备时出现和消失。这个文件系统在重启后不是持久的:它是由内核动态填充的。使用 `devtmpfs` 需要启用以下内核配置选项: `CONFIG_DEVTMPFS` 和 `CONFIG_DEVTMPFS_MOUNT` 。当 `Buildroot` 负责为您的嵌入式设备构建 Linux 内核时，它会确保启用这两个选项。但是，如果您在 `Buildroot` 外部构建Linux内核，那么启用这两个选项就是您的责任(如果您未能启用它们，您的 `Buildroot` 系统将无法启动)。

- 第三种解决方案是使用动态的 `devtmpfs + mdev` 。这种方法也依赖于上述详细介绍的 `devtmpfs` 虚拟文件系统(所以内核配置中必须启用 `CONFIG_DEVTMPFS` 和 `CONFIG_DEVTMPFS_MOUNT` 这两个选项)，但在其上添加了 `mdev` 用户空间实用程序。 `mdev` 是 `BusyBox` 的一部分程序，内核将在设备添加或删除时调用它。通过 `/etc/mdev.conf` 配置文件，可以配置 `mdev` ，例如为设备文件设置特定的权限或所有权，或者在设备出现或消失时调用脚本或应用程序等。简而言之，它允许用户空间响应设备添加和删除事件。例如， `mdev` 可以自动加载当设备出现在系统上时需要的内核模块。如果设备需要固件， `mdev` 还负责将固件内容推送到内核。 `mdev` 是 `udev` 的一个轻量级实现(具有较少的功能)。有关 `mdev` 和其配置文件的语法的更多详细信息，请参阅 http://git.busybox.net/-busybox/tree/docs/mdev.txt 。

- 第四种解决方案是使用动态的 `devtmpfs + eudev` 。这种方法也依赖于上面详细介绍的 `devtmpfs` 虚拟文件系统，但在其上添加了 `eudev` 用户空间守护进程。 `eudev` 是一个后台运行的守护进程，它会被内核调用来响应系统中设备的添加或删除。它是 `mdev` 更重量级的解决方案，但提供了更高的灵活性。 `eudev` 是 `udev` 的独立版本， `udev` 原来是大多数桌面 Linux 发行版使用的用户空间守护进程，现在它成为 `Systemd` 的一部分。有关详细信息，请参阅 http://en.wikipedia.org/wiki/Udev 。

Buildroot开发人员的建议是从仅使用动态 `devtmpfs` 的解决方案开始，直到您需要用户空间被通知设备添加/删除，或者需要固件，此时使用动态 `devtmpfs + mdev` 通常是一个很好的解决方案。
需要注意的是，如果选择 `systemd` 作为 init 系统， `/dev` 管理将由 `systemd` 提供的 `udev` 程序进行。

### 6.3 init 系统
`init` 程序是内核启动的第一个用户空间程序(它的PID号是1)，它负责启动用户空间服务和程序(例如:Web服务器，图形应用程序，其他网络服务器等)。

`Buildroot` 允许使用三种不同类型的 `init` 系统，可以从 系统配置->初始化系统(`System configuration > Init system:`)中选择:

- 第一种解决方案是 `BusyBox` 。除了许多程序外， `BusyBox` 还实现了一个基本的 `init` 程序，对大多数嵌入式系统来说已经足够。启用 `BR2_INIT_BUSYBOX` 将确保 `BusyBox` 构建和安装其 `init` 程序。这是 `Buildroot` 的默认解决方案。`BusyBox init` 程序将在引导时读取 `/etc/inittab` 文件以知道下一个操作。此文件的语法可以在 http://git.busybox.net/busybox/tree/examples/inittab 找到(请注意，`BusyBox inittab` 语法是特殊的:不要使用互联网上的任何 `inittab` 文档来学习 `BusyBox inittab` )`。Buildroot` 默认的 `inittab` 存储在 `system/skeleton/etc/inittab` 。除了挂载几个重要的文件系统外，默认 `inittab` 的主要工作是启动 `/etc/init.d/rcS ` shell 脚本，并启动 `getty` 程序(提供登录提示)。

- 第二种解决方案是 `systemV` 。这种解决方案使用传统的 `sysvinit` 程序，它被打包在 `Buildroot` 的 `package/sysvinit` 包中。这曾是大多数桌面 Linux 发行版使用的解决方案，直到它们转向更现代的替代方案如 `Upstart` 或 `Systemd` 。 `sysvinit` 也使用 `inittab` 文件(语法与 `BusyBox` 版本略有不同)。与此 `init` 解决方案一起安装的默认 `inittab` 位于 `package/sysvinit/inittab` 。

- 第三种解决方案是 `systemd` 。 `systemd` 是 Linux 新的一代 `init` 系统。它比传统的 init 程序功能更强大:支持高度并行化、使用 `socket` 和 `D-Bus` 激活启动服务、支持按需启动守护进程、使用 Linux 控制组跟踪进程状态等。 `systemd` 对相对复杂的嵌入式系统很有用，例如需要 `D-Bus` 和服务间通信的系统。需要注意的是， `systemd` 带来了大量依赖，如 `dbus、udev` 等。有关 `systemd` 的更多详细信息，请参阅 http://www.freedesktop.org/wiki/Software/systemd 。

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

    $ make V=1 <target>

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

**清除**: 当任何架构或工具链配置选项更改时，需要显式清理。
删除所有构建产品(包括构建目录、主机、交叉编译和目标树、镜像以及工具链):

    $ make clean

**生成手册**: 当前手册源码位于 docs/manual 目录。要生成手册:

    $ make manual-clean
    $ make manual 
手册输出将生成在output/docs/manual。（注意：构建手册需要一些工具 (see: Section 2.2).）

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

在内部， Buildroot 通过所谓的印记文件跟踪每个包各个构建步骤的完成情况。它们存储在包构建目录 `output/build/<package>-<version>/` 中，命名为 `.stamp_<step-name>` 。

上述命令简单地操纵这些印记文件，强制Buildroot重新启动包构建过程的特定一组步骤。

有关包特殊 make 目标的更多详细信息请参阅第8.13.5节。


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
生成的图位于 output/graphs/graph-depends.pdf 。

如果系统非常大，依赖关系图可能过于复杂难以阅读。所以可以生成给定包的依赖关系图:

    make <pkg>-graph-depends 
生成的图位于 output/graph/<pkg>-graph-depends.pdf 。

注意依赖关系图使用Graphviz项目的dot工具生成，您必须在系统中安装此工具才能使用此功能。在大多数发行版中它作为graphviz软件包提供。

默认情况下，依赖关系图使用PDF格式生成。但是通过设置 `BR2_GRAPH_OUT` 环境变量，可以切换到其他格式，如PNG、PostScript或SVG。dot工具的-T选项支持的所有格式都支持。

    BR2_GRAPH_OUT=svg make graph-depends

可以通过设置 BR2_GRAPH_DEPS_OPTS 环境变量控制 graph-depends 行为。
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

这个graph-build目标需要安装Python的Matplotlib和Numpy库（大多数发行版上 -matplotlib 和 python-numpy ），如果使用的是Python版本低于2.7，则还需要安装argparse模块（大多数发行版上是 python-argparse ）。

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
#### 8.13.1 在Buildroot之外使用生成的工具链
您可能希望为目标平台编译自己的程序或其他未打包在Buildroot中的软件。为了做到这一点，您可以使用Buildroot生成的工具链。

Buildroot生成的工具链默认位于 `output/host/` 。使用它的最简单方法是将 `output/host/bin/` 添加到您的PATH环境变量中，然后使用 ARCH-linux-gcc、ARCH-linux-objdump、ARCH-linux-ld等命令。

另外，Buildroot 还可以通过运行 make sdk 命令将所有选定软件包的工具链和开发文件作为SDK导出。这将生成一个 tarball ，其中包含主机目录 output/host/ 的内容，命名为 <TARGET-TUPLE>_sdk-buildroot.tar.gz（可以通过设置环境变量 BR2_SDK_PREFIX 进行覆盖），位于 output/images/ 目录中。

然后，可以将此tarball分发给应用程序开发人员，当他们想要开发尚未打包为 Buildroot 软件包的应用程序时使用。

在提取SDK tarball后，用户必须运行relocate-sdk.sh脚本（位于SDK的顶级目录），以确保所有路径都更新为新位置。

另外，如果您只想准备SDK而不生成tarball（例如，因为您将只移动主机目录，或者将自己生成tarball），Buildroot 还允许您只使用 `make prepare-sdk` 来准备SDK，而不实际生成tarball。

为了方便起见，通过选择选项 BR2_PACKAGE_HOST_ENVIRONMENT_SETUP ，您可以在 output/host/ 中安装一个 environment-setup 脚本，因此在您的SDK中也会有这个脚本。您可以使用.  your/sdk/path/environment-setup 来源化此脚本，以导出一些环境变量，帮助使用Buildroot SDK进行交叉编译项目：PATH将包含SDK二进制文件，标准的 autotools 变量将被定义为适当的值，并且 CONFIGURE_FLAGS 将包含基本的 ./configure 选项，用于交叉编译 autotools 项目。它还提供了一些有用的命令。但请注意，一旦此脚本被源化，环境只会为交叉编译设置，不再适用于本地编译。

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
要实现NFS引导，请在文件系统镜像菜单中启用tar根文件系统。

构建完成后，只需运行以下命令来设置NFS根目录:

    sudo tar -xavf /path/to/output_dir/rootfs.tar -C /path/to/nfs_root_dir 

记住在/etc/exports中添加此路径。

然后，您可以从目标设备执行NFS引导。

#### 14.1.2 实时CD
要构建实时CD镜像，请在文件系统镜像菜单中启用iso镜像选项。请注意，此选项仅在 x86 和 x86-64 体系结构上可用，如果您使用 Buildroot 构建内核。

您可以使用IsoLinux、Grub或Grub 2作为引导程序构建实时CD镜像，但只有IsoLinux支持使此镜像既可以作为实时CD也可以作为实时U盘使用(通过Build hybrid image选项)。

您可以使用QEMU测试您的实时CD镜像:

    qemu-system-i386 -cdrom output/images/rootfs.iso9660

或者如果它是混合ISO，可以将其用作硬盘镜像:

    qemu-system-i386 -hda output/images/rootfs.iso9660

它可以使用dd轻松刻录到U盘:

    dd if=output/images/rootfs.iso9660 of=/dev/sdb


### 14.2 chroot
如果您要在生成的镜像中chroot，则应了解几点:
- 您应该从tar根文件系统镜像设置新的根目录;
- 选择的目标体系结构要兼容您的主机，或者您应使用一些qemu-*二进制文件并正确设置它们的binfmt属性，才能在主机上运行为目标构建的二进制文件;
- Buildroot当前不提供为此目的正确构建和设置的host-qemu和binfmt。




-------------
-------------

# III 进阶指导

## Chapter 15、Buildroot 的工作原理
如上所述，Buildroot本质上是一个包含Makefile的集合，它可以下载、配置和使用正确选项编译软件。它还包括各种软件包的补丁 - 主要是那些参与交叉编译工具链(gcc、binutils和uClibc)的软件包。

每个软件包基本上对应一个Makefile，它使用.mk扩展名。Makefile被分成许多不同部分。

- toolchain/目录包含所有与交叉编译工具链相关的软件的Makefile和相关文件:binutils、gcc、gdb、内核头文件和uClibc。
- arch/目录包含Buildroot支持的所有处理器体系结构的定义。
- package/目录包含Buildroot可以编译并添加到目标根文件系统的所有用户空间工具和库的Makefile和相关文件。每个包对应一个子目录。
- linux/目录包含内核的Makefile和相关文件。
- boot/目录包含Buildroot支持的引导程序的Makefile和相关文件。
- system/目录包含系统集成支持，例如目标文件系统骨架和初始化系统选择。
- fs/目录包含与生成目标根文件系统镜像相关的软件的Makefile和相关文件。

每个目录至少包含两个文件:
- something.mk是下载、配置、编译和安装包something的Makefile。
- Config.in是配置工具描述文件的一部分。它描述与该包相关的选项。
主Makefile执行以下步骤(在配置完成后):
- 在输出目录(默认为output/，也可以使用O=指定其他值)中创建所有输出目录:staging、target、build等。
- 生成工具链目标。对于内置工具链，这意味着生成交叉编译工具链。对于外部工具链，这意味着检查外部工具链的功能并将其导入到Buildroot环境中。
- 生成TARGETS变量中列出的所有目标。这个变量由所有单个组件的Makefile填充。生成这些目标将触发用户空间包(库、程序)、内核和引导程序的编译，以及根文件系统镜像的生成，这取决于配置。


## Chapter 16、 翻译:代码风格
总体来说，这些代码风格规则旨在帮助您向Buildroot添加新文件或重构现有文件。

如果您稍微修改一些现有文件，那么重要的是保持整个文件的一致性，所以您可以:
- 遵循该文件中可能已过时的代码风格;
- 或者完全重构它，以使其符合这些规则。

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
- 帮助文本应该换行适应72列，其中制表符计为8个字符，所以文本本身为62个字符。

Config.in文件是Buildroot中使用的配置工具Kconfig的输入。有关Kconfig语言的更多详细信息，请参阅http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt。

### 16.2 .mk文件
- 标题(Header):文件从标题开始。它包含模块名称，最好使用小写，括在由80个井号组成的分隔符之间。标题后必须有一个空行:
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
注意:define块中的命令应始终使用制表符开始，以便make将其识别为命令。
- 可选依赖:
  - 优先使用多行语法。  
    YES:
    ```
    ifeq ($(BR2_PACKAGE_PYTHON3)，y)
    LIBFOO_CONF_OPTS += --with-python-support
    LIBFOO_DEPENDENCIES += python3
    else
    LIBFOO_CONF_OPTS += --without-python-support
    endif
    ```
    NO:
    ```
    LIBFOO_CONF_OPTS += --with$(if $(BR2_PACKAGE_PYTHON3)，，out)-python-support
    LIBFOO_DEPENDENCIES += $(if $(BR2_PACKAGE_PYTHON3)，python3，)
    ```
  - 将配置选项和依赖关系保持在一起。

- 可选钩子(HOOK):将钩子定义和赋值保持在一个if块中。  
    YES:
    ```
    ifneq ($(BR2_LIBFOO_INSTALL_DATA)，y)
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

    ifneq ($(BR2_LIBFOO_INSTALL_DATA)，y)
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
- 每个节点(部分、分区、文件、子节点)名称必须在同一行使用一个左花括号，而右花括号必须在新行且后跟一个新行，除最后一个节点外。选项(如option size =)也一样。
- 每个选项(如image、offset、size)等号赋值必须与其前后各有一个空格。
- 文件名至少应以genimage前缀开头并使用.cfg扩展名以便识别。 
- 允许的offset和size选项单位有:G、M、K(不用k)。如果无法用上述单位精确表示字节数，则使用0x十六进制前缀，或者直接使用字节数。在注释中分别使用GB、MB、KB(不用kb)替换G、M、K。
- 对于ChatMindAi分区，partition-type-uuid值必须是U(代表EFI系统分区，genimage扩展为c12a7328-f81f-11d2-ba4b-00a0c93ec93b)、F(FAT分区，扩展为ebd0a0a2-b9e5-4433-87c0-68b6b72699c7)或L(根文件系统或其他文件系统，扩展为0fc63daf-8483-4772-8e79-3d69d8477de4)。尽管L是genimage的默认值，但我们优先在genimage.cfg文件中明确指定它。最后，这些缩写应不使用双引号，例如partition-type-uuid = U。如果指定了明确的GUID，应使用小写字母。

genimage.cfg文件是Buildroot用于生成最终镜像文件的genimage工具的输入。有关genimage语言的更多详细信息，请参考https://github.com/pengutronix/genimage/blob/master/README.rst。


### 16.4 文档
文档使用asciidoc格式。

有关asciidoc语法的更多详细信息，请参阅https://asciidoc-py.github.io/userguide.html。

### 16.5 支持脚本 
support/和utils/目录中的一些脚本使用Python编写，应遵循Python代码的PEP8风格指南。


## Chapter 17、 为特定板卡添加支持
Buildroot 包含了对几个公开可用硬件板卡的基本配置，这样这些板卡的用户就可以轻松构建一个知道可以工作的系统。您也可以向 Buildroot 添加其他板卡的支持。

要做到这一点，您需要创建一个普通的 Buildroot 配置，可以为该硬件构建一个基本系统:内部工具链、内核、引导加载程序、文件系统和一个简单的仅包含 BusyBox 的用户空间。不应选择任何特定软件包:配置应尽可能简单，仅构建一个工作的基于 BusyBox 的基本系统用于目标平台。当然，您可以为内部项目使用更复杂的配置，但 Buildroot 项目仅会集成基本的板卡配置。因为软件包选择高度依赖于应用。

一旦您有一个知道可以工作的配置，运行 make savedefconfig。这将在 Buildroot 源代码树的根目录生成一个最小的 defconfig 文件。将这个文件移动到 configs/ 目录下，并重命名为 `<板卡名称>_defconfig`。 

如果配置较为复杂，可以手动重新格式化它，并用注释将其分成几个部分，典型的部分包括:架构、工具链选项(通常只是 Linux 头文件版本)、固件、引导加载程序、内核和文件系统。

应始终使用固定的版本或提交哈希来设置不同组件，而不是“最新”版本。例如，设置 BR2_LINUX_KERNEL_CUSTOM_VERSION=y 并将 BR2_LINUX_KERNEL_CUSTOM_VERSION_VALUE 设置为您测试过的内核版本。

建议尽可能使用 Linux 内核和引导加载程序的上游版本，并尽可能使用内核和引导加载程序的默认配置。如果它们不适用于您的板卡，或者没有默认配置，我们鼓励您向对应上游项目提交修复。

不过，在此期间，您可能希望存储特定于目标平台的内核或引导加载程序配置或补丁。为此，请创建目录 board/<制造商> 和子目录 board/<制造商>/<板卡名称>。然后可以在这些目录中存储您的补丁和配置，并从主 Buildroot 配置中引用它们。请参阅第 9 章了解更多细节。

在提交新板卡补丁之前，建议使用最新版本的 gitlab-CI Docker 容器进行测试构建。操作如下:

    $ make <板卡名称>_defconfig 
    $ make

默认情况下，Buildroot 开发人员使用 gitlab.com 注册表上官方托管的镜像，对大多数使用场景来说应该很方便。如果仍然想构建自己的 Docker 镜像，可以从官方镜像作为 Dockerfile 的 FROM 指令:

    FROM registry.gitlab.com/buildroot.org/buildroot/base:YYYYMMDD.HHMM
    RUN ...
    COPY ...

当前版本 YYYYMMDD.HHMM 可以在 Buildroot 源代码树顶部的 .gitlab-ci.yml 文件中找到;所有过去版本都在上述注册表中列出。


## Chapter 18、 添加Buildroot新软件包
本节介绍如何将新软件包(用户空间库或应用程序)集成到Buildroot中。它还展示了如何集成现有软件包，这对修复问题或调整其配置很重要。

添加新软件包时，务必在各种条件下进行测试(见第18.25.3节)，并检查代码风格(见第18.25.2节)。

### 18.1 软件包目录
首先，在软件包目录下为您的软件创建一个目录，例如libfoo。

一些软件包已经根据主题在子目录中进行分组:x11r7、qt5和gstreamer。如果您的软件包适合这些类别中的一个，那么请在这些目录下创建软件包目录。但是，不鼓励创建新的子目录。

### 18.2 配置文件
要使软件包在配置工具中显示，需要在软件包目录下创建Config文件。有两种类型:Config.in和Config.in.host。

#### 18.2.1 Config.in文件
对于目标上的软件包，请创建名为Config.in的文件。这个文件将包含与我们的libfoo软件相关的选项描述，这些选项将在配置工具中使用和显示。它基本应包含:

```
config BR2_PACKAGE_LIBFOO
    bool "libfoo"  
    help
        This is a comment that explains what libfoo is. The help text
        should be wrapped.

        http://foosoftware.org/libfoo/
```
bool行，help行和其他元数据信息 about 配置选项必须与一个制表符对齐。帮助文本本身应该与一个制表符和两个空格对齐，行应换行以适应72列，其中制表符计为8个字符，所以文本本身为62个字符。帮助文本必须在空行后面提到项目的上游URL。

作为Buildroot的一项约定，属性顺序如下:
1. 选项类型:bool、string等带有提示的 
2. 如果需要，默认值
3. 任何依赖目标的depends on形式的依赖
4. 任何依赖工具链的depends on形式的依赖 
5. 任何依赖其他软件包的depends on形式的依赖
6. 任何select形式的依赖
7. help关键词和帮助文本

您可以在if BR2_PACKAGE_LIBFOO...endif语句中添加其他子选项来配置软件中的特定内容。您可以查看其他软件包的示例。Config.in文件语法与内核Kconfig文件相同。此语法的文档可在http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt找到。

最后，您必须将新的libfoo/Config.in添加到package/Config.in(如果决定将软件包放入现有类别中的一个，则放在相应子目录)。包含的文件按类别字母排序，不应包含任何除软件包名称外的内容。

    source "package/libfoo/Config.in"

#### 18.2.2 Config.in.host文件
一些软件包也需要为主机系统构建。这里有两种选择:
- 主机软件包仅需要满足一个或多个目标软件包的构建时依赖。在这种情况下，请将host-foo添加到目标软件包的BAR_DEPENDENCIES变量中。不应创建Config.in.host文件。
- 主机软件包应该允许用户从配置菜单明确选择。在这种情况下，为该主机软件包创建Config.in.host文件:
```
config BR2_PACKAGE_HOST_FOO
    bool "host foo"
    help
        This is a comment that explains what foo for the host is.

    http://foosoftware.org/foo/
```
Config.in文件同样适用的编码风格和选项。

最后，您必须将新的libfoo/Config.in.host添加到package/Config.in.host。包含的文件按字母顺序排序，不应包含除软件包名称外的任何内容。

    source "package/foo/Config.in.host"

主机软件包随后将从主机实用程序菜单中可用。


#### 18.2.3选择depends on或select翻译:
您软件包的Config.in文件也必须确保依赖项被启用。通常，Buildroot使用以下规则:
- 对库依赖使用select类型的依赖。这些依赖通常不是显而易见的，因此使用kconfig系统确保依赖项被选择是有意义的。例如，libgtk2软件包使用select BR2_PACKAGE_LIBGLIB2来确保启用这个库。select关键字使用反向语义表达依赖。
- 当用户真的需要了解依赖时，使用depends on类型的依赖。通常，Buildroot会对目标架构、MMU支持和工具链选项(参见第18.2.4节)这样的依赖使用这种依赖类型，或者对“大”东西如X.org系统的依赖使用它。depends on关键字使用正向语义表达依赖。

注意:kconfig语言当前的问题是，这两种依赖语义内在上没有链接。因此，可能会选择一个软件包，但其中一个依赖/需求没有满足。

下面一个例子说明了select和depends on的使用。注意，这两种依赖类型只对相同类型的依赖是传递的。
```
config BR2_PACKAGE_RRDTOOL
    bool "rrdtool"
    depends on BR2_USE_WCHAR
    select BR2_PACKAGE_FREETYPE
    select BR2_PACKAGE_LIBART
    select BR2_PACKAGE_LIBPNG
    select BR2_PACKAGE_ZLIB
    help
        RRDtool is the OpenSource industry standard， high performance
        data logging and graphing system for time series data.

        http://oss.oetiker.ch/rrdtool/
comment "rrdtool needs a toolchain w/ wchar"
    depends on !BR2_USE_WCHAR
```

请注意，这两种依赖类型仅对相同类型的依赖是传递性的。

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

- 选择软件包C仅在软件包B被选择的情况下可见，软件包B的选择又只在软件包A被选择时可见。
- 选择软件包E将选择软件包D，软件包D将选择软件包B，但它不会检查软件包B的依赖，所以不会选择软件包A。
- 由于软件包B被选择但软件包A没有被选择，这违反了软件包B对软件包A的依赖。因此，在这样的情况下，依赖关系必须显式添加传递性:
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

总体来说，对于库依赖，应优先考虑select类型依赖。

请注意，这样的依赖可以确保依赖选项也被启用，但不一定保证依赖项在您的软件包之前被构建。为此，依赖也需要在软件包的.mk文件中表达。

有关格式的其他细节，请参考代码风格。

#### 18.2.4 目标依赖和交叉编译工具链的选项
许多软件包依赖于工具链的某些选项:C库的选择，C++支持，线程支持，RPC支持，宽字符支持或动态库支持。一些软件包只能在某些目标体系结构上构建，或者如果处理器中有MMU支持。

这些依赖关系必须通过Config.in文件中的适当depends on语句来表达。此外，对于工具链选项的依赖，如果该选项未启用，则应显示一个注释，以便用户了解为什么该软件包不可用。对目标体系结构或MMU支持的依赖不应在注释中显式显示:由于用户可能无法自由选择其他目标，显式显示这些依赖关系没有太大意义。

注释只应在工具链选项依赖满足时才可见。这意味着软件包的所有其他依赖(包括对目标体系结构和MMU支持的依赖)都必须在注释定义中重复一次。为了保持清晰，这些非工具链选项的depends on语句应与工具链选项的depends on语句分开。如果在同一文件(通常是主软件包)中存在对配置选项的依赖，最好使用全局if...endif结构，而不是在注释和其他配置选项上重复depends on语句。

软件包foo的依赖注释的一般格式是:
    
    foo needs a toolchain w/ featA， featB， featC

例如:

    mpd needs a toolchain w/ C++， threads， wchar

或者:

    crda needs a toolchain w/ threads

注意：注释文本故意保持简洁，以便它可以适应80字符终端。

本节后面将列出不同的目标和工具链选项，对应的配置符号以及注释文本中的依赖说明。
- 目标体系结构
  - 依赖符号:BR2_powerpc，BR2_mips等(见arch/Config.in)
  - 注释字符串:不添加注释

- MMU支持
  - 依赖符号:BR2_USE_MMU 
  - 注释字符串:不添加注释

- Gcc _sync* 内置函数用于原子操作。它有1字节，2字节，4字节和8字节版本。由于不同体系结构支持不同大小的原子操作，所以每个大小都有一个依赖符号:
  - 依赖符号:BR2_TOOLCHAIN_HAS_SYNC_1 对于1字节， BR2_TOOLCHAIN_HAS_SYNC_2 对于2字节， BR2_TOOLCH对于4字节， BR2_TOOLCHAIN_HAS_SYNC_8 对于8字节。 
  - 注释字符串:无需添加注释
- Gcc _atomic* 内置函数用于原子操作。
  - 依赖符号:BR2_TOOLCHAIN_HAS_ATOMIC。
  - 注释字符串:无需添加注释
- 内核头文件
  - 依赖符号:BR2_TOOLCHAIN_HEADERS_AT_LEAST_X_Y， (用适当的版本替换X_Y，参见toolchain/C)
  - 注释字符串:头文件版本>= X.Y 和/或 <= X.Y(用适当的版本替换X.Y)
- GCC版本
  - 依赖符号:BR2_TOOLCHAIN_GCC_AT_LEAST_X_Y，(用适当的版本替换X_Y，参见toolchain/Config.in)
  - 注释字符串:gcc版本>= X.Y 和/或 <= X.Y(用适当的版本替换X.Y)  
- 宿主GCC版本
  - 依赖符号:BR2_HOST_GCC_AT_LEAST_X_Y，(用适当的版本替换X_Y，参见Config.in)
  - 注释字符串:无需添加注释
  - 注意，通常不是包本身需要最小宿主GCC版本，而是它依赖的宿主包。
- C库
  - 依赖符号:BR2_TOOLCHAIN_USES_GLIBC， BR2_TOOLCHAIN_USES_MUSL， BR2_TOOLCHAIN_USES_UCLIB
  - 注释字符串:对于C库，使用不同的注释文本，如:需要glibc工具链，或者需要带C++的glibc工具链。
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
  - 注释字符串:线程(除非也需要BR2_TOOLCHAIN_HAS_THREADS_NPTL，这种情况下仅指定NPTL就足够了)
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
某些包需要Buildroot构建Linux内核，通常是内核模块或固件。Config.in文件中应添加注释来表达这个依赖，与工具链选项依赖类似。格式如下:

    foo needs a Linux kernel to be built

如果同时依赖工具链选项和Linux内核，格式如下: 

    foo needs a toolchain w/ featA， featB， featC and a Linux kernel to be built


#### 18.2.6 对udev/dev管理的依赖
如果一个包需要udev设备管理，它应依赖符号BR2_PACKAGE_HAS_UDEV，并添加以下注释:

    foo needs udev /dev management

如果同时依赖工具链选项和udev设备管理，格式如下:

    foo needs udev /dev management and a toolchain w/ featA， featB， featC


#### 18.2.7 对虚拟包提供的功能依赖
某些功能可以由多个包提供，如openGL库。

有关虚拟包的更多信息，请参阅第18.12节。


### 18.3 .mk文件
最后，这是最难的部分。创建名为libfoo.mk的文件。它描述了如何下载、配置、构建、安装该包等。

根据包类型，需要用不同的方式编写.mk文件，使用不同的基础设施:
- 普通包的Makefile(不使用autotools或CMake):基于类似autotools包使用的基础设施，但开发者需要做更多工作。它指定了配置、编译和安装过程。这种基础设施必须用于不使用autotools作为构建系统的所有包。未来可能会为其他构建系统编写其他专业基础设施。我们通过教程和参考文档进行介绍。
- 基于autotools的Makefile(autoconf， automake等):我们提供了专门的基础设施，因为autotools是很常见的构建系统。这种基础设施必须用于依赖于autotools构建系统的新包。我们通过教程和参考文档进行介绍。
- 基于CMake的Makefile:我们提供了专门的基础设施，因为CMake正在成为越来越常见的构建系统，并且有标准化的行为。这种基础设施必须用于依赖于CMake的新包。我们通过教程和参考文档进行介绍。  
- Python模块的Makefile:我们有专门的基础设施用于使用distutils， flit， pep517或setuptools机制的Python模块。我们通过教程和参考文档进行介绍。
- Lua模块的Makefile:我们有专门的基础设施用于通过LuaRocks网站提供的Lua模块。我们通过教程和参考文档进行介绍。

关于格式细节，请参阅写作规则。

### 18.4 .hash文件 
如果可能，您必须添加第三个文件libfoo.hash，包含libfoo包下载文件的哈希值。不添加.hash文件的唯一原因是下载方式使哈希检查不可能。

如果一个包有版本选择，那么哈希文件可以存储在名为版本号的子目录中，例如package/libfoo/1.2.3/libfoo.hash。这在不同版本具有不同许可条款但存储在同一个文件中的情况下尤其重要。否则，哈希文件应保留在包目录中。

该文件中的哈希值用于验证下载文件和许可证文件的完整性。

该文件的格式为每个需要检查哈希值的文件一行，每行包含以下三个字段，用两个空格分隔:
- 哈希类型，选择以下一种:
  - md5
  - sha1 
  - sha224
  - sha256 
  - sha384
  - sha512
- 文件的哈希值:
  - 对于md5，32个十六进制字符
  - 对于sha1，40个十六进制字符
  - 对于sha224，56个十六进制字符
  - 对于sha256，64个十六进制字符
  - 对于sha384，96个十六进制字符
  - 对于sha512，128个十六进制字符
- 文件的名称:
  - 对于源代码压缩包:文件名不包含任何目录组件的基名
  - 对于许可证文件:它在FOO_LICENSE_FILES中出现的路径

以#开头的行被视为注释，将被忽略。空行也将被忽略。

一个文件可以有多个哈希值，每个哈希值单独占一行。在这种情况下，所有哈希值都必须匹配。

注意:理想情况下，此文件中的哈希值应与上游发布的哈希值匹配，例如在他们的网站或电子邮件公告中。如果上游提供了多个哈希类型(例如sha1和sha512)，最好在.hash文件中添加所有这些哈希值。如果上游没有提供任何哈希值，或者只提供了md5哈希值，那么自己计算至少一个强哈希值(优先选择sha256，但不是md5)，并在哈希值上面添加一个注释行说明。

注意:许可证文件的哈希值用于检测版本提升时许可证的变化。哈希值在make legal-info目标运行期间进行检查。对于具有多个版本(如Qt5)的包，请在该包的子目录<packageversion>中创建哈希文件(另请参阅第19.2节)。

下面的例子定义了上游为主要的libfoo-1.2.3.tar.bz2源码包提供的sha1和sha256哈希值，上游提供的二进制blob的md5值和本地计算的sha256哈希值，下载补丁的sha256哈希值，以及没有哈希值的归档文件:
```
# Hashes from: http://www.foosoftware.org/download/libfoo-1.2.3.tar.bz2.{sha1，sha256}:
sha1 486fb55c3efa71148fe07895fd713ea3a5ae343a libfoo-1.2.3.tar.bz2
sha256 efc8103cc3bcb06bda6a781532d12701eb081ad83e8f90004b39ab81b65d4369 libfoo-1.2.3.tar.bz2

# md5 from: http://www.foosoftware.org/download/libfoo-1.2.3.tar.bz2.md5， sha256 locally computed:
md5 2d608f3c318c6b7557d551a5a09314f03452f1a1 libfoo-data.bin
sha256 01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b libfoo-data.bin

# Locally computed:
sha256 ff52101fb90bbfc3fe9475e425688c660f46216d7e751c4bbdb1dc85cdccacb9 libfoo-fix-blabla.patch

# Hash for license files:
sha256 a45a845012742796534f7e91fe623262ccfb99460a2bd04015bd28d66fba95b8 COPYING
sha256 01b1f9f2c8ee648a7a596a1abe8aa4ed7899b1c9e5551bda06da6e422b04aa55 doc/COPYING.LGPL
```

如果存在.hash文件，并且它包含一个或多个下载文件的哈希值，则Buildroot计算的哈希值(下载后)必须与.hash文件中存储的哈希值匹配。如果一个或多个哈希值不匹配，Buildroot将视为错误，删除下载文件并中止。

如果.hash文件存在，但它不包含下载文件的哈希值，Buildroot也会视为错误并中止。但是，下载文件会留在下载目录中，因为这通常表示.hash文件有误但下载文件可能是正确的。

目前对从http/ftp服务器，Git仓库和使用scp复制的文件进行哈希值检查。对其他版本控制系统(如Subversion，CVS等)不进行检查，因为Buildroot目前在从这样的版本控制系统获取源代码时无法生成可重复的tar包。

只有对保证稳定的文件添加.hash文件中的哈希值。例如，由Github自动生成的补丁不保证稳定，因此其哈希值可能随时间变化。这样的补丁不应下载，而应本地添加到包文件夹中。

如果缺少.hash文件，则不进行任何检查。

### 18.5 SNNfoo启动脚本
提供系统守护进程的包通常需要在引导时以某种方式启动。Buildroot提供了对几种init系统的支持，部分被视为一级(参见第6.3节)，而其他也可用但没有同样的集成级别。理想情况下，所有提供系统守护进程的包应提供BusyBox/SysV init的启动脚本和systemd单元文件。

为保持一致，启动脚本必须遵循参考示例package/busybox/S01syslogd中的样式和结构。下面给出了带注释的样例。systemd单元文件没有特定的编码风格，但如果一个包带有自己的单元文件，且与Buildroot兼容，则优先考虑该单元文件，而不是Buildroot专用的单元文件。

启动脚本的名称由SNN和守护进程名称组成。NN是启动顺序号，需要谨慎选择。例如，需要网络才能启动的程序不应该早于S40network启动。脚本按字母顺序启动，所以S01syslogd比S01watchdogd先启动，S02sysctl随后启动。

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
11: # BusyBox' syslogd does not create a pidfile， so pass "-n" in the command line
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
50:         # Restart， since there is no true "reload" feature.
51:         restart;;
52:     *)
53:     echo "Usage: $0 {start|stop|restart|reload}"
54:     exit 1
55: esac
```

注意:支持以某种方式重新加载配置(SIGHUP)的程序应提供类似stop()的reload()函数。start-stop-daemon支持-K -s HUP实现此功能。建议始终将-x "/sbin/$DAEMON"附加到所有start-stop-daemon命令，以确保信号设置到与$DAEMON匹配的PID。

启动脚本和单元文件都可以从/etc/default/foo中获取命令行参数，通常如果该文件不存在，除非守护进程需要某些站点特定的命令行参数才能启动，否则它不应阻止守护进程的启动。对于启动脚本，可以在FOO_ARGS="-s -o -m -e -args"中定义默认值，用户可以从/etc/default/foo覆盖此值。


### 18.6 针对具体构建系统的基础设施
我们所说的具有特定构建系统的包，是指所有构建系统不是标准的autotools或CMake的包。这通常包括基于手写Makefile或shell脚本的构建系统的包。
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
7-11行定义了元数据信息:包版本(LIBFOO_VERSION)、包含该包的压缩包名称(LIBFOO_SOURCE)(推荐使用xz压缩包)、可以从中下载压缩包的互联网位置(LIBFOO_SITE)、许可证(LIBFOO_LICENSE)、包含许可证文本的文件(LIBFOO_LICENSE_FILES)。所有变量都必须以相同的前缀开头，这里是LIBFOO_。这个前缀总是包名称的大写版本(下面会解释包名称定义在哪里)。

12行指定这个包要在staging空间安装一些内容。这对库包来说经常需要，因为它们必须在staging空间安装头文件和其他开发文件。这将确保执行在LIBFOO_INSTALL_STAGING_CMDS变量中列出的命令。

13行指定需要修复在LIBFOO_INSTALL阶段安装的一些libfoo-config文件。这些*-config文件是位于$(STAGING_DIR)/usr/bin目录的可执行shell脚本，被其他第三方包执行以获取这个特定包的位置和链接选项。

问题是，默认这些*-config文件给出错误的宿主系统链接选项，不适用于交叉编译。

例如:-I/usr/include而不是-I$(STAGING_DIR)/usr/include或者:-L/usr/lib而不是-L$(STAGING_DIR)/usr/lib。

所以使用一些sed魔法修复这些脚本，使它们给出正确的选项。LIBFOO_CONFIG_SCRIPTS的参数是需要修复的shell脚本文件的名称，所有名称相对于$(STAGING_DIR)/usr/bin。如果需要可以给出多个名称。

此外，列在LIBFOO_CONFIG_SCRIPTS中的脚本从$(TARGET_DIR)/usr/bin删除，因为目标上不需要它们。

------------------------------------
**示例18.1** 配置脚本:divine包

divine包安装shell脚本$(STAGING_DIR)/usr/bin/divine-config。
所以它的修复应该是:

    DIVINE_CONFIG_SCRIPTS = divine-config

-----------------------------------
**示例18.2** 配置脚本:imagemagick包:
imagemagick包安装以下脚本:$(STAGING_DIR)/usr/bin/{Magick，Magick++，MagickCore，MagickWand，Wand}-config
所以它的修复应该是:

    IMAGEMAGICK_CONFIG_SCRIPTS = \
    Magick-config Magick++-config \
    MagickCore-config MagickWand-config Wand-config

----------------------------------

14行指定这个包依赖的包，使用小写包名表示，可以是目标包(没有host-前缀)或者宿主包(有host-前缀)。Buildroot将确保这些包在当前包配置前构建和安装。

16-29行定义了包在不同阶段的配置，编译和安装操作。LIBFOO_BUILD_CMDS告诉如何构建包。

LIBFOO_INSTALL_STAGING_CTELLS如何在staging空间安装。LIBFOO_INSTALL_TARGET_CMDS告诉如何在目标空间安装。

所有这些步骤都依赖于 $(@D) 变量，包含源码解压目录。

31-33行定义这个包使用的用户(如运行守护进程)。

35-37行定义设备节点文件。

39-41行定义特定文件权限。

最后，43行调用generic-package函数，根据前面定义的变量生成所有必需的Makefile代码使包正常工作。

#### 18.6.2 普通包参考
有两种通用目标。generic-package宏用于交叉编译目标包。host-generic-package宏用于本地编译宿主包。可以在单个.mk文件中调用它们两次:一次创建目标包规则，一次创建宿主包规则:

    $(eval $(generic-package))
    $(eval $(host-generic-package))

这在目标包编译需要安装一些宿主工具时可能很有用。如果包名是libfoo，那么目标包名也是libfoo，而宿主包名是host-libfoo。这些名称应在其他包的DEPENDENCIES变量中使用，如果它们依赖于libfoo或host-libfoo。

对generic-package和/或host-generic-package的调用必须放在.mk文件最后，在所有变量定义之后。如果有的话，host-generic-package调用必须放在generic-package调用之后。

对于目标包，generic-package使用以包名称大写开头的LIBFOO_*变量。host-generic-package使用HOST_LIBFOO_*变量。对于一些变量，如果没有HOST_LIBFOO_前缀的变量，则包基础设施会使用LIBFOO_前缀的对应变量。这是对可能在目标和宿主包中具有相同值的变量进行的。下面有详细说明。

在.mk文件中可以设置的变量列表(假设包名为libfoo)包括:
- LIBFOO_VERSION，必需，必须包含包版本。如果没有HOST_LIBFOO_VERSION，则假定与LIBFOO_VERSION相同。它也可以是版本控制系统直接获取的包的修订号或标记。例如:
    - 发布压缩包的版本:LIBFOO_VERSION = 0.1.2
    - git树的sha1:LIBFOO_VERSION = cb9d6aa9429e838f0e54faa3d455bcbab5eef057
    - git树的标签:LIBFOO_VERSION = v0.1.2  
        注意:使用分支名作为FOO_VERSION不受支持，因为它无法像人们期望的那样工作:
        1. 由于本地缓存，Buildroot不会重新获取仓库，所以期望能跟随远程仓库的人会很惊讶;
        2. 因为两个构建永远不能完全同时进行，远程仓库的分支任何时候都可能有新提交，两个使用相同Buildroot树和配置的用户可能获取不同源代码，从而导致构建不可重复，人们会很惊讶。

- LIBFOO_SOURCE可以包含包的压缩包名称，Buildroot将从LIBFOO_SITE下载这个压缩包。如果没有指定HOST_LIBFOO_SOURCE，则默认为LIBFOO_SOURCE。如果都没有指定，则假定为libfoo-$(LIBFOO_VERSION).tar.gz。例如:LIBFOO_SOURCE = foobar-$(LIBFOO_VERSION).tar.bz2

- LIBFOO_PATCH可以包含空格分隔的补丁文件名列表，Buildroot将下载并应用于源代码。如果包含://，则Buildroot将假定它是完整URL，从该位置下载补丁。否则，Buildroot将假定应从LIBFOO_SITE下载补丁。如果没有指定HOST_LIBFOO_PATCH，则默认为LIBFOO_PATCH。最后，LIBFOO_PATCH列出的补丁在Buildroot包目录内补丁先应用。

- LIBFOO_SITE提供包位置，可以是URL或本地文件系统路径。支持HTTP、FTP和SCP URL类型获取包压缩包。在这些情况下不包括尾随斜杠:Buildroot会在目录和文件名之间添加适当的斜杠。支持Git、Subversion、Mercurial和Bazaar URL类型直接从源代码管理系统获取包。有一个辅助函数可以更轻松从GitHub下载源码压缩包(参见18.25.4节了解详情)。文件系统路径可以指定压缩包或包含源代码的目录。有关获取方式的更多详细信息，请参阅下面的LIBFOO_SITE_METHOD。  
注意SCP URL应为scp://[user@]host:filepath格式，filepath相对于用户主目录，所以可能需要在前面加斜杠指定绝对路径，如scp://[user@]host:/absolutepath。SFTP URL也一样。
如果没有指定HOST_LIBFOO_SITE，则默认为LIBFOO_SITE。例如:

    LIBFOO_SITE=http://www.libfoosoftware.org/libfoo  
    LIBFOO_SITE=http://svn.xiph.org/trunk/Tremor  
    LIBFOO_SITE=/opt/software/libfoo.tar.gz  
    LIBFOO_SITE=$(TOPDIR)/../src/libfoo  

- LIBFOO_DL_OPTS包含传递给下载器的额外选项列表。用于需要服务器端检查用户登录和密码的文档下载，或使用代理。所有LIBFOO_SITE_METHOD支持的下载方法都支持;有效选项取决于下载方法(参考相关下载工具手册)。

- LIBFOO_EXTRA_DOWNLOADS包含额外需要下载的文件的空格分隔列表。如果包含://，Buildroot将假定它是完整URL，使用该URL下载文件。否则，Buildroot将假定文件位于LIBFOO_SITE。Buildroot不会对这些额外文件做任何操作，由包配方决定如何使用它们$(LIBFOO_DL_DIR)。

- LIBFOO_SITE_METHOD确定获取或复制源代码的方法。在许多情况下，Buildroot会从LIBFOO_SITE内容猜测方法，通常无需设置LIBFOO_SITE_METHOD。如果没有指定HOST_LIBFOO_SITE_METHOD，则默认为LIBFOO_SITE_METHOD的值。  
LIBFOO_SITE_METHOD可能的值包括:
    - wget用于正常的FTP/HTTP压缩包下载。LIBFOO_SITE开始于http://或ftp://默认为此值。
    - scp用于SSH scp下载压缩包。LIBFOO_SITE开始于scp://默认为此值。
    - sftp用于SSH sftp下载压缩包。LIBFOO_SITE开始于sftp://默认为此值。
    - svn从Subversion仓库检出源代码。LIBFOO_SITE开始于svn://默认为此值。http:// Subversion仓库URL必须指定LIBFOO_SITE_METHOD=svn。
    - cvs从CVS仓库获取源代码，匿名pserver模式默认。
    - git从Git仓库获取源代码。LIBFOO_SITE开始于git://默认为此值。
    - hg从Mercurial仓库获取源代码，必须指定LIBFOO_SITE_METHOD=hg。
    - bzr从Bazaar仓库获取源代码。LIBFOO_SITE开始于bzr://默认为此值。
    - file本地压缩包，LIBFOO_SITE指定本地文件名。
    - local本地源代码目录，LIBFOO_SITE指定目录路径。Buildroot将目录内容复制到包构建目录。

- LIBFOO_GIT_SUBMODULES可以设置为YES，以创建包含仓库中的git子模块的归档文件。这只适用于使用git下载的包(即LIBFOO_SITE_METHOD=git)。注意，我们尽量不使用包含捆绑库的git子模块，在这种情况下，我们更倾向于从它们自己的包中使用这些库。

- LIBFOO_GIT_LFS应设置为YES，如果Git仓库使用Git LFS存储大文件。这只适用于使用git下载的包(即LIBFOO_SITE_METHOD=git)。

- LIBFOO_STRIP_COMPONENTS是tar从文件名中提取时必须剥离的前导组件(目录)数。大多数包的压缩包有一个前导组件名为"<pkg-name>-<pkg-version>"，因此Buildroot传递--strip-components=1给tar删除它。对于非标准包没有此组件或有多个前导组件需要删除，请设置此变量的值传递给tar。默认:1。

- LIBFOO_EXCLUDES是在提取归档时排除模式的空格分隔列表。该列表中的每个项都作为tar的--exclude选项传递。默认为空。

- LIBFOO_DEPENDENCIES列出当前目标包编译需要的依赖项(以包名表示)。这些依赖项保证在当前包配置开始前编译和安装。但是，这些依赖项的配置修改不会强制重新编译当前包。同样，HOST_LIBFOO_DEPENDENCIES列出当前宿主包的依赖项。

- LIBFOO_EXTRACT_DEPENDENCIES列出当前目标包提取需要的依赖项。这些依赖项保证在当前包提取步骤开始前编译和安装。这只在包基础设施内部使用，包通常不应直接使用。

- LIBFOO_PATCH_DEPENDENCIES列出当前包打补丁需要的依赖项。这些依赖项保证在当前包打补丁前提取和打补丁(但不一定构建)。同样，HOST_LIBFOO_PATCH_DEPENDENCIES列出当前宿主包的依赖项。这很少使用;通常你真正需要的是LIBFOO_DEPENDENCIES。

- LIBFOO_PROVIDES列出libfoo实现的所有虚拟包。参见18.12节。

- LIBFOO_INSTALL_STAGING可以设置为YES或NO(默认)。如果设置为YES，则执行LIBFOO_INSTALL_STA变量中的命令在staging目录安装包。

- LIBFOO_INSTALL_TARGET可以设置为YES(默认)或NO。如果设置为YES，则执行LIBFOO_INSTALL_TARGE变量中的命令在目标目录安装包。

- LIBFOO_INSTALL_IMAGES可以设置为YES或NO(默认)。如果设置为YES，则执行LIBFOO_INSTALL_IMAG变量中的命令在镜像目录安装包。

- LIBFOO_CONFIG_SCRIPTS列出需要特殊修复以支持交叉编译的$(STAGING_DIR)/usr/bin中的文件名称。可以使用空格分隔多个文件名称，所有名称相对于$(STAGING_DIR)/usr/bin。LIBFOO_CONFIG_SCRIPTS列出的文件也从$(TARGET_DIR)/usr/bin删除，因为目标上不需要它们。

- LIBFOO_DEVICES可选地列出Buildroot使用静态设备表创建的设备文件。使用makedevs语法。可以参考第25章找到此语法的一些文档。

- LIBFOO_PERMISSIONS可选地列出构建过程结束时需要做的权限更改。使用makedevs语法。可以参考第25章找到此语法的一些文档。

- LIBFOO_USERS可选地列出为这个包创建的用户，如果它安装了一个程序需要作为特定用户运行(例如作为守护进程或cron作业)。语法在精神上类似makedevs，描述在第26章。

- LIBFOO_LICENSE定义包的许可证(或许可证)。此名称将出现在make legal-info产生的清单文件中。如果许可证出现在SPDX许可证列表中，请使用SPDX短标识符使清单文件统一。否则，用精确和简洁的方式描述许可证，避免模糊名称如BSD实际上是一组许可证。此变量是可选的。如果未定义，未知将出现在此包的许可证字段中。  
此变量的预期格式必须遵循以下规则:
    - 如果包的不同部分根据不同的许可证发布，请使用逗号分隔许可证(例如LIBFOO_LICENSE=GPL-2.0+，LGPL-2.1+)。如果清楚区分哪个组件根据哪个许可证许可，请在括号中注释许可证(例如LIBFOO_LICENSE=GPL-2.0+(programs)，LGPL-2.1+(libraries))。
    - 如果一些许可证取决于子选项是否启用，请使用逗号将有条件许可证附加(例如:FOO_LICENSE+=，GPL-2.0+(programs));基础设施将内部删除前面的空格。 
    - 如果包是双重许可的，请使用或关键字分隔许可证(例如LIBFOO_LICENSE=AFL-2.1或GPL-2.0+)。

- LIBFOO_LICENSE_FILES是包含包发布许可证的压缩包中的文件列表，空格分隔。make legal-info将所有这些文件复制到legal-info目录。参见第13章了解更多信息。此变量是可选的。如果未定义，将产生警告提示您，未保存将出现在此包的许可文件字段中。

- LIBFOO_ACTUAL_SOURCE_TARBALL仅适用于LIBFOO_SITE/LIBFOO_SOURCE对指向实际不包含源代码而包含二进制代码的归档的包。这是非常少见的情况，仅知道适用于预编译的外部工具链，但理论上也可能适用于其他包。在这种情况下，通常有单独的压缩包包含实际源代码。设置LIBFOO_ACTUAL_SOURCE_TARBALL为实际源代码归档的名称，Buildroot将下载并在运行make legal-info收集相关法律材料时使用它。注意此文件不会在常规构建中下载，也不会通过make source下载。

- LIBFOO_ACTUAL_SOURCE_SITE提供实际源码压缩包的位置。默认值为LIBFOO_SITE，所以如果二进制和源码归档位于同一目录，则无需设置此变量。如果未设置LIBFOO_ACTUAL_SOURCE_T，则没有设置LIBFOO_ACTUAL_SOURCE_SITE的意义。

- LIBFOO_REDISTRIBUTE可以设置为YES(默认)或NO，表示是否允许重新分发包源代码。对非开源包设置为NO:Buildroot将不会保存此包的源代码收集legal-info时。

- LIBFOO_IGNORE_CVES是空格分隔的CVE列表，告诉Buildroot CVE跟踪工具哪些CVE应该忽略此包。通常用于CVE通过包补丁修复，或因某种原因不影响Buildroot包时使用。必须始终用Makefile注释前面添加CVE。
例如:
    ```
    # 0001-fix-cve-2020-12345.patch
    LIBFOO_IGNORE_CVES += CVE-2020-12345
    # only when built with libbaz， which Buildroot doesn't support
    LIBFOO_IGNORE_CVES += CVE-2020-54321
    ```

- LIBFOO_CPE_ID_*变量集允许包定义其CPE标识符。可用变量包括:

- LIBFOO_CPE_ID_PREFIX，指定CPE标识符的前缀，即前三个字段。未定义时默认值为cpe:2.3:a。

- LIBFOO_CPE_ID_VENDOR，指定CPE标识符的供应商部分。未定义时默认值为<pkgname>_project。

- LIBFOO_CPE_ID_PRODUCT，指定CPE标识符的产品部分。未定义时默认值为<pkgname>。

- LIBFOO_CPE_ID_VERSION，指定CPE标识符的版本部分。未定义时默认值为$(LIBFOO_VERSION)。

- LIBFOO_CPE_ID_UPDATE指定CPE标识符的更新部分。未定义时默认值为*。  
如果定义了这些变量中的任何一个，则通用包基础设施将假定包提供有效的CPE信息。在这种情况下，通用包基础设施将定义LIBFOO_CPE_ID。  
对于宿主包，如果未定义其LIBFOO_CPE_ID_*变量，它将继承对应目标包的这些变量值。

定义这些变量的推荐方式是使用以下语法:  
```
LIBFOO_VERSION = 2.32
```

现在，定义应在构建过程不同阶段执行什么的变量:

- LIBFOO_EXTRACT_CMDS列出提取包时需要执行的操作。通常不需要，因为tar包自动由Buildroot处理。但是，如果包使用非标准归档格式(如ZIP或RAR文件)，或者tar包组织方式非标准，此变量允许覆盖包基础设施的默认行为。
- LIBFOO_CONFIGURE_CMDS列出编译前需要执行的配置操作。
- LIBFOO_BUILD_CMDS列出编译时需要执行的操作。
- HOST_LIBFOO_INSTALL_CMDS列出安装宿主包时需要执行的操作。包必须将文件安装到$(HOST_DIR)目录。
- LIBFOO_INSTALL_TARGET_CMDS列出安装目标包到目标目录时需要执行的操作。只需安装运行包所需的文件。
- LIBFOO_INSTALL_STAGING_CMDS列出安装目标包到staging目录时需要执行的操作。所有开发文件都应安装。
- LIBFOO_INSTALL_IMAGES_CMDS列出安装包到镜像目录时需要执行的操作。只能放置不属于TARGET_DIR但必需引导板的二进制镜像。
- LIBFOO_INSTALL_INIT_XXX列出安装init脚本的操作，用于不同的init系统。
- LIBFOO_HELP_CMDS列出打印帮助信息的操作，包含在make help输出中。
- LIBFOO_LINUX_CONFIG_FIXUPS列出构建和使用此包所需的内核配置选项。

推荐定义这些变量的方式是:
```
define LIBFOO_CONFIGURE_CMDS
    action 1
    action 2
    action 3
endef
```

在操作定义中，可以使用以下变量:
- $(LIBFOO_PKGDIR)包含libfoo.mk和Config.in文件所在的目录路径。用于安装打包在Buildroot中的文件，如运行时配置文件、启动画面等。
- $(@D)，包含解压缩包源代码的目录。 
- $(LIBFOO_DL_DIR)包含Buildroot为libfoo下载的所有文件存储的目录路径。
- $(TARGET_CC)、$(TARGET_LD)等获取交叉编译工具
- $(TARGET_CROSS)获取交叉编译工具链前缀
- 当然还有$(HOST_DIR)、$(STAGING_DIR)和$(TARGET_DIR)变量正确安装包。除非使用按包目录支持，否则它们指向全局主机、staging和目标目录;使用按包目录支持时，它们指向当前包的主机、staging和目标目录。从包角度没有区别:它应简单使用HOST_DIR、STAGING_DIR和TARGET_DIR。第8.12节有更多按包目录支持细节。

最后，也可以使用钩子。第18.23节有更多信息。


### 18.7 autotools基包基础设施
#### 18.7.1 autotools包教程
首先，看看如何为基于autotools的包编写.mk文件，以一个例子:
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

第10行告诉Buildroot将包安装到staging目录。位于output/staging/的staging目录是安装所有包(包括开发文件等)的目录。默认情况下，包不会安装到staging目录，因为通常只需要库安装到staging目录:它们的开发文件需要用于编译依赖它们的其他库或应用程序。默认情况下，启用staging安装时，使用make install命令安装包。

第11行告诉Buildroot不将包安装到目标目录。这个目录将成为运行在目标上的根文件系统。对于纯静态库来说，无需将它们安装到目标目录，因为它们在运行时不会使用。默认情况下启用目标安装;几乎不需要设置此变量为NO。默认情况下，使用make install命令安装包。

第12行告诉Buildroot传递自定义配置选项，在配置和构建包前传递给./configure脚本。

第13行声明依赖关系，以便它们在包构建过程开始前构建。

最后，第15行调用autotools-package宏，生成实际允许构建包的Makefile规则。


#### 18.7.2 autotools包基础设施参考
autotools包基础设施的主要宏是autotools-package。它类似于通用包宏。也可以使用主机autotools包宏实现主机和目标包。

就像通用基础设施一样，autotools基础设施通过在调用autotools-package宏之前定义一些变量来工作。
首先，通用基础设施中存在的所有包元数据信息变量也存在于autotools基础设施中:LIBFOO_VERSION、LIBFOO_SOURCE、LIBFOO_PATCH、LIBFOO_SITE、LIBFOO_SUBDIR、LIBFOO_DEPENDENCIES、LIBFOO_INSTALL_STAGING、LIBFOO_INSTALL_TARGET。

autotools基础设施也可以定义一些特定变量。许多变量只在特定情况下有用，所以典型包只会使用其中一些:
- LIBFOO_SUBDIR可以包含包内包含配置脚本的子目录的名称。如果主配置脚本不在tarball提取的树的根目录中，则这很有用。如果未指定HOST_LIBFOO_SUBDIR，则默认为LIBFOO_SUBDIR。
- LIBFOO_CONF_ENV用于指定传递给配置脚本的额外环境变量。默认为空。
- LIBFOO_CONF_OPTS用于指定传递给配置脚本的额外配置选项。默认为空。
- LIBFOO_MAKE用于指定替代的make命令。当在配置中启用并行构建(使用BR2_JLEVEL)但对于给定的包应禁用此功能时，这通常很有用。默认设置为$(MAKE)。如果包不支持并行构建，则应设置为LIBFOO_MAKE=$(MAKE1)。
- LIBFOO_MAKE_ENV用于指定传递给构建步骤中的make的额外环境变量。这些变量在make命令之前传递。默认为空。
- LIBFOO_MAKE_OPTS用于指定传递给构建步骤中的make的额外变量。这些变量在make命令之后传递。默认为空。
- LIBFOO_AUTORECONF指示是否应重新配置包(即是否应通过重新运行autoconf、automake、libtool等重新生成配置脚本和Makefile.in文件)。有效值为YES和NO。默认值为NO。
- LIBFOO_AUTORECONF_ENV用于指定传递给autoreconf程序的额外环境变量。这些变量在autoreconf命令的环境中传递。默认为空。
- LIBFOO_AUTORECONF_OPTS用于指定传递给autoreconf程序的额外选项。仅在LIBFOO_AUTORECONF=YES时有效。默认为空。
- LIBFOO_AUTOPOINT指示是否应自动设置包(即是否需要复制I18N基础设施)。仅在LIBFOO_AUTORECONF=YES时有效。有效值为YES和NO。默认值为NO。
- LIBFOO_LIBTOOL_PATCH指示是否应应用修复libtool交叉编译问题的Buildroot补丁。有效值为YES和NO。默认值为YES
- LIBFOO_INSTALL_STAGING_OPTS包含用于将包安装到staging目录的make选项。默认值为DESTDIR=$(STAGING_DIR) install，对大多数autotools包正确。仍可覆盖。
- LIBFOO_INSTALL_TARGET_OPTS包含用于将包安装到目标目录的make选项。默认值为DESTDIR=$(TARGET_DIR) install。对大多数autotools包正确，但仍可在需要时覆盖。

使用autotools基础设施，已经定义了构建和安装包所需的所有步骤，它们通常可以很好地支持基于autotools的大多数包。但是，在需要时，仍然可以自定义任何特定步骤:
- 添加后操作钩子(提取、修补、配置、构建或安装后)。详见18.23节。 
- 覆盖其中一个步骤。例如，即使使用autotools基础设施，如果包的.mk文件定义了自己的LIBFOO_CONFIGURE_CMDS变量，也会使用它而不是默认的autotools配置步骤。但是，只应在特定情况下使用此方法。一般情况下不要使用。

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

第10行告诉Buildroot将包安装到staging目录。位于output/staging/的staging目录是安装所有包(包括开发文件等)的目录。默认情况下，包不会安装到staging目录，因为通常只需要库安装到staging目录:它们的开发文件需要用于编译依赖它们的其他库或应用程序。默认情况下，启用staging安装时，使用make install命令安装包。

第11行告诉Buildroot不将包安装到目标目录。这个目录将成为运行在目标上的根文件系统。对于纯静态库来说，无需将它们安装到目标目录，因为它们在运行时不会使用。默认情况下启用目标安装;几乎不需要设置此变量为NO。默认情况下，使用make install命令安装包。

第12行告诉Buildroot在配置包时传递自定义选项给CMake。

第13行声明依赖关系，以便它们在包构建过程开始前构建。

最后，第15行调用cmake-package宏，生成实际允许构建包的Makefile规则。

#### 18.8.2 CMake包基础设施参考
CMake包基础设施的主要宏是cmake-package。它类似于通用包宏generic-package。

也可以使用主机CMake包宏host-cmake-package实现主机和目标包的能力。

就像通用基础设施一样，CMake基础设施通过在调用cmake-package宏之前定义一些变量来工作。

首先，通用基础设施中存在的所有包元数据信息变量也存在于CMake基础设施中:
LIBFOO_VERSION、LIBFOO_SOURCE、LIBFOO_PATCH、LIBFOO_SITE、LIBFOO_SUBDIR、LIBFOO_DEPENDENCIES、
LIBFOO_INSTALL_STAGING、LIBFOO_INSTALL_TARGET。

CMake基础设施也可以定义一些特定变量。许多变量只在特定情况下有用，所以典型包只会使用其中一些。
- LIBFOO_SUBDIR可以包含主CMakeLists.txt文件的子目录名称。
- LIBFOO_CONF_ENV指定传递给CMake的额外环境变量。
- LIBFOO_CONF_OPTS指定传递给CMake的额外配置选项。  
cmake-package基础设施会设置一些常用的CMake选项，所以通常无需在包的*.mk文件中设置，除非要覆盖它们。
    - CMAKE_BUILD_TYPE由BR2_ENABLE_RUNTIME_DEBUG驱动;
    - CMAKE_INSTALL_PREFIX; 
    - BUILD_SHARED_LIBS由BR2_STATIC_LIBS驱动;
    - BUILD_DOC、BUILD_DOCS被禁用;
    - BUILD_EXAMPLE、BUILD_EXAMPLES被禁用;
    - BUILD_TEST、BUILD_TESTS、BUILD_TESTING被禁用。
- LIBFOO_SUPPORTS_IN_SOURCE_BUILD=NO应当设置为包无法在源目录内构建但需要单独的构建目录。
- LIBFOO_MAKE用于指定替代的make命令。默认为$(MAKE)。如果不支持并行构建，应设置为LIBFOO_MAKE=$(MAKE1)。
- LIBFOO_MAKE_ENV指定传递给make的额外环境变量。这些变量在make命令之前传递。默认为空。
- LIBFOO_MAKE_OPTS指定传递给make的额外变量。这些变量在make命令之后传递。默认为空。
- LIBFOO_INSTALL_OPTS包含安装到主机目录的make选项。默认为install，对大多数CMake包正确。
- LIBFOO_INSTALL_STAGING_OPTS包含安装到staging目录的make选项。默认为DESTDIR=$(STAGING_DIR) install/fast，对大多数CMake包正确。但都可以覆盖。
- LIBFOO_INSTALL_TARGET_OPTS包含安装到目标目录的make选项。默认为DESTDIR=$(TARGET_DIR) install/fast。对大多数CMake包正确，但仍可在需要时覆盖。

使用CMake基础设施，已经定义了构建和安装包所需的所有步骤，它们通常可以很好地支持基于CMake的大多数包。但是，在需要时，仍然可以自定义任何特定步骤:
- 添加后操作钩子(提取、修补、配置、构建或安装后)。详见18.23节。
- 覆盖其中一个步骤。例如，即使使用CMake基础设施，如果包的.mk文件定义了自己的LIBFOO_CONFIGURE_CMDS变量，也会使用它而不是默认的CMake配置步骤。但是，只应在特定情况下使用此方法。一般情况下不要使用。


### 18.9 Python包基础设施
此基础设施适用于使用标准Python setuptools或pep517机制作为构建系统的Python包，通常通过使用setup.py脚本或pyproject.toml文件识别。
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

第10-11行提供了包的许可详情(第10行是许可证，第11行是包含许可文本的文件)。

第12行告诉Buildroot在配置包时将自定义选项传递给Python setup.py脚本。

第13行声明依赖关系，以便它们在包构建过程开始前构建。

第14行声明了使用的具体Python构建系统。在此例中使用的是Python的distutils构建系统。

支持的四种构建系统有distutils、flit、pep517和setuptools。

最后，第16行调用python-package宏，生成实际允许构建包的Makefile规则。

#### 18.9.2 Python软件包参考
作为政策，仅提供Python模块的软件包在Buildroot中应该全部以python-<something>命名。其他使用Python构建系统但不是Python模块的软件包可以自由选择名称（Buildroot中的现有示例有scons和supervisor）。

Python软件包基础设施的主要宏是python-package。它类似于generic-package宏。

还可以使用host-python-package宏创建Python主机软件包。

与通用基础设施一样，Python基础设施通过在调用python-package或host-python-package宏之前定义一些变量来工作。

在Python基础设施中，所有存在于通用软件包基础设施中的软件包元数据信息变量也存在，如PYTHON_FOO_VERSION、PYTHON_FOO_SOURCE、PYTHON_FOO_PATCH、PYTHON_FOO_SITE、PYTHON_FOO_SUBDIR、PYTHON_FOO_DEPENDENCIES、PYTHON_FOO_LICENSE、PYTHON_FOO_LICENSE_FILES、PYTHON_FOO_INSTALL_STAGING等。

请注意：
- 在软件包的PYTHON_FOO_DEPENDENCIES变量中不需要添加python或host-python，因为这些基本依赖关系会根据需要由Python软件包基础设施自动添加。
- 同样，对于基于setuptools的软件包，不需要将host-setuptools添加到PYTHON_FOO_DEPENDENCIES中，因为Python基础设施会根据需要自动添加。

一个特定于Python基础架构的必选变量是：

- PYTHON_FOO_SETUP_TYPE，用于定义包使用的Python构建系统。支持的四个值分别为distutils、flit、pep517和setuptools。如果您不知道包中使用的是哪个构建系统，请查看包源代码中的setup.py或pyproject.toml文件，并查看其是否从distutils、flit模块或setuptools模块导入内容。如果包使用了一个没有任何build-system要求和一个本地in-tree backend-path的pyproject.toml文件，则应使用pep517。

根据包的需求，还可以选择定义一些特定于Python基础架构的其他变量。其中许多变量只在非常特定的情况下有用，因此典型的包可能只使用其中几个或不使用任何变量。
- PYTHON_FOO_SUBDIR可以包含包中包含主要setup.py或pyproject.toml文件的子目录的名称。
如果主要setup.py或pyproject.toml文件不在tarball提取的树的根目录中，则这很有用。如果未指定HOST_PYTHON_FOO_SUBDIR，则默认为PYTHON_FOO_SUBDIR。
- PYTHON_FOO_ENV，用于指定要传递给Python setup.py脚本（用于distutils/setup-tools包）或support/scripts/pyinstaller.py脚本（用于flit/pep517包）的附加环境变量，用于构建和安装步骤。
请注意，基础架构会自动传递一些标准变量，这些变量在PKG_PYTHON_DISTUTILS_ENV（用于distutils目标包）、HOST_PKG_PYTHON_DISTUTILS_ENV（用于distutils主机包）、PKG_PYTHON_SETUPTOOLS_ENV（用于setuptools目标包）、HOST_PKG_PYTHON_SETUPTOOLS_ENV（用于setuptools主机包）、PKG_PYTHON_PEP517_ENV（用于flit/pep517目标包）和HOST_PKG_PYTHON_PEP517_ENV（用于flit/pep517主机包）中定义。
- PYTHON_FOO_BUILD_OPTS，用于在构建步骤中指定要传递给Python setup.py脚本的附加选项，这通常只对基于distutils/setuptools的包有意义，因为基于flit/pep517的包不会将这些选项传递给setup.py脚本，而是传递给support/scripts/pyinstaller.py脚本。
对于目标distutils包，基础架构已经自动传递了PKG_PYTHON_DISTUTILS_BUILD_OPTS选项。
- PYTHON_FOO_INSTALL_TARGET_OPTS、PYTHON_FOO_INSTALL_STAGING_OPTS、HOST_PYTHON_FOO_INSTALL_OPTS用于在目标安装步骤、暂存安装步骤或主机安装步骤中指定要传递给Python setup.py脚本（用于distutils/setuptools包）或support/scripts/pyinstaller.py脚本（用于flit/pep517包）的附加选项。请注意，基础架构会自动传递一些选项，这些选项在PKG_PYTHON_DISTUTILS_INSTALL_TARGET_OPTS或PKG_PYTHON_DISTUTILS_INSTALL_STAGING_OPTS（用于目标distutils包）、HOST_PKG_PYTHON_DISTUTILS_INSTALL_OPTS（用于主机distutils包）、PKG_PYTHON_SETUPTOOLS_INSTALL_TARGET_OPTS或PKG_PYTHON_SETUPTOOLS_INSTALL_STAGING_OPTS（用于目标setuptools包）、HOST_PKG_PYTHON_SETUPTOOLS_INSTALL_OPTS（用于主机setuptools包）以及PKG_PYTHON_PEP517_INSTALL_TARGET_OPTS或PKG_PYTHON_PEP517_INSTALL_STAGING_OPTS（用于目标flit/pep517包）中定义。

使用Python基础架构，构建和安装包所需的所有步骤已经定义，并且通常适用于大多数基于Python的包。然而，当需要时，仍然可以自定义任何特定步骤的操作：
- 通过添加后操作钩子（在提取、修补、配置、构建或安装之后）。详细信息请参见第18.23节。
- 通过覆盖其中的一个步骤。例如，即使使用Python基础架构，如果包的.mk文件定义了自己的PYTHON_FOO_BUILD_CMDS变量，它将替代默认的Python变量。然而，应该将这种方法限制在非常特定的情况下使用。不要在一般情况下使用它。

#### 18.9.3 从PyPI存储库生成python包
如果您想为其创建Buildroot包的Python包在PyPI上可用，您可以使用位于utils/目录下的scanpypi工具来自动化该过程。

您可以在此处找到现有的PyPI包列表。

scanpypi工具需要在主机上安装Python的setuptools包。

当位于buildroot目录的根目录时，执行以下操作：

    utils/scanpypi foo bar -o package

如果python-foo和python-bar存在于https://pypi.python.org上，这将在package文件夹中生成python-foo和python-bar包。

找到外部python模块菜单，并将您的包插入其中。请记住，菜单内的项目应按字母顺序排列。

请记住，由于生成器无法猜测某些内容（例如对任何python核心模块的依赖，如BR2_PACKAGE_PYTHON_ZLIB），您很可能需要手动检查包中的任何错误。

此外，请注意，许可证和许可证文件是根据猜测生成的，必须进行检查。您还需要手动将包添加到package/Config.in文件中。

如果您的Buildroot包不在官方Buildroot树中，而是在br2-external树中，请使用-o标志，如下所示：

    utils/scanpypi foo bar -o other_package_dir

这将在other_package_directory中生成python-foo和python-bar包，而不是package文件夹。
选项-h将列出可用的选项：

    utils/scanpypi -h


#### 18.9.4 python-package CFFI后端
Python的C Foreign Function Interface（CFFI）提供了一种便捷可靠的方式，通过在C中编写的接口声明来调用编译的C代码。依赖于此后端的Python包可以通过其setup.py文件中的install_requires字段中出现的cffi依赖项来识别。
此类包应该：
- 将python-cffi作为运行时依赖项添加到目标安装已编译的C库封装。通过在包的Config.in文件中添加select BR2_PACKAGE_PYTHON_CFFI来实现。
```
config BR2_PACKAGE_PYTHON_FOO
    bool "python-foo"
    select BR2_PACKAGE_PYTHON_CFFI # runtime
```

- 将host-python-cffi作为构建时依赖项添加，以便交叉编译C封装。通过将host-python-cffi添加到PYTHON_FOO_DEPENDENCIES变量中来实现。
```
################################################################################
## python-foo
#
################################################################################
...

PYTHON_FOO_DEPENDENCIES = host-python-cffi

$(eval $(python-package))
```


### 18.10 基于LuaRocks的包的基础架构
#### 18.10.1 luarocks-package教程
首先，让我们看一下如何为一个基于LuaRocks的包编写一个.mk文件，这里有一个例子：
```
01: ################################################################################
02: #
03: # lua-foo
04: #
05: ################################################################################
06:
07: LUA_FOO_VERSION = 1.0.2-1
08: LUA_FOO_NAME_UPSTREAM = foo
09: LUA_FOO_DEPENDENCIES = bar
10:
11: LUA_FOO_BUILD_OPTS += BAR_INCDIR=$(STAGING_DIR)/usr/include
12: LUA_FOO_BUILD_OPTS += BAR_LIBDIR=$(STAGING_DIR)/usr/lib
13: LUA_FOO_LICENSE = luaFoo license
14: LUA_FOO_LICENSE_FILES = $(LUA_FOO_SUBDIR)/COPYING
15:
16: $(eval $(luarocks-package))
```

在第7行，我们声明了包的版本（与rockspec中的版本相同，它是上游版本和rockspec修订版的连接，用连字符-分隔）。

在第8行，我们声明该包在LuaRocks上叫做“foo”。在Buildroot中，我们给Lua相关的包一个以“lua”开头的名称，因此Buildroot的名称与上游名称不同。LUA_FOO_NAME_UPSTREAM建立了两个名称之间的关联。

在第9行，我们声明了对本地库的依赖关系，以便在我们的包开始构建过程之前先构建它们。

在第11-12行，我们告诉Buildroot在构建包时向LuaRocks传递自定义选项。

在第13-14行，我们指定了包的许可条款。

最后，在第16行，我们调用luarocks-package宏生成所有实际允许构建包的Makefile规则。

大多数这些细节可以从rock和rockspec中获取。因此，这个文件和Config.in文件可以通过在Buildroot目录中运行命令luarocks buildroot foo lua-foo来生成。这个命令运行了一个特定的luarocks Buildroot插件，它将自动生成一个Buildroot包。结果仍然需要手动检查和可能修改。
- 必须手动更新package/Config.in文件以包含生成的Config.in文件。


#### 18.10.2 luarocks-package参考
LuaRocks是一个用于Lua模块的部署和管理系统，支持各种构建类型：builtin、make和cmake。在Buildroot的上下文中，luarocks-package基础架构只支持builtin模式。使用make或cmake构建机制的LuaRocks包应该分别使用Buildroot中的generic-package和cmake-package基础架构进行打包。

LuaRocks包基础架构的主要宏是luarocks-package：与generic-package类似，它通过定义一些变量提供有关包的元数据信息，然后调用luarocks-package来工作。就像通用基础架构一样，LuaRocks基础架构在调用luarocks-package宏之前通过定义一些变量来工作。

首先，所有在通用基础架构中存在的包元数据信息变量也存在于LuaRocks基础架构中：LUA_FOO_VERSION、LUA_FOO_SOURCE、LUA_FOO_SITE、LUA_FOO_DEPENDENCIES、LUA_FOO_LICENSE、LUA_FOO_LICENSE_FILES。

其中两个由LuaRocks基础架构填充（用于下载步骤）。如果您的包不托管在LuaRocks镜像$(BR2_LUAROCKS_MIRROR)上，您可以覆盖它们：
- LUA_FOO_SITE，默认为$(BR2_LUAROCKS_MIRROR)
- LUA_FOO_SOURCE，默认为$(lowercase LUA_FOO_NAME_UPSTREAM)-$(LUA_FOO_VERSION).src.rock

还定义了一些额外的变量，特定于LuaRocks基础架构。在特定情况下，它们可以被覆盖。
- LUA_FOO_NAME_UPSTREAM，默认为lua-foo，即Buildroot包名称
- LUA_FOO_ROCKSPEC，默认为$(lowercase LUA_FOO_NAME_UPSTREAM)-$(LUA_FOO_VERSION).rockspec
- LUA_FOO_SUBDIR，默认为$(LUA_FOO_NAME_UPSTREAM)-$(LUA_FOO_VERSION_WITHOUT_ROCKSPEC_REVISION)
- LUA_FOO_BUILD_OPTS包含luarocks构建调用的额外构建选项。

### 18.11 Perl/CPAN包基础架构
#### 18.11.1 perl-package教程
首先，让我们看一下如何为Perl/CPAN包编写一个.mk文件，这里有一个例子：
```
01: ################################################################################
02: #
03: # perl-foo-bar
04: #
05: ################################################################################
06:
07: PERL_FOO_BAR_VERSION = 0.02
08: PERL_FOO_BAR_SOURCE = Foo-Bar-$(PERL_FOO_BAR_VERSION).tar.gz
09: PERL_FOO_BAR_SITE = $(BR2_CPAN_MIRROR)/authors/id/M/MO/MONGER
10: PERL_FOO_BAR_DEPENDENCIES = perl-strictures
11: PERL_FOO_BAR_LICENSE = Artistic or GPL-1.0+
12: PERL_FOO_BAR_LICENSE_FILES = LICENSE
13: PERL_FOO_BAR_DISTNAME = Foo-Bar
14:
15: $(eval $(perl-package))
```
在第7行，我们声明了包的版本。

在第8和9行，我们声明了tarball的名称和在CPAN服务器上的位置。Buildroot将自动从这个位置下载tarball。

在第10行，我们声明我们的依赖关系，以便在我们的包的构建过程开始之前先构建它们。

在第11和12行，我们提供了关于包的许可细节（第11行是许可证，第12行是包含许可证文本的文件）。

在第13行，我们提供了脚本utils/scancpan所需的分发名称（为了重新生成/升级这些包文件）。
最后，在第15行，我们调用perl-package宏生成所有实际允许构建包的Makefile规则。

大多数这些数据可以从https://metacpan.org/获取。因此，可以通过在Buildroot目录（或br2-external树）中运行脚本utils/scancpan Foo-Bar来生成这个文件和Config.in文件。该脚本为所请求的包创建一个Config.in文件和foo-bar.mk文件，并且还会递归地为CPAN指定的所有依赖项创建。您仍然需要手动编辑结果。特别是，应该检查以下内容。
- 如果Perl模块与由另一个（非Perl）包提供的共享库链接，这个依赖关系不会自动添加。它必须手动添加到PERL_FOO_BAR_DEPENDENCIES中。
- 必须手动更新package/Config.in文件以包含生成的Config.in文件。作为提示，scancpan脚本按字母顺序打印所需的源“…”语句。

#### 18.11.2 perl-package参考
作为一项政策，提供Perl/CPAN模块的包在Buildroot中都应该以perl-<something>的形式命名。

该基础架构处理各种Perl构建系统：ExtUtils-MakeMaker（EUMM）、Module-Build（MB）和Module-Build-Tiny。当一个包提供Makefile.PL和Build.PL时，默认情况下会优先选择Build.PL。

Perl/CPAN包基础架构的主要宏是perl-package。它类似于generic-package宏。

还可以使用host-perl-package宏来处理目标和主机包。

就像通用基础架构一样，Perl/CPAN基础架构在调用perl-package宏之前通过定义一些变量来工作。

首先，所有在通用基础架构中存在的包元数据信息变量也存在于Perl/CPAN基础架构中：PERL_FOO_VERSION、PERL_FOO_SOURCE、PERL_FOO_PATCH、PERL_FOO_SITE、PERL_FOO_SUBDIR、PERL_FOO_DEPENDENCIES、PERL_FOO_INSTALL_TARGET。
请注意，除非定义了PERL_FOO_INSTALL_STAGING_CMDS变量，否则设置PERL_FOO_INSTALL_STAGING为YES没有任何效果。Perl基础架构不定义这些命令，因为Perl模块通常不需要安装到暂存目录。

还可以定义一些特定于Perl/CPAN基础架构的附加变量。其中许多只在特定情况下有用，因此典型的包只会使用其中的几个。
- PERL_FOO_PREFER_INSTALLER/HOST_PERL_FOO_PREFER_INSTALLER，指定首选的安装方法。可能的值是EUMM（基于Makefile.PL使用ExtUtils-MakeMaker进行安装）和MB（基于Build.PL使用Module-Build进行安装）。只有当包提供了这两种安装方法时才会使用这个变量。
- PERL_FOO_CONF_ENV/HOST_PERL_FOO_CONF_ENV，用于指定传递给perl Makefile.PL或perl Build.PL的额外环境变量。默认为空。
- PERL_FOO_CONF_OPTS/HOST_PERL_FOO_CONF_OPTS，用于指定传递给perl Makefile.PL或perl Build.PL的额外配置选项。默认为空。
- PERL_FOO_BUILD_OPTS/HOST_PERL_FOO_BUILD_OPTS，用于指定在构建步骤中传递给make pure_all或perl Build build的额外选项。默认为空。
- PERL_FOO_INSTALL_TARGET_OPTS，用于指定在安装步骤中传递给make pure_install或perl Build install的额外选项。默认为空。
- HOST_PERL_FOO_INSTALL_OPTS，用于指定在安装步骤中传递给make pure_install或perl Build install的额外选项（仅对主机包有效）。默认为空。

### 18.12 虚拟包基础架构
在Buildroot中，虚拟包是由一个或多个提供者提供功能的包。虚拟包管理是一种可扩展的机制，允许用户选择在rootfs中使用的提供者。

例如，OpenGL ES是嵌入式系统上用于2D和3D图形的API。该API的实现在Allwinner Tech Sunxi和Texas Instruments OMAP35xx平台上是不同的。因此，libgles将是一个虚拟包，sunxi-mali-utgard和ti-gfx将是其提供者。

#### 18.12.1 虚拟包教程
在下面的示例中，我们将解释如何添加一个新的虚拟包（something-virtual）和一个提供者（some-provider）。

首先，让我们创建虚拟包。

#### 18.12.2 虚拟包的Config.in文件
虚拟包something-virtual的Config.in文件应包含：
```
01: config BR2_PACKAGE_HAS_SOMETHING_VIRTUAL
02:     bool
03:
04: config BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL
05:     depends on BR2_PACKAGE_HAS_SOMETHING_VIRTUAL
06:     string
```
在这个文件中，我们声明了两个选项，BR2_PACKAGE_HAS_SOMETHING_VIRTUAL和BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL，它们的值将被提供者使用。

#### 18.12.3 虚拟包的.mk文件
虚拟包的.mk文件应该只求值虚拟包宏：
```
01: ################################################################################
02: #
03: # something-virtual
04: #
05: ################################################################################
06:
07: $(eval $(virtual-package))
```
也可以使用host-virtual-package宏来处理目标和主机包。


#### 18.12.4 提供者的Config.in文件
当将一个包添加为提供者时，只需要对Config.in文件进行一些修改。
提供功能something-virtual的包some-provider的Config.in文件应包含：
```
01: config BR2_PACKAGE_SOME_PROVIDER
02:     bool "some-provider"
03:     select BR2_PACKAGE_HAS_SOMETHING_VIRTUAL
04:     help
05:         This is a comment that explains what some-provider is.
06:
07:         http://foosoftware.org/some-provider/
08:
09: if BR2_PACKAGE_SOME_PROVIDER
10: config BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL
11:     default "some-provider"
12: endif
```
在第3行，我们选择BR2_PACKAGE_HAS_SOMETHING_VIRTUAL，在第11行，我们将BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL的值设置为提供者的名称，但仅在选择了该提供者时才设置。

#### 18.12.5 提供者的.mk文件
.mk文件还应声明一个额外的变量SOME_PROVIDER_PROVIDES，其中包含它是某个虚拟包的实现的所有虚拟包的名称：
```
01: SOME_PROVIDER_PROVIDES = something-virtual
```
当然，不要忘记为此包添加适当的构建和运行时依赖关系！

#### 18.12.6 关于依赖于虚拟包的注意事项
当添加一个需要虚拟包提供的某个FEATURE的包时，您必须使用depends on BR2_PACKAGE_HAS_FEATURE，例如：
```
config BR2_PACKAGE_HAS_FEATURE
    bool

config BR2_PACKAGE_FOO
    bool "foo"
    depends on BR2_PACKAGE_HAS_FEATURE
```

#### 18.12.7 关于依赖于特定提供者的注意事项
如果您的包确实需要特定的提供者，那么您将需要使您的包依赖于此提供者；您不能选择一个提供者。
让我们以一个具有两个提供者的FEATURE为例：
```
config BR2_PACKAGE_HAS_FEATURE
    bool

config BR2_PACKAGE_FOO
    bool "foo"
    select BR2_PACKAGE_HAS_FEATURE

config BR2_PACKAGE_BAR
    bool "bar"
    select BR2_PACKAGE_HAS_FEATURE
```

您正在添加一个需要foo提供的FEATURE的包，但不需要bar提供。

如果您使用select BR2_PACKAGE_FOO，那么用户仍然可以在menuconfig中选择BR2_PACKAGE_BAR。这将创建一个配置不一致，即同时启用了两个相同FEATURE的提供者，一个是用户明确设置的，另一个是您的select隐式设置的。

相反，您必须使用depends on BR2_PACKAGE_FOO，这样可以避免任何隐式的配置不一致。


### 18.13 使用kconfig进行配置文件的软件包基础架构
一种处理用户指定配置的流行方式是使用kconfig。它被Linux内核、Busybox和Buildroot本身等软件包使用。.config文件的存在和menuconfig目标是使用kconfig的两个众所周知的特征。

Buildroot为使用kconfig进行配置的软件包提供了基础架构。该基础架构提供了将软件包的menuconfig目标作为foo-menuconfig在Buildroot中公开，并以正确的方式处理配置文件的复制的必要逻辑。

kconfig-package基础架构基于generic-package基础架构。所有在generic-package中支持的变量在kconfig-package中也都可用。更多细节请参见第18.6.2节。

为了在Buildroot软件包中使用kconfig-package基础架构，除了generic-package基础架构所需的变量外，.mk文件中最低限度需要的行是：

    FOO_KCONFIG_FILE = reference-to-source-configuration-file
    $(eval $(kconfig-package))

这段代码创建了以下make目标：
- foo-menuconfig，调用软件包的menuconfig目标
- foo-update-config，将配置文件复制回源配置文件。当设置了片段文件时，无法使用此目标。
- foo-update-defconfig，将配置文件复制回源配置文件。配置文件只列出与默认值不同的选项。当设置了片段文件时，无法使用此目标。
- foo-diff-config，输出当前配置与Buildroot配置中的kconfig软件包定义之间的差异。该输出有助于识别可能需要传播到配置片段中的配置更改，例如。

并确保在正确的时机将源配置文件复制到构建目录中。

有两种指定要使用的配置文件的选项，可以使用FOO_KCONFIG_FILE（如上面的示例）或FOO_KCONFIG_DEFCONFIG。必须提供其中之一，但不能同时使用两者：
- FOO_KCONFIG_FILE指定用于配置软件包的defconfig或full-config文件的路径。
- FOO_KCONFIG_DEFCONFIG指定要调用的defconfig make规则以配置软件包。

除了这些最低限度需要的行外，还可以设置几个可选变量以适应所考虑的软件包的需求：
- FOO_KCONFIG_EDITORS：支持的kconfig编辑器的空格分隔列表，例如menuconfig xconfig。默认为menuconfig。
- FOO_KCONFIG_FRAGMENT_FILES：要合并到主配置文件的配置片段文件的空格分隔列表。通常在希望与上游(def)config文件保持同步并进行一些微小修改时使用片段文件。
- FOO_KCONFIG_OPTS：调用kconfig编辑器时传递的额外选项。这可能需要包括$(FOO_MAKE_OPTS)，例如。默认为空。
- FOO_KCONFIG_FIXUP_CMDS: 一组在复制或运行kconfig编辑器后需要修复配置文件的shell命令。这些命令可能需要确保与Buildroot的其他配置一致的配置，例如。默认为空。
- FOO_KCONFIG_DOTCONFIG: .config文件的路径（包括文件名），相对于软件包源代码树。默认值.config适用于使用从Linux内核继承的标准kconfig基础架构的所有软件包；一些软件包使用kconfig的派生版本，该版本使用不同的位置。
- FOO_KCONFIG_DEPENDENCIES: 需要在解释此软件包的kconfig之前构建的软件包（很可能是主机软件包）的列表。很少使用。默认为空。
- FOO_KCONFIG_SUPPORTS_DEFCONFIG: 软件包的kconfig系统是否支持使用defconfig文件；很少有软件包不支持。默认为YES。


### 18.14 基于rebar的软件包基础架构
#### 18.14.1 rebar-package教程
首先，让我们看看如何为基于rebar的软件包编写一个.mk文件，下面是一个示例：
```
01: ################################################################################
02: #
03: # erlang-foobar
04: #
05: ################################################################################
06:
07: ERLANG_FOOBAR_VERSION = 1.0
08: ERLANG_FOOBAR_SOURCE = erlang-foobar-$(ERLANG_FOOBAR_VERSION).tar.xz
09: ERLANG_FOOBAR_SITE = http://www.foosoftware.org/download
10: ERLANG_FOOBAR_DEPENDENCIES = host-libaaa libbbb
11:
12: $(eval $(rebar-package))
```

在第7行，我们声明了软件包的版本。

在第8行和第9行，我们声明了tarball的名称（建议使用xz压缩的tarball）和tarball在Web上的位置。Buildroot将自动从该位置下载tarball。

在第10行，我们声明了我们的依赖项，以便在我们的软件包的构建过程开始之前先构建它们。
最后，在第12行，我们调用rebar-package宏，该宏生成了实际允许构建软件包的所有Makefile规则。

#### 18.14.2 rebar-package参考
rebar软件包基础架构的主要宏是rebar-package。它类似于generic-package宏。

还可以使用host-rebar-package宏来支持主机软件包。

与generic基础架构类似，rebar基础架构通过在调用rebar-package宏之前定义一些变量来工作。

首先，所有在generic基础架构中存在的软件包元数据信息变量在rebar基础架构中也存在：ERLANG_FOOBAR_VERSION、ERLANG_FOOBAR_SOURCE、ERLANG_FOOBAR_PATCH、ERLANG_FOOBAR_SITE、ERLANG_FOOBAR_SUBDIR、ERLANG_FOOBAR_DEPENDENCIES、ERLANG_FOOBAR_INSTALL_STAGING、ERLANG_FOOBAR_INSTALL_TARGET、ERLANG_FOOBAR_LICENSE和ERLANG_FOOBAR_LICENSE_FILES。

还可以定义一些特定于rebar基础架构的附加变量。其中许多只在非常特定的情况下有用，因此典型的软件包只会使用其中的一部分。
- ERLANG_FOOBAR_USE_AUTOCONF，用于指定在配置步骤中使用autoconf的软件包。当软件包将此变量设置为YES时，将使用autotools基础架构。  
注意：您还可以使用autotools基础架构中的一些变量：ERLANG_FOOBAR_CONF_ENV、ERLANG_FOOBAR_CONF_OPTS、ERLANG_FOOBAR_AUTORECONF、ERLANG_FOOBAR_AUTORECONF_ENV和ERLANG_FOOBAR_AUTORECONF_OPTS。
- ERLANG_FOOBAR_USE_BUNDLED_REBAR，用于指定软件包是否具有一个捆绑版本的rebar，并且应该使用它。有效值为YES或NO（默认值）。  
注意：如果软件包捆绑了一个rebar实用程序，但可以使用Buildroot提供的通用实用程序，只需设置为NO（即不指定此变量）。只有在必须使用此软件包中捆绑的rebar实用程序时才设置。
- ERLANG_FOOBAR_REBAR_ENV，用于指定传递给rebar实用程序的附加环境变量。
- ERLANG_FOOBAR_KEEP_DEPENDENCIES，用于保留rebar.config文件中描述的依赖项。有效值为YES或NO（默认值）。除非将此变量设置为YES，否则rebar基础架构将在post-patch钩子中删除此类依赖项，以确保rebar不会下载或编译它们。

使用rebar基础架构，构建和安装软件包所需的所有步骤已经定义好，并且通常适用于大多数基于rebar的软件包。然而，如果需要，仍然可以自定义特定步骤中的操作：
- 通过添加后操作钩子（在提取、补丁、配置、构建或安装之后）。有关详细信息，请参阅第18.23节。
- 通过重写其中一个步骤。例如，即使使用rebar基础架构，如果软件包的.mk文件定义了自己的ERLANG_FOOBAR_BUILD_CMDS变量，它将被用于替代默认的rebar变量。但是，应该将此方法限制在非常特定的情况下使用。不要在一般情况下使用它。


### 18.15 基于Waf的软件包基础架构
#### 18.15.1 waf-package教程
首先，让我们看看如何为基于Waf的软件包编写一个.mk文件，下面是一个示例：
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
10: LIBFOO_CONF_OPTS = --enable-bar --disable-baz
11: LIBFOO_DEPENDENCIES = bar
12:
13: $(eval $(waf-package))
```
在第7行，我们声明了软件包的版本。

在第8行和第9行，我们声明了tarball的名称（建议使用xz压缩的tarball）和tarball在Web上的位置。Buildroot将自动从该位置下载tarball。

在第10行，我们告诉Buildroot为libfoo启用哪些选项。

在第11行，我们告诉Buildroot libfoo的依赖关系。
最后，在第13行，我们调用waf-package宏，该宏生成了实际允许构建软件包的所有Makefile规则。


#### 18.15.2 waf-package参考
Waf软件包基础架构的主要宏是waf-package。它类似于generic-package宏。

与generic基础架构类似，Waf基础架构通过在调用waf-package宏之前定义一些变量来工作。

首先，所有在generic基础架构中存在的软件包元数据信息变量也存在于Waf基础架构中：
LIBFOO_VERSION、LIBFOO_SOURCE、LIBFOO_PATCH、LIBFOO_SITE、LIBFOO_SUBDIR、LIBFOO_DEPENDENCIES、LIBFOO_INSTALL_STAGING、LIBFOO_INSTALL_TARGET。

还可以定义一个特定于Waf基础架构的附加变量。
- LIBFOO_SUBDIR 可以包含软件包中包含主wscript文件的子目录的名称。如果，例如，主wscript文件不在tarball提取的树的根目录中，这将非常有用。如果未指定 HOST_LIBFOO_SUBDIR，则默认为 LIBFOO_SUBDIR。
- LIBFOO_NEEDS_EXTERNAL_WAF 可以设置为 YES 或 NO，告诉 Buildroot 使用捆绑的 waf 可执行文件。如果设置为 NO（默认值），则 Buildroot 将使用软件包源代码树中提供的 waf 可执行文件；如果设置为 YES，则 Buildroot 将下载、安装 waf 作为主机工具，并使用它构建软件包。
- LIBFOO_WAF_OPTS，用于指定要在软件包构建过程的每个步骤（configure、build和安装）中传递给 waf 脚本的附加选项。默认为空。
- LIBFOO_CONF_OPTS，用于指定要在配置步骤中传递给 waf 脚本的附加选项。默认为空。
- LIBFOO_BUILD_OPTS，用于指定要在构建步骤中传递给 waf 脚本的附加选项。默认为空。
- LIBFOO_INSTALL_STAGING_OPTS，用于指定要在分阶段安装步骤中传递给 waf 脚本的附加选项。默认为空。
- LIBFOO_INSTALL_TARGET_OPTS，用于指定要在目标安装步骤中传递给 waf 脚本的附加选项。默认为空。

18.16 基于Meson的软件包基础架构
18.16.1 meson-package 教程
Meson 是一个旨在既快速又用户友好的开源构建系统。它使用 Ninja 作为辅助工具来执行实际的构建操作。
让我们看看如何为基于 Meson 的软件包编写一个 .mk 文件，以下是一个示例：
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.0
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.gz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-3.0+
11: FOO_LICENSE_FILES = COPYING
12: FOO_INSTALL_STAGING = YES
13:
14: FOO_DEPENDENCIES = host-pkgconf bar
15:
16: ifeq ($(BR2_PACKAGE_BAZ)，y)
17: FOO_CONF_OPTS += -Dbaz=true
18: FOO_DEPENDENCIES += baz
19: else
20: FOO_CONF_OPTS += -Dbaz=false
21: endif
22:
23: $(eval $(meson-package))
```

Makefile 以定义软件包声明的标准变量开始（第7行到第11行）。

在第23行，我们调用 meson-package 宏，该宏生成了实际允许构建软件包的所有 Makefile 规则。

在示例中，host-pkgconf 和 bar 在第14行被声明为 FOO_DEPENDENCIES 的依赖项，因为 foo 的 Meson 构建文件使用 pkg-config 来确定包 bar 的编译标志和库。

请注意，在软件包的 FOO_DEPENDENCIES 变量中不需要添加 host-meson，因为 Meson 软件包基础架构会根据需要自动添加此基本依赖项。

如果选择了 "baz" 软件包，则通过将 -Dbaz=true 添加到 FOO_CONF_OPTS 的第17行来激活 "foo" 中 "baz" 功能的支持，如 "foo" 源代码树中的 meson_options.txt 文件中所指定的。 "baz" 软件包也被添加到 FOO_DEPENDENCIES 中。

请注意，如果未选择软件包，则在第20行明确禁用了对 baz 的支持。

总而言之，要添加一个新的基于 Meson 的软件包，可以直接复制 Makefile 示例，然后编辑以替换所有 FOO 的出现，并更新标准变量的值为新软件包的大写名称。


#### 18.16.2 meson-package 参考资料
Meson 软件包基础架构的主要宏是 meson-package。它与 generic-package 宏类似。

还可以使用 host-meson-package 宏来支持目标和主机软件包。

与 generic 基础架构类似，Meson 基础架构在调用 meson-package 宏之前通过定义一些变量来工作。

首先，所有在 generic 基础架构中存在的软件包元数据信息变量也存在于 Meson 基础架构中：
FOO_VERSION、FOO_SOURCE、FOO_PATCH、FOO_SITE、FOO_SUBDIR、FOO_DEPENDENCIES、FOO_INSTALL_STAGING、FOO_INSTALL_TARGET。

还可以定义一些特定于 Meson 基础架构的附加变量。其中许多仅在特定情况下有用，因此典型的软件包只会使用其中的几个。
- FOO_SUBDIR 可以包含软件包中包含主 meson.build 文件的子目录的名称。如果，例如，主 meson.build 文件不在 tarball 提取的树的根目录中，这将非常有用。如果未指定 HOST_FOO_SUBDIR，则默认为 FOO_SUBDIR。
- FOO_CONF_ENV，用于指定要在配置步骤中传递给 meson 的附加环境变量。默认为空。
- FOO_CONF_OPTS，用于指定要在配置步骤中传递给 meson 的附加选项。默认为空。
- FOO_CFLAGS，用于指定添加到软件包特定的交叉编译.conf 文件 c_args 属性的编译器参数。默认值为 TARGET_CFLAGS。
- FOO_CXXFLAGS，用于指定添加到软件包特定的交叉编译.conf 文件 cpp_args 属性的编译器参数。默认值为 TARGET_CXXFLAGS。
- FOO_LDFLAGS，用于指定添加到软件包特定的交叉编译.conf 文件 c_link_args 和 cpp_link_args 属性的编译器参数。默认值为 TARGET_LDFLAGS。
- FOO_MESON_EXTRA_BINARIES，用于指定要添加到 meson 交叉编译.conf 配置文件的 [binaries] 部分的以空格分隔的程序列表。格式为 program-name=’/path/to/program’，等号周围没有空格，并且程序的路径放在单引号之间。默认为空。请注意，Buildroot 已经为 c、cpp、ar、strip 和 pkgconfig 设置了正确的值。
- FOO_MESON_EXTRA_PROPERTIES，用于指定要添加到 meson 交叉编译.conf 配置文件的 [properties] 部分的以空格分隔的属性列表。格式为 property-name=<value>，等号周围没有空格，并且字符串值要放在单引号之间。默认为空。请注意，Buildroot 已经为 needs_exe_wrapper、c_args、c_link_args、cpp_args、cpp_link_args、sys_root 和 pkg_config_libdir 设置了值。
- FOO_NINJA_ENV，用于指定要传递给 ninja 的附加环境变量，ninja 是 meson 的伴随工具，负责构建操作。默认为空。
- FOO_NINJA_OPTS，用于指定要构建的目标的以空格分隔的列表。默认为空，表示构建默认目标。


### 18.17 基于 Cargo 的软件包基础架构
Cargo 是 Rust 编程语言的包管理器。它允许用户构建用 Rust 编写的程序或库，并下载和管理它们的依赖项，以确保可重复构建。Cargo 软件包被称为 "crates"。
#### 18.17.1 cargo-package 教程
基于 Cargo 的软件包 foo 的 Config.in 文件应包含：
```
01: config BR2_PACKAGE_FOO
02:     bool "foo"
03:     depends on BR2_PACKAGE_HOST_RUSTC_TARGET_ARCH_SUPPORTS
04:     select BR2_PACKAGE_HOST_RUSTC
05:     help
06:         This is a comment that explains what foo is.
07:
08:         http://foosoftware.org/foo/
```
而该软件包的 .mk 文件应包含：
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.0
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.gz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-3.0+
11: FOO_LICENSE_FILES = COPYING
12:
13: $(eval $(cargo-package))
```
Makefile 从定义软件包声明的标准变量开始（第 7 至 11 行）。

如第 13 行所示，它基于 cargo-package 基础架构。这个基础架构会自动调用 Cargo 来构建和安装软件包。

仍然可以定义自定义构建命令或安装命令（例如使用 FOO_BUILD_CMDS 和 FOO_INSTALL_TARGET_CMDS）。然后，这些命令将替换 cargo 基础架构中的命令。

#### 18.17.2 cargo-package 参考资料
Cargo 软件包基础架构的主要宏是 cargo-package，用于目标软件包，host-cargo-package 用于主机软件包。

与 generic 基础架构类似，Cargo 基础架构在调用 cargo-package 或 host-cargo-package 宏之前通过定义一些变量来工作。

首先，所有在 generic 基础架构中存在的软件包元数据信息变量也存在于 Cargo 基础架构中：FOO_VERSION、FOO_SOURCE、FOO_PATCH、FOO_SITE、FOO_DEPENDENCIES、FOO_LICENSE、FOO_LICENSE_FILES 等等。

还可以定义一些特定于 Cargo 基础架构的附加变量。其中许多仅在特定情况下有用，因此典型的软件包只会使用其中的几个。
- FOO_SUBDIR 可以包含软件包中包含 Cargo.toml 文件的子目录的名称。如果，例如，它不在 tarball 提取的树的根目录中，这将非常有用。如果未指定 HOST_FOO_SUBDIR，则默认为 FOO_SUBDIR。
- FOO_CARGO_ENV 可以用于在 cargo 调用的环境中传递额外的变量。它在构建和安装时都会使用。
- FOO_CARGO_BUILD_OPTS 可以用于在构建时向 cargo 传递额外的选项。
- FOO_CARGO_INSTALL_OPTS 可以用于在安装时向 cargo 传递额外的选项。

一个 crate 可能依赖于 crates.io 或 git 存储库中的其他库，这些库在其 Cargo.toml 文件中列出。Buildroot 会自动在使用 cargo-package 基础架构的软件包的下载步骤中下载这些依赖项。这些依赖项与软件包源代码一起保存在 Buildroot 的 DL_DIR 中的 tarball 中，因此软件包的 tarball 的哈希值包括这些依赖项。

这个机制确保任何依赖项的更改都将被检测到，并允许完全离线进行构建。

### 18.18 Go 软件包基础架构
该基础架构适用于使用标准构建系统和捆绑依赖项的 Go 软件包。
#### 18.18.1 golang-package 教程
首先，让我们看看如何为一个 Go 软件包编写一个 .mk 文件，以一个示例为例：
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.0
08: FOO_SITE = $(call github，bar，foo，$(FOO_VERSION))
09: FOO_LICENSE = BSD-3-Clause
10: FOO_LICENSE_FILES = LICENSE
11:
12: $(eval $(golang-package))
```
在第 7 行，我们声明了软件包的版本。

在第 8 行，我们声明了软件包的上游位置，这里是从 Github 获取的，因为许多 Go 软件包托管在 Github 上。

在第 9 和 10 行，我们提供了关于软件包的许可证详细信息。

最后，在第 12 行，我们调用 golang-package 宏，该宏生成实际允许构建软件包的所有 Makefile 规则。

#### 18.18.2 golang-package 参考资料
在使用 golang-package 基础架构的软件包的 Config.in 文件中，应该依赖于 BR2_PACKAGE_HOST_GO_TARGET_ARCH_SUPPORTS，因为 Buildroot 会自动为这些软件包添加对 host-go 的依赖。如果您的软件包需要 CGO 支持，您必须添加对 BR2_PACKAGE_HOST_GO_TARGET_CGO_LINKING_SUPPORTS 的依赖。

Go 软件包基础架构的主要宏是 golang-package，它类似于 generic-package 宏。

还可以构建主机软件包，使用 host-golang-package 宏。由 host-golang-package 宏构建的主机软件包应该依赖于 BR2_PACKAGE_HOST_GO_HOST_ARCH_SUPPORTS。

与 generic 基础架构类似，Go 基础架构在调用 golang-package 之前通过定义一些变量来工作。所有在通用软件包基础架构中存在的软件包元数据信息变量也存在于 Go 基础架构中：FOO_VERSION、FOO_SOURCE、FOO_PATCH、FOO_SITE、FOO_SUBDIR、FOO_DEPENDENCIES、FOO_LICENSE、FOO_LICENSE_FILES、FOO_INSTALL_STAGING 等等。

请注意，在软件包的 FOO_DEPENDENCIES 变量中不需要添加 host-go，因为这个基本依赖项会根据需要自动添加到 Go 软件包基础架构中。

还可以根据软件包的需求选择性地定义一些特定于 Go 基础架构的附加变量。其中许多仅在特定情况下有用，因此典型的软件包只会使用其中的几个，或者根本不使用。

- 软件包必须在 FOO_GOMOD 变量中指定其 Go 模块名称。如果未指定，默认为 URL-域名/URL 的第一部分/URL 的第二部分，例如，对于指定 FOO_SITE = $(call github，bar，foo，$(FOO_VERSION)) 的软件包，FOO_GOMOD 将取值为 github.com/bar/foo。
如果软件包源代码树中不存在 go.mod 文件，Go 软件包基础架构将自动生成一个最小化的 go.mod 文件。
- FOO_LDFLAGS 和 FOO_TAGS 分别用于将 LDFLAGS 或 TAGS 传递给 go build 命令。
- FOO_BUILD_TARGETS 可用于传递应该构建的目标列表。如果未指定 FOO_BUILD_TARGETS，则默认为..我们有两种情况：
    - FOO_BUILD_TARGETS 是.. 在这种情况下，我们假设只会生成一个二进制文件，并且默认情况下将其命名为软件包名称。如果不合适，可以使用 FOO_BIN_NAME 覆盖生成的二进制文件的名称。
    - FOO_BUILD_TARGETS 不是.. 在这种情况下，我们遍历值以构建每个目标，并为每个目标生成一个非目录组件的二进制文件。例如，如果 FOO_BUILD_TARGETS = cmd/docker cmd/dockerd，则生成的二进制文件为 docker 和 dockerd。
- FOO_INSTALL_BINS 可用于传递应该安装在目标的 /usr/bin 中的二进制文件列表。如果未指定 FOO_INSTALL_BINS，则默认为软件包名称的小写形式。

使用 Go 基础架构，构建和安装软件包所需的所有步骤已经定义好，并且通常适用于大多数基于 Go 的软件包。然而，当需要时，仍然可以自定义特定步骤的操作：
- 通过添加后操作钩子（extract、patch、configure、build 或 install 之后）。有关详细信息，请参见第 18.23 节。
- 通过覆盖其中一个步骤。例如，即使使用了 Go 基础架构，如果软件包的 .mk 文件定义了自己的 FOO_BUILD_CMDS 变量，它将替代默认的 Go 变量。但是，使用此方法应限制在非常特定的情况下。不要在一般情况下使用它。

Go 软件包可以依赖于其 go.mod 文件中列出的其他 Go 模块。Buildroot 在使用 golang-package 基础架构的软件包的下载步骤中自动处理此类依赖项的下载。然后，这些依赖项与软件包源代码一起保存在 Buildroot 的 DL_DIR 中的 tarball 中，因此软件包 tarball 的哈希值包括这些依赖项。

这个机制确保任何依赖项的更改都将被检测到，并且允许完全离线执行构建。


### 18.19 QMake-based软件包的基础设施
#### 18.19.1 qmake-package教程
首先，让我们看看如何为基于QMake的软件包编写.mk文件，举个例子:
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
10: LIBFOO_CONF_OPTS = QT_CONFIG+=bar QT_CONFIG-=baz
11: LIBFOO_DEPENDENCIES = bar
12:
13: $(eval $(qmake-package))
```
第7行，我们声明软件包的版本。

第8行和第9行，我们声明tarball文件的名称(推荐xz压缩的tarball文件)和tarball文件在网络上的位置。Buildroot将自动从这个位置下载tarball文件。

第10行，我们告诉Buildroot为libfoo启用什么选项。

第11行，我们告诉Buildroot libfoo的依赖关系。

最后，在第13行，我们调用qmake-package宏，该宏生成所有实际允许软件包构建的Makefile规则。

#### 18.19.2 qmake-package 参考
QMake 软件包基础设施的主要宏是 qmake-package。它类似于通用软件包宏。

就像通用基础设施一样，QMake 基础设施通过在调用 qmake-package 宏之前定义一些变量来工作。

首先，存在于通用基础设施中的所有软件包元数据信息变量也存在于 QMake 基础设施中:
LIBFOO_VERSION、LIBFOO_SOURCE、LIBFOO_PATCH、LIBFOO_SITE、LIBFOO_SUBDIR、LIBFOO_DEPENDENCIES、
LIBFOO_INSTALL_STAGING、LIBFOO_INSTALL_TARGET。

此外，QMake 基础设施还可以定义一个额外变量。
- LIBFOO_CONF_ENV，指定要传递给 qmake 脚本的额外环境变量进行配置步骤。默认为空。
- LIBFOO_CONF_OPTS，指定要传递给 qmake 脚本的额外选项进行配置步骤。默认为空。
- LIBFOO_MAKE_ENV，指定传递给 make 命令的额外环境变量进行构建和安装步骤。默认为空。
- LIBFOO_MAKE_OPTS，指定传递给 make 命令的额外目标进行构建步骤。默认为空。
- LIBFOO_INSTALL_STAGING_OPTS，指定传递给 make 命令的额外目标进行安装阶段安装步骤。默认为 install。
- LIBFOO_INSTALL_TARGET_OPTS，指定传递给 make 命令的额外目标进行目标安装步骤。默认为 install。
- LIBFOO_SYNC_QT_HEADERS，在 qmake 之前运行 syncqt.pl。有些软件包需要这一步才能在构建前拥有正确填充的包含目录。

### 18.20 构建内核模块的软件包基础设施
Buildroot 提供了一个辅助基础设施，可以方便地编写构建和安装 Linux 内核模块的软件包。有些软件包只包含内核模块，其他软件包除内核模块外还包含程序和库。Buildroot 的辅助基础设施同时支持这两种情况。

#### 18.20.1 内核模块教程
我们从一个示例开始，看看如何准备一个只构建内核模块而没有其他组件的简单软件包:
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.2.3
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.xz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-2.0
11: FOO_LICENSE_FILES = COPYING
12:
13: $(eval $(kernel-module))
14: $(eval $(generic-package))
```
7-11 行定义了常见的元数据，指定版本、归档文件名、软件包源代码的远程 URI 地址以及许可信息。

13 行调用内核模块辅助基础设施，生成所有需要的 Makefile 规则和变量来构建该内核模块。 

14 行调用通用软件包基础设施。

自动添加对 linux 的依赖，所以不需要在 FOO_DEPENDENCIES 中指定。

你可能注意到，与其他基础设施不同，我们显式调用了第二个基础设施。这允许软件包构建内核模块，同时如果需要，也可以使用任何一个软件包基础设施构建常规用户空间组件(库、可执行文件等)。仅使用内核模块基础设施是不够的，还必须使用另一个软件包基础设施。
看一个更复杂的示例:
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.2.3
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.xz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-2.0
11: FOO_LICENSE_FILES = COPYING
12:
13: FOO_MODULE_SUBDIRS = driver/base
14: FOO_MODULE_MAKE_OPTS = KVERSION=$(LINUX_VERSION_PROBED)
15:
16: ifeq ($(BR2_PACKAGE_LIBBAR)，y)
17: FOO_DEPENDENCIES += libbar
18: FOO_CONF_OPTS += --enable-bar
19: FOO_MODULE_SUBDIRS += driver/bar
20: else
21: FOO_CONF_OPTS += --disable-bar
22: endif
23:
24: $(eval $(kernel-module))
26: $(eval $(autotools-package))
```
这里我们看到，这是一个基于 autotools 的软件包，同时在子目录 driver/base 和 driver/bar(如果 libbar 启用)构建内核模块，并定义 KVERSION 变量传递给 Linux 构建系统来构建模块。


#### 18.20.2 内核模块参考
内核模块基础设施的主要宏是 kernel-module。与其他软件包基础设施不同，它本身不独立，需要在其后调用任何一个*-package 宏。

kernel-module 宏定义了构建后和目标安装后钩子，用于构建内核模块。如果软件包的.mk 需要访问构建好的内核模块，它应该在注册 kernel-module 后定义的构建后钩子中进行。

同样，如果软件包的.mk 需要访问安装后的内核模块，它应该在注册 kernel-module 后定义的安装后钩子中进行。例如:
```
$(eval $(kernel-module))

define FOO_DO_STUFF_WITH_KERNEL_MODULE
    # Do something with it...
endef
FOO_POST_BUILD_HOOKS += FOO_DO_STUFF_WITH_KERNEL_MODULE

$(eval $(generic-package))
```

与其他软件包基础设施不同，没有 host-kernel-module 变体来构建宿主机内核模块。
可以可选地定义以下额外变量来进一步配置内核模块的构建:
- FOO_MODULE_SUBDIRS 可以设置一个或多个子目录(相对于软件包源代码顶级目录)，内核模块源代码位于其中。如果为空或未设置，则内核模块源代码被视为位于软件包源代码树顶层。
- FOO_MODULE_MAKE_OPTS 可以设置包含传递给 Linux 构建系统的额外变量定义。

您也可以引用(但不可以设置!)以下变量:
- LINUX_DIR 包含 Linux 内核提取和构建后的路径。
- LINUX_VERSION 包含用户配置的版本字符串。 
- LINUX_VERSION_PROBED 包含通过运行 make -C $(LINUX_DIR) kernelrelease 获取的实际内核版本字符串。
- KERNEL_ARCH 包含当前体系结构的名称，如 arm、mips 等。

### 18.21 AsciiDoc文档基础设施
您现在正在阅读的Buildroot手册完全使用AsciiDoc标记语法编写。手册然后会渲染成多种格式:
- html
- split-html 
- pdf
- epub
- text
尽管Buildroot只包含一个使用AsciiDoc编写的文档，但与软件包一样，它提供了一个基础设施来使用AsciiDoc语法渲染文档。

与软件包一样，AsciiDoc基础设施也可以从br2-external树中获取。这允许br2-external树的文档与Buildroot文档匹配，因为它们将使用相同的格式、布局和主题进行渲染。

#### 18.21.1 asciidoc-document教程
与软件包基础设施后缀为-package，文档基础设施后缀为-document。所以AsciiDoc基础设施命名为asciidoc-document。

下面是一个示例来渲染一个简单的AsciiDoc文档:
```
01: ################################################################################
02: #
03: # foo-document
04: #
05: ################################################################################
06:
07: FOO_SOURCES = $(sort $(wildcard $(FOO_DOCDIR)/*))
08: $(eval $(call asciidoc-document))
```
7行，Makefile声明文档源文件在哪里。目前，文档源文件只能是本地的;Buildroot不会尝试下载任何内容来渲染文档。所以您必须指出源文件位置。对于没有子目录结构的文档，上面的字符串就足够了。

8行，我们调用asciidoc-document函数，它生成所有必需的Makefile代码来渲染文档。

#### 18.21.2 asciidoc-document参考
在.mk文件中可以设置的用于提供元数据信息的变量列表(假设文档名称为foo):
- FOO_SOURCES，必需，定义文档源文件。
- FOO_RESOURCES，可选，可以包含一个以空格分隔的路径列表，指向一个或多个包含所谓资源(如CSS或图像)的目录。默认为空。
- FOO_DEPENDENCIES，可选，必须在构建此文档前构建的软件包列表(很可能是宿主软件包)。
- FOO_TOC_DEPTH，FOO_TOC_DEPTH_<FMT>，可选，此文档的目录深度，可以单独为指定格式<FMT>覆盖(参见上面渲染格式的列表，但用大写并用下划线替换连字符;见下例)。默认:1。

还有一些附加钩子(有关钩子的通用信息请参见第18.23节)，文档可以设置以定义在各个步骤执行额外操作:
- FOO_POST_RSYNC_HOOKS 在Buildroot拷贝源文件后运行额外命令。例如可以用来使用从树中提取的信息生成文档的一部分。Buildroot就是用这个钩子生成附录中的表格。
- FOO_CHECK_DEPENDENCIES_HOOKS 检查生成文档所需组件的额外测试。在AsciiDoc中，可以调用过滤器，即将解析AsciiDoc块并适当渲染的程序(如ditaa或aafigure)。
- FOO_CHECK_DEPENDENCIES_<FMT>_HOOKS 为指定格式<FMT>运行额外测试(参见上面渲染格式列表)。

Buildroot设置以下变量可以在上述定义中使用:
- $(FOO_DOCDIR)，类似于$(FOO_PKGDIR)，包含foo.mk的目录路径。可以用来引用文档源，也可以在钩子中使用，尤其是post-rsync钩子，如果文档的一部分需要生成。
- $(@D)，与传统软件包一样，包含文档将被复制和构建的目录路径。
下面是一个完整示例使用所有变量和所有钩子:
```
01: ################################################################################
02: #
03: # foo-document
04: #
05: ################################################################################
06:
07: FOO_SOURCES = $(sort $(wildcard $(FOO_DOCDIR)/*))
08: FOO_RESOURCES = $(sort $(wildcard $(FOO_DOCDIR)/ressources))
09:
10: FOO_TOC_DEPTH = 2
11: FOO_TOC_DEPTH_HTML = 1
12: FOO_TOC_DEPTH_SPLIT_HTML = 3
13:
14: define FOO_GEN_EXTRA_DOC
15:     /path/to/generate-script --outdir=$(@D)
16: endef
17: FOO_POST_RSYNC_HOOKS += FOO_GEN_EXTRA_DOC
18:
19: define FOO_CHECK_MY_PROG
20:     if ! which my-prog >/dev/null 2>&1; then \
21:         echo "You need my-prog to generate the foo document"; \
22:         exit 1; \
23:     fi
24: endef
25: FOO_CHECK_DEPENDENCIES_HOOKS += FOO_CHECK_MY_PROG
26:
27: define FOO_CHECK_MY_OTHER_PROG
28:     if ! which my-other-prog >/dev/null 2>&1; then \
29:         echo "You need my-other-prog to generate the foo document as PDF"; \
30:         exit 1; \
31:     fi
32: endef
33: FOO_CHECK_DEPENDENCIES_PDF_HOOKS += FOO_CHECK_MY_OTHER_PROG
34:
35: $(eval $(call asciidoc-document))
```

### 18.22 针对 Linux 内核软件包的基础设施
Linux 内核软件包可以使用一些基于软件包钩子的特定基础设施来构建 Linux 内核工具或者/和构建 Linux 内核扩展。

#### 18.22.1 linux-kernel-tools
Buildroot 提供了一个辅助基础设施来构建目标机器在 Linux 内核源码中可用的一些用户空间工具。由于它们的源代码是内核源代码的一部分，专门有一个软件包 linux-tools，它重用运行在目标机器上的 Linux 内核的源代码。

看一个 Linux 工具的例子。为新的 Linux 工具 foo 创建一个新的菜单项在现有的 package/linux-tools/Config.in 文件中。

这个文件将包含与每个将使用的内核工具相关的选项描述，并在配置工具中显示。基本如下:
```
01: config BR2_PACKAGE_LINUX_TOOLS_FOO
02:     bool "foo"
03:     select BR2_PACKAGE_LINUX_TOOLS
04:     help
05:         This is a comment that explains what foo kernel tool is.
06:
07:         http://foosoftware.org/foo/
```

工具选项名称以前缀 BR2_PACKAGE_LINUX_TOOLS_ 开头，后跟工具的大写名称(与软件包一样)。

注意，与其他软件包不同，linux-tools 软件包选项出现在内核菜单下的内核工具子菜单中，而不是主目标软件包菜单下。

然后对每个 Linux 工具，添加一个新的 .mk.in 文件，如 package/linux-tools/linux-tool-foo.mk.in。基本如下:
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: LINUX_TOOLS += foo
08:
09: FOO_DEPENDENCIES = libbbb
10:
11: define FOO_BUILD_CMDS
12:     $(TARGET_MAKE_ENV) $(MAKE) -C $(LINUX_DIR)/tools foo
13: endef
14:
15: define FOO_INSTALL_STAGING_CMDS
16:     $(TARGET_MAKE_ENV) $(MAKE) -C $(LINUX_DIR)/tools \
17:         DESTDIR=$(STAGING_DIR) \
18:         foo_install
19: endef
20:
21: define FOO_INSTALL_TARGET_CMDS
22:     $(TARGET_MAKE_ENV) $(MAKE) -C $(LINUX_DIR)/tools \
23:         DESTDIR=$(TARGET_DIR) \
24:         foo_install
25: endef
```

7行注册 foo 到可用 Linux 工具列表。

9行指定此工具依赖的依赖项列表。这些依赖项仅在选择 foo 工具时添加到 Linux 软件包依赖项列表。

11-25 行定义在 Linux 工具构建过程不同步骤所应执行的内容，类似通用软件包。实际仅在选择 foo 工具时使用。仅支持的命令是 _BUILD_CMDS、_INSTALL_STAGING_CMDS 和 _INSTALL_TARGET_CMDS。

注意不要调用 $(eval $(generic-package)) 或任何其他软件包基础设施!Linux 工具本身不是软件包，它们是 linux-tools 软件包的一部分。


#### 18.22.2 linux-kernel-extensions
一些软件包提供了需要修改 Linux 内核树的新功能。这可以是应用于内核树的补丁形式，也可以是添加到树中的新文件形式。Buildroot 的 Linux 内核扩展基础设施提供了一种简单解决方案，自动在提取内核源代码后和应用内核补丁前进行此操作。使用此机制打包的扩展例子包括实时扩展 Xenomai 和 RTAI，以及来自树外的 LCD 驱动程序集 fbtft。

看一个如何添加新的 Linux 扩展 foo 的例子。

首先，创建提供扩展的 foo 软件包:这是一个标准软件包;有关如何创建这样的软件包，请参阅前几章。这个软件包负责下载源代码归档，检查哈希值，定义许可信息并构建任何用户空间工具。

然后创建真正的 Linux 扩展，在现有的 linux/Config.ext.in 文件中创建一个新的菜单项。这个文件包含与每个内核扩展相关的选项描述，将在配置工具中使用和显示。基本如下:
```
01: config BR2_LINUX_KERNEL_EXT_FOO
02:     bool "foo"
03:     help
04:         This is a comment that explains what foo kernel extension is.
05:
06:         http://foosoftware.org/foo/
```

然后对每个 Linux 扩展添加一个新的 .mk 文件 linux/linux-ext-foo.mk。它基本应包含:
```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: LINUX_EXTENSIONS += foo
08:
09: define FOO_PREPARE_KERNEL
10: $(FOO_DIR)/prepare-kernel-tree.sh --linux-dir=$(@D)
11: endef
```

7行将 Linux 扩展 foo 添加到可用扩展列表。

9-11行定义扩展应如何修改 Linux 内核树;这与 Linux 扩展具体相关，可以使用 foo 软件包定义的变量，如 $(FOO_DIR) 或 $(FOO_VERSION) 以及所有 Linux 变量，如 $(LINUX_VERSION) 或 $(LINUX_VERSION_PROBED)、$(KERNEL_ARCH)。查看这些内核变量的定义。


### 18.23 各个构建步骤中可用的钩子
通用基础设施(因此衍生的 autotools 和 cmake 基础设施也是)允许软件包指定钩子。这些定义了额外在现有步骤后执行的操作。对于通用软件包来说，大多数钩子实际上没有太大用处，因为.mk文件已经完全控制每个软件包构建步骤中的操作。

以下钩子点可用:
- LIBFOO_PRE_DOWNLOAD_HOOKS
- LIBFOO_POST_DOWNLOAD_HOOKS 
- LIBFOO_PRE_EXTRACT_HOOKS
- LIBFOO_POST_EXTRACT_HOOKS
- LIBFOO_PRE_RSYNC_HOOKS
- LIBFOO_POST_RSYNC_HOOKS
- LIBFOO_PRE_PATCH_HOOKS
- LIBFOO_POST_PATCH_HOOKS
- LIBFOO_PRE_CONFIGURE_HOOKS
- LIBFOO_POST_CONFIGURE_HOOKS
- LIBFOO_PRE_BUILD_HOOKS
- LIBFOO_POST_BUILD_HOOKS
- LIBFOO_PRE_INSTALL_HOOKS (仅针对宿主软件包)
- LIBFOO_POST_INSTALL_HOOKS (仅针对宿主软件包)  
- LIBFOO_PRE_INSTALL_STAGING_HOOKS (仅针对目标软件包)
- LIBFOO_POST_INSTALL_STAGING_HOOKS (仅针对目标软件包)
- LIBFOO_PRE_INSTALL_TARGET_HOOKS (仅针对目标软件包)
- LIBFOO_POST_INSTALL_TARGET_HOOKS (仅针对目标软件包)
- LIBFOO_PRE_INSTALL_IMAGES_HOOKS
- LIBFOO_POST_INSTALL_IMAGES_HOOKS
- LIBFOO_PRE_LEGAL_INFO_HOOKS
- LIBFOO_POST_LEGAL_INFO_HOOKS  
- LIBFOO_TARGET_FINALIZE_HOOKS
这些变量包含在此钩子点执行的操作的变量名称列表。这允许在给定的钩子点注册多个钩子。例如:
```
define LIBFOO_POST_PATCH_FIXUP
    action1
    action2 
endef

LIBFOO_POST_PATCH_HOOKS += LIBFOO_POST_PATCH_FIXUP
```

#### 18.23.1 使用 POST_RSYNC 钩子
POST_RSYNC 钩子仅针对使用本地源的软件包运行，无论是通过本地站点方法还是 OVERRIDE_SRCDIR 机制。在这种情况下，软件包源通过 rsync 从本地位置复制到 Buildroot 构建目录。但是 rsync 命令不会复制源目录中的所有文件。属于版本控制系统的文件，如 .git、.hg 等目录不会被复制。对于大多数软件包来说这已足够，但给定软件包可以使用 POST_RSYNC 钩子进行其他操作。

原则上，钩子可以包含任何命令。然而，一个具体用例是有意使用 rsync 复制版本控制目录。在钩子中使用的 rsync 命令可以使用以下变量:
- $(SRCDIR):覆盖源目录的路径
- $(@D):构建目录的路径

#### 18.23.2 目标 finalize 钩子 
软件包也可以在 LIBFOO_TARGET_FINALIZE_HOOKS 注册钩子。这些钩子在所有软件包构建完成后但生成文件系统映像前运行。它们使用较少，您的软件包可能不需要它们。

### 18.24 Gettext集成和软件包交互
许多支持国际化的软件包使用gettext库。该库的依赖关系较为复杂，因此需要一些解释。

glibc C库内置了完整的gettext实现，支持翻译。因此，本地语言支持直接集成在glibc中。

另一方面，uClibc和musl C库只提供gettext功能的简单实现，它允许使用gettext函数编译库和程序，但不提供完整gettext实现的翻译能力。使用这些C库时，如果需要真正的本地语言支持，可以由gettext软件包的libintl库提供。

因此，为了确保正确处理本地语言支持，Buildroot中的可以使用NLS支持的软件包应该:
1. 当BR2_SYSTEM_ENABLE_NLS=y时，确保启用NLS支持。这对autotools软件包自动生效，所以其他基础设施的软件包需要单独做。
2. 将$(TARGET_NLS_DEPENDENCIES)添加到软件包<pkg>_DEPENDENCIES变量。这一添加应无条件进行:这个变量的值由核心自动调整为相关软件包列表。如果NLS关闭，这个变量为空;如果开启，包含host-gettext提供编译翻译文件的工具。此外，如果使用uClibc或musl，也包含gettext获取完整实现。 
3. 如果需要，可以将$(TARGET_NLS_LIBS)添加到链接器标志，以便与libintl链接。autotools软件包通常自动检测应与libintl链接。但是其他构建系统或autotools问题软件包可能需要此操作。应无条件添加$(TARGET_NLS_LIBS)，核心会使其为空或定义为-lintl。

不应向Config.in文件添加任何更改支持NLS。

最后，某些软件包需要一些gettext实用程序在目标上，例如gettext本身允许从命令行获取翻译字符串。这种情况下，软件包应:
- 在Config.in中使用select BR2_PACKAGE_GETTEXT，注释表示仅为运行时依赖。
- 不在.mk文件中的DEPENDENCIES变量添加任何gettext依赖。

### 18.25 招数和技巧
#### 18.25.1 软件包名称、配置入口名称和Makefile变量关系
在Buildroot中，软件包名称、配置入口名称和Makefile变量前缀之间存在一些关系:
- 软件包名称就是软件包目录名称(和*.mk文件名);
- 配置入口名称在Config.in文件中声明; 
- Makefile变量前缀。

必须保持这些元素之间的一致性，遵循以下规则:
- 软件包目录和*.mk名称就是软件包名称本身(如:package/foo-bar_boo/foo-bar_boo.mk);
- Make目标名称就是软件包名称(如:foo-bar_boo);
- 配置入口是大写软件包名称，用_替换.和-，前缀为BR2_PACKAGE_(如:BR2_PACKAGE_FOO_BAR_BOO);
- *.mk文件变量前缀是大写软件包名称，用_替换.和-(如:FOO_BAR_BOO_VERSION)
这保持了软件包名称、配置和Makefile变量之间的一致性。

#### 18.25.2 如何检查代码风格
Buildroot提供了一个utils/check-package脚本，用于检查新创建或修改的文件是否符合代码风格。它不是完整的语言验证器，但可以检测许多常见错误。它用于检查您实际创建或修改的文件，然后再为提交创建补丁。

这个脚本可以用于软件包、文件系统Makefile、Config.in文件等。它不检查定义软件包基础设施和一些其他共享代码的文件。

使用方法是:

    $ ./utils/check-package package/new-package/* 

或者:

    $ cd package/new-package/ 
    $ check-package *

也可以用于br2-external中的软件包:

    $ check-package -b /path/to/br2-ext-tree/package/my-package/*


#### 18.25.3 如何测试您的软件包
一旦您添加了新的软件包，测试它在各种条件下运行很重要:它是否能在所有体系结构上构建?它是否能与不同的 C 库一起构建?它是否需要线程，NPTL吗?等等。

Buildroot 运行自动构建器，它们会持续测试随机配置。但是，这些只会构建 git 树的主分支，您新的高端软件包还没有加入。 

Buildroot 提供了一个 util/test-pkg 脚本，它使用自动构建器所使用的相同基础配置，这样您就可以在相同条件下测试您的软件包。

首先，创建一个配置片段，包含启用您软件包所需的所有选项，但不包含任何体系结构或工具链选项。例如，我们可以创建一个仅启用 libcurl 的配置片段，而不使用任何 TLS 后端:

    $ cat libcurl.config
    BR2_PACKAGE_LIBCURL=y

如果您的软件包需要更多配置选项，您可以将它们添加到配置片段中。例如，下面是如何测试使用 OpenSSL 作为 TLS 后端并包含 curl 程序的 libcurl:
```
$ cat libcurl.config
BR2_PACKAGE_LIBCURL=y
BR2_PACKAGE_LIBCURL_CURL=y
BR2_PACKAGE_OPENSSL=y
```

然后运行测试脚本，告诉它使用哪个配置片段并测试哪个软件包:
```
$ ./utils/test-pkg -c libcurl.config -p libcurl
```

默认情况下，test-pkg 将您的软件包与自动构建器使用的一些工具链进行构建，这些工具链由 Buildroot 开发人员选择为最有用和代表性的子集。如果您想测试所有工具链，请传入 -a 选项。请注意，在任何情况下，内部工具链都将被排除，因为它们构建时间过长。
输出会列出测试的所有工具链及相应结果(摘录，结果仅为虚构):
```
$ ./utils/test-pkg -c libcurl.config -p libcurl
      armv5-ctng-linux-gnueabi [ 1/11]: OK
    armv7-ctng-linux-gnueabihf [ 2/11]: OK
              br-aarch64-glibc [ 3/11]: SKIPPED
                 br-arcle-hs38 [ 4/11]: SKIPPED
                  br-arm-basic [ 5/11]: FAILED
        br-arm-cortex-a9-glibc [ 6/11]: OK
         br-arm-cortex-a9-musl [ 7/11]: FAILED
         br-arm-cortex-m4-full [ 8/11]: OK
                   br-arm-full [ 9/11]: OK
          br-arm-full-nothread [10/11]: FAILED
            br-arm-full-static [11/11]: OK
11 builds， 2 skipped， 2 build failed， 1 legal-info failed
```
意思是:
- OK:构建成功。 
- SKIPPED:配置片段中列出的一个或多个配置选项没有出现在最终配置中。这是由于选项具有不满足工具链依赖关系，例如依赖于BR2_USE_MMU但使用无MMU工具链的软件包。遗漏的选项将在输出构建目录(默认为~/br-test-pkg/TOOLCHAIN_NAME/)中的missing.config报告。
- FAILED:构建失败。检查输出构建目录中的logfile文件以查看什么出错了:
    - 实际构建失败
    - legal-info失败 
    - 预备步骤(下载配置文件、应用配置、为软件包运行dirclean)中的一个失败

当出现失败时，您可以使用相同的选项重新运行脚本(在您修复软件包后);脚本将尝试为使用-p指定的软件包重新构建所有工具链，而无需重新构建该软件包的所有依赖项。

test-pkg脚本接受一些选项，您可以通过运行以下内容获取一些帮助:
```
$ ./utils/test-pkg -h
```

#### 18.25.4 如何从GitHub添加软件包
GitHub上的软件包通常没有下载区域包含发布的tar包。但是，可以直接从GitHub仓库下载tar包。由于GitHub过去曾更改下载机制，应使用github助手函数，如下所示:
```
# Use a tag or a full commit ID
FOO_VERSION = 1.0
FOO_SITE = $(call github，<user>，<package>，v$(FOO_VERSION))
```

注意:
- FOO_VERSION可以是标签或提交ID。
- github生成的tarball名称与Buildroot的默认名称匹配(例如:foo-f6fb6654af62045239caed5950bc6c7971965e60.tar.gz)，所以在.mk文件中不需要指定它。
- 使用提交ID作为版本时，应使用完整的40个16进制字符。
- 当标签包含前缀如v时，比如v1.0，那么VERSION变量应只包含1.0，v应直接添加到SITE变量中，如上所示。这可以确保VERSION变量值可以匹配release-monitoring.org结果。

如果您要添加的软件包实际上在GitHub上有发布部分，维护者可能已上传发布的tar包，或者发布可能只指向从git标签自动生成的tar包。如果维护者上传了发布的tar包，我们更倾向于使用它，因为它可能略有不同(例如它包含一个配置脚本，所以我们不需要做AUTORECONF)。

您可以在发布页面看到是否是上传的tar包还是git标签:

                                    github_hash_mongrel2.png

- 如果看起来像上图那样，那么它是由维护者上传的，您应使用该链接(在该例子中:mongrel2-v1.9.2.tar.bz2)指定FOO_SITE，不应使用github助手。
- 另一方面，如果只有"源代码"链接，那么它是一个自动生成的tar包，您应使用github助手函数。


#### 18.25.5 如何从Gitlab添加软件包
与第18.25.4节中描述的github宏相似，Buildroot也提供gitlab宏从Gitlab仓库下载。它可以用于下载Gitlab自动生成的tarball，可以是特定标签或提交:
```
# Use a tag or a full commit ID
FOO_VERSION = 1.0
FOO_SITE = $(call gitlab，<user>，<package>，v$(FOO_VERSION))
```

默认情况下，它将使用.tar.gz tarball，但Gitlab也提供.tar.bz2 tarball，所以通过添加<pkg>_SOURCE变量，可以使用这个.tar.bz2 tarball:
```
# Use a tag or a full commit ID
FOO_VERSION = 1.0
FOO_SITE = $(call gitlab，<user>，<package>，v$(FOO_VERSION))
FOO_SOURCE = foo-$(FOO_VERSION).tar.bz2
```

如果上游开发者在https://gitlab.com/<project>/releases/上传了特定的tarball，不要使用这个宏，而应直接使用tarball链接。


### 18.26 结论
如您所见，向Buildroot添加软件包只需要编写一个使用现有示例的Makefile，并根据软件包的编译过程进行修改。

如果您打包的软件可能对其他人有用，不要忘记将补丁发送到Buildroot邮件列表(见第22.5节)!


## Chapter 19、打补丁软件包
在集成新的软件包或更新现有软件包时，可能需要对软件源代码进行修补，以便在Buildroot中进行交叉编译。

Buildroot提供了一套自动化机制来在构建过程中处理这些修补。它支持三种应用补丁集的方式:下载补丁、Buildroot内置的补丁以及用户定义的全局补丁目录。

### 19.1 提供补丁
#### 19.1.1 下载的补丁
如果需要应用可以下载的补丁，则需要将它添加到<软件包名>_PATCH变量中。如果条目包含“://”，Buildroot将假设它是一个完整的URL，并从这个位置下载补丁。否则，Buildroot将假设补丁应该从<软件包名>_SITE下载。它可以是一个单独的补丁，也可以是一个包含补丁系列的tar包。 

与所有下载一样，应该添加哈希值到<软件包名>.hash文件中。

这种方法通常用于来自Debian的软件包。

#### 19.1.2 Buildroot内置的补丁
大多数补丁提供在Buildroot内，位于软件包目录中;这些补丁通常用于解决交叉编译、libc支持或其他问题。

这些补丁文件应命名为<序号>-<描述>.patch。

注意:
- Buildroot内置的补丁文件名不应包含任何软件包版本信息。
- 补丁文件名中的<序号>字段表示应用顺序，从1开始;建议用零填充到4位宽，如git format-patch所做。例如:0001-foobar-the-buz.patch 
- 补丁邮件主题前缀不应编号。应使用git format-patch -N命令生成补丁，它会自动添加编号用于系列。例如，补丁主题行应为Subject: [PATCH] foobar the buz，而不是Subject: [PATCH n/m] foobar the buz。
- 以前，补丁文件名必须以软件包名前缀，如<软件包名>-<序号>-<描述>.patch，但现在不再需要。现有软件包将随时间修正。不要在补丁文件名前添加软件包名前缀。
- 以前可以添加quilt系列文件，但现在不再推荐，将来会删除。不要使用系列文件。

#### 19.1.3 全局补丁目录
可以使用BR2_GLOBAL_PATCH_DIR配置选项指定一个以空格分隔的一个或多个包含全局软件包补丁的目录列表。详见第9.8节。


### 19.2 补丁应用顺序
1. 如果定义了<软件包名>_PRE_PATCH_HOOKS，则运行它;
2. 清理构建目录，删除任何存在的*.rej文件; 
3. 如果定义了<软件包名>_PATCH，则应用来自这些tar包的补丁;
4. 如果软件包Buildroot目录或名为<软件包版本>的子目录中存在*.patch文件，则:
   - 如果软件包目录中存在系列文件，则根据系列文件应用补丁;
   - 否则，按字母顺序应用匹配*.patch的补丁文件。因此，为确保正确顺序，强烈建议按如下命名补丁文件:<序号>-<描述>.patch，其中<序号>表示应用顺序。
5. 如果定义了BR2_GLOBAL_PATCH_DIR，则按指定顺序枚举目录。按前一步描述应用补丁。
6. 如果定义了<软件包名>_POST_PATCH_HOOKS，则运行它。

如果第3或4步出错，则构建失败。


### 19.3 软件包补丁的格式和许可
补丁根据被应用软件的许可协议发布(见第13.2节)。

应在补丁头注释中添加解释该补丁功能和需要的原因。

应在每个补丁头添加Signed-off-by声明，以跟踪更改并证明补丁根据修改软件的同一许可协议发布。
如果软件受版本控制，建议使用上游SCM软件生成补丁集。否则，可以将头注释与diff -purN package-version.orig/ package-version/命令输出连接起来。

如果更新现有补丁(例如升级软件包版本)，请确保保留现有的From头和Signed-off-by标签，但在适当时更新补丁注释的其他内容。

最后，补丁应如下:
```
configure.ac: add C++ support test
Signed-off-by: John Doe <john.doe@noname.org>
--- configure.ac.orig
+++ configure.ac
@@ -40，2 +40，12 @@

AC_PROG_MAKE_SET
+
+AC_CACHE_CHECK([whether the C++ compiler works]，
+   [rw_cv_prog_cxx_works]，
+   [AC_LANG_PUSH([C++])
+   AC_LINK_IFELSE([AC_LANG_PROGRAM([]， [])]，
+       [rw_cv_prog_cxx_works=yes]，
+       [rw_cv_prog_cxx_works=no])
+   AC_LANG_POP([C++])])
+
+AM_CONDITIONAL([CXX_WORKS]， [test "x$rw_cv_prog_cxx_works" = "xyes"])
```

### 19.4 额外的补丁文档
理想情况下，所有补丁在适用时都应通过Upstream trailer记录对应的上游补丁或补丁提交。

当回溯上游已被主线接受的补丁时，最好参考URL到上游提交:

    Upstream: <URL to upstream commit> 

如果在Buildroot中识别到一个新的问题，而这个问题通常也影响上游(不是Buildroot特有的问题)，则应向上游提交补丁，并在可能时提供提交到上游邮件列表或合并请求的链接:

    Upstream: <URL to upstream mailing list submission or merge request>

已提交但被上游拒绝的补丁应注明这一点，并说明为什么尽管上游状态如此，该补丁仍在使用。

注意:在上述任何场景下，添加对补丁可能需要的任何更改的简要说明也是明智的。
如果补丁不适用于上游，则应注明并提供额外信息说明该补丁是Buildroot特有的: 

    Upstream: N/A <additional information about why patch is Buildroot specific>

添加此文档有助于在软件包版本更新过程中优化补丁审查。


## Chapter 20、下载基础框架
直接下载


## Chapter 21、 调试Buildroot
可以对Buildroot在构建软件包时执行的步骤进行仪表化。定义BR2_INSTRUMENTATION_SCRIPTS变量包含一个或多个脚本(或其他可执行文件)的路径，以空格分隔列表，这些脚本将在每个步骤前后调用。脚本按顺序调用，带有三个参数:
- "start" 或 "end" 来标记步骤的开始(或结束);
- 即将开始或刚结束的步骤名称;
- 软件包名称。

例如:

    make BR2_INSTRUMENTATION_SCRIPTS="/path/to/my/script1 /path/to/my/script2"

步骤列表为:
- extract
- patch 
- configure
- build
- install-host，当一个宿主软件包安装在$(HOST_DIR)中
- install-target，当一个目标软件包安装在$(TARGET_DIR)中
- install-staging，当一个目标软件包安装在$(STAGING_DIR)中  
- install-image，当一个目标软件包在$(BINARIES_DIR)安装文件

脚本可以访问以下变量:
- BR2_CONFIG: Buildroot .config文件的路径
- HOST_DIR，STAGING_DIR，TARGET_DIR: 见第18.6.2节
- BUILD_DIR: 软件包提取和构建的目录
- BINARIES_DIR: 所有二进制文件(即映像)的存储位置
- BASE_DIR: 基础输出目录


## Chapter 22、 贡献Buildroot
有很多方式可以贡献Buildroot:分析和修复bug、分析和修复自动构建机器检测到的软件包构建失败、测试和审查其他开发者发送的补丁、工作在我们的TODO列表项上并发送对Buildroot或其手册的改进。以下部分给出了每个项目的一些细节。

如果您有兴趣贡献Buildroot，首先要做的是订阅Buildroot邮件列表。这个列表是与其他Buildroot开发者交互和发送贡献的主要方式。如果您还没有订阅，请参考第5章获取订阅链接。

如果您要修改代码，强烈建议使用Buildroot Git仓库，而不是从压缩源代码tarball开始。Git是最简单的开发和直接将补丁发送到邮件列表的方式。请参考第3章了解如何获取Buildroot Git树。

### 22.1 重现、分析和修复bug
贡献的第一种方式是查看Buildroot bug跟踪器中的开放bug报告。我们致力于保持bug数量尽可能小，所以所有帮助重现、分析和修复报告的bug都非常欢迎。即使您还没有完全看清情况，也不要犹豫在bug报告中添加注释报告您的发现。

### 22.2 分析和修复自动构建失败 
Buildroot自动构建机器是一个持续运行Buildroot构建的机器集，基于随机配置。它对Buildroot支持的所有体系结构、各种工具链和随机选择的软件包进行构建。由于Buildroot的大量提交活动，这些自动构建机器可以非常早地检测到问题。

所有构建结果都在http://autobuild.buildroot.org可见，统计数据在http://autobuild.buildroot.org/stats.php。每天都会向邮件列表发送一封概述所有失败软件包的邮件。

检测问题很重要，但显然这些问题也必须修复。您的贡献在这里将非常受欢迎!

主要有两件事可以做:
- 分析问题。每日概述邮件不包含实际失败的详细信息:为了看清情况，必须打开构建日志并检查最后输出。有人为邮件中所有软件包做这一操作将对其他开发者非常有用，他们可以仅基于此输出进行初步分析。
- 修复问题。当修复自动构建失败时，应遵循以下步骤:
    1. 检查是否可以通过使用相同配置进行构建来重现问题。您可以手动进行，或使用br-reproduce-build脚本，它将自动克隆Buildroot Git仓库，检出正确版本，下载和设置正确的配置，然后启动构建。
    2. 分析问题并创建修复。
    3. 通过从清洁的Buildroot树开始，仅应用您的修复来验证问题真正得到解决。 
    4. 将修复发送到Buildroot邮件列表(见第22.5节)。如果您对软件包源代码创建了补丁，也应将补丁提交给上游，以便在后续版本中修复问题，并在Buildroot中删除该补丁。在修复自动构建失败的补丁提交消息中，请添加对构建结果目录的引用，如下:  
    Fixes autobuild failure in http://autobuild.buildroot.org/results/pkg-x.y-20180201-123456

### 22.3 审查和测试补丁
随着每天邮件列表上发送的补丁数量，维护者判断哪些补丁已经准备好应用，哪些还不行的工作非常艰巨。贡献者在这里可以很大程度上提供帮助，通过审查和测试这些补丁。

在审查过程中，不要犹豫地对补丁提交提供意见，建议或任何有助于每个人理解补丁并使其更好的内容进行回复。请使用纯文本电子邮件回复补丁提交时采用互联网风格回复。

要表示对补丁的批准，有三个正式标签可以跟踪这一批准。要将你的标签添加到补丁中，请在原作者的“Signed-off-by”行下方回复补丁时添加批准标签。这些标签将被补丁工作自动检测到(见第22.3.1节)，并将成为接受补丁时的提交日志的一部分。

**测试通过**  
表示该补丁已经成功测试。您被鼓励指定您进行了哪种测试（在X和Y架构上进行编译测试，对目标A进行运行时测试等）。这些额外的信息有助于其他测试人员和维护者。

**代码审查通过**  
表示您对该补丁进行了代码审查，并尽力发现问题，但您对所涉及的领域不够熟悉，无法提供“Acked-by”标签。这意味着该补丁可能存在未解决的问题，这些问题可能会被在该领域更有经验的人员发现。如果发现了这样的问题，您的“Reviewed-by”标签仍然适用，您不能被责怪。

**确认通过**  
表示您对该补丁进行了代码审查，并对所涉及的领域足够熟悉，认为该补丁可以按原样提交（不需要进行其他更改）。如果后来发现该补丁有问题，您的“Acked-by”可能被认为是不恰当的。因此，“Acked-by”和“Reviewed-by”的区别主要在于您愿意为“Acked”补丁承担责任，而不愿意为“Reviewed”补丁承担责任。

如果您对一个补丁进行了审查并对其有评论，您应该简单地回复该补丁并陈述这些评论，而不提供“Reviewed-by”或“Acked-by”标签。只有当您认为补丁本身很好时，才应提供这些标签。

重要的是要注意，“Reviewed-by”和“Acked-by”都不意味着已经进行了测试。要表示您对补丁进行了审查和测试，请提供两个单独的标签（Reviewed/Acked-by和Tested-by）。

还请注意，任何开发人员都可以提供Tested/Reviewed/Acked-by标签，没有例外，并且我们鼓励每个人都这样做。Buildroot没有定义核心开发人员的团队，只是一些开发人员比其他人更活跃。维护者将根据提交者的记录来评估标签的价值。由经常贡献的开发者提供的标签比新手提供的标签更可信。随着您更频繁地提供标签，您的可信度（在维护者眼中）将提高，但任何提供的标签都是有价值的。

Buildroot的Patchwork网站可以用于拉取补丁进行测试。有关使用Buildroot的Patchwork网站应用补丁的更多信息，请参阅第22.3.1节。

#### 22.3.1 从Patchwork应用补丁
对于开发人员来说，Buildroot的Patchwork网站的主要用途是将补丁拉入他们的本地git存储库进行测试。
在Patchwork管理界面浏览补丁时，页面顶部提供了一个mbox链接。复制此链接地址并运行以下命令：

    $ git checkout -b <测试分支名称>
    $ wget -O - <mbox链接> | git am

应用补丁的另一种选项是创建一个bundle。一个bundle是一组可以使用patchwork界面进行分组的补丁。一旦创建了bundle并且bundle被公开，您可以复制bundle的mbox链接，并使用上述命令应用bundle。


### 22.4 从待办事项列表中处理项目
如果您想为Buildroot做贡献但不知道从哪里开始，而且您不喜欢上述任何主题，您始终可以从Buildroot的待办事项列表中处理项目。请不要犹豫，先在邮件列表或IRC上讨论该项目。在开始处理项目时，请编辑维基以指示，以避免重复努力。

### 22.5 提交补丁
-----------
注意：请不要给bug附加补丁，而是将它们发送到邮件列表中。

-----------
如果您对Buildroot进行了一些更改，并希望将它们贡献给Buildroot项目，请按照以下步骤进行。

#### 22.5.1 补丁的格式
我们希望补丁按特定的方式进行格式化。这对于审查补丁、轻松地将其应用到git存储库、轻松地找到历史记录中的变更方式和原因，并能够使用git bisect定位问题的起源都是必要的。

首先，补丁必须有一个良好的提交消息。提交消息应该以一个单独的行开始，其中包含由补丁所触及的领域作为前缀的变更的简要摘要。以下是一些良好提交标题的示例：
- package/linuxptp: 升级版本到2.0
- configs/imx23evk: 升级Linux版本到4.19
- package/pkg-generic: 推迟对依赖条件的评估
- boot/uboot: 需要host-{flex，bison}
- support/testing: 添加python-ubjson测试

前缀之后的描述应以小写字母开头（即上述示例中的“升级”，“需要”，“推迟”，“添加”）。

其次，提交消息的正文应描述为什么需要这个变更，如果需要，还应提供关于如何进行该变更的详细信息。在编写提交消息时，请考虑审查人员将如何阅读，同时也要考虑到您在数年后再次查看这个变更时将如何阅读。

其三，补丁本身应该只做一个完整的变更。通常，两个无关或弱关联的变更应该分别在两个单独的补丁中进行。这通常意味着一个补丁只影响一个单独的软件包。如果有几个变更是相关的，通常仍然可以将它们拆分为小的补丁，并按照特定的顺序应用它们。小的补丁使得审查更容易，并且通常在之后更容易理解为什么进行了某个变更。然而，每个补丁必须是完整的。当仅应用第一个补丁而不是第二个补丁时，构建不能出现错误。这对于之后使用git bisect是必要的。

当然，在开发过程中，您可能会在不同的软件包之间来回切换，并且肯定不会立即以足够干净的方式提交代码以供提交。因此，大多数开发人员会重写提交历史，以生成适合提交的干净的提交集。为此，您需要使用交互式变基（interactive rebasing）。您可以在《Pro Git》书中了解相关内容。有时，甚至可以使用git reset --soft origin/master丢弃您的历史，并使用git add -i或git add -p选择单个变更。

最后，补丁应该被签名确认。这可以通过在提交消息的末尾添加Signed-off-by: Your Real Name <your@email.address>来完成。如果正确配置了，git commit -s会为您自动添加签名确认。Signed-off-by标签表示您以Buildroot许可证（例如GPL-2.0+，除了软件包补丁，其具有上游许可证）发布该补丁，并且您被允许这样做。有关详细信息，请参阅开发者证书原则（Developer Certificate of Origin）。

为了给赞助创建补丁或将其上游化的人员致谢，您可以使用电子邮件子地址作为您的git身份（即用作提交作者和电子邮件From：字段以及您的Signed-off-by标签的内容）；在本地部分添加后缀，使用加号+分隔。例如：
- 对于赞助提交工作的公司，使用公司名称作为详细（后缀）部分：
Your-Name Your-Surname <your-name.your-surname+companyname@mail.com>
- 对于赞助提交工作的个人，使用他们的名字和姓氏：
Your-Name Your-Surname <your-name.your-surname+their-name.their-surname@mail.com>

在添加新软件包时，您应该将每个软件包单独提交为一个补丁。此补丁应包括package/Config.in的更新，软件包的Config.in文件，.mk文件，.hash文件，任何初始化脚本以及所有软件包补丁。如果软件包有许多子选项，有时最好将它们作为单独的后续补丁添加。摘要行应该类似于<软件包名称>：新软件包。提交消息的正文对于简单的软件包可以为空，或者可以包含软件包的描述（例如Config.in帮助文本）。如果构建软件包需要进行特殊操作，这也应在提交消息正文中明确说明。

当您将软件包升级到新版本时，您还应为每个软件包提交一个单独的补丁。不要忘记更新.hash文件，如果尚不存在，则添加它。还要检查_LICENSE和_LICENSE_FILES是否仍然有效。摘要行应该类似于<软件包名称>：升级到版本<新版本>。如果新版本与现有版本相比仅包含安全更新，则摘要应为<软件包名称>：安全升级到版本<新版本>，提交消息正文应显示修复的CVE编号。如果新版本中的某些软件包补丁可以删除，应明确说明为什么可以删除，最好附带上游提交ID。还应明确说明任何其他所需更改，例如不再存在或不再需要的配置选项。

如果您希望在构建失败和您添加或修改的软件包中出现进一步更改时收到通知，请将自己添加到DEVELOPERS文件中。这应在创建或修改软件包的同一个补丁中完成。有关更多信息，请参阅DEVELOPERS文件。

Buildroot提供了一个方便的工具来检查您创建或修改的文件中的常见代码风格错误，称为check-package（参见第18.25.2节获取更多信息）。

#### 22.5.2准备补丁系列
从您的本地git视图中提交的更改开始，在生成补丁集之前，请将您的开发分支在上游代码树之上进行变基。为此，请运行：

    $ git fetch --all --tags
    $ git rebase origin/master

现在检查您提交的更改的代码风格：

    $ utils/docker-run make check-package

现在，您已经准备好生成并提交您的补丁集。

要生成补丁集，请运行：

    $ git format-patch -M -n -s -o outgoing origin/master

这将在outgoing子目录中生成补丁文件，并自动添加Signed-off-by行。

生成补丁文件后，您可以使用您喜欢的文本编辑器在提交之前进行审查/编辑提交消息。

Buildroot提供了一个方便的工具，用于确定应将补丁发送给谁，称为get-developers（请参阅第23章获取更多信息）。该工具读取您的补丁并输出适当的git send-email命令以使用：

    $ ./utils/get-developers outgoing/*

使用get-developers的输出发送您的补丁：
    
    $ git send-email --to buildroot@buildroot.org --cc bob --cc alice outgoing/*

或者，可以直接使用get-developers -e与git send-email的--cc-cmd参数一起使用，以自动抄送相关的开发人员：
    
    $ git send-email --to buildroot@buildroot.org \
        --cc-cmd './utils/get-developers -e' origin/master

可以配置git自动执行此操作：
    
    $ git config sendemail.to buildroot@buildroot.org
    $ git config sendemail.ccCmd "$(pwd)/utils/get-developers -e"

然后只需执行：
    
    $ git send-email origin/master

请注意，git应配置为使用您的电子邮件帐户。要配置git，请参阅man git-send-email或在Google中搜索。

如果您不使用git send-email，请确保已发布的补丁没有换行，否则它们无法轻松应用。在这种情况下，请修复您的电子邮件客户端，或者更好地学会使用git send-email。


#### 22.5.3 封面信
如果您想将整个补丁集呈现在单独的邮件中，请在git format-patch命令中添加--cover-letter选项（有关更多信息，请参阅man git-format-patch）。这将生成一个模板，用于介绍您的补丁系列的引言邮件。

在以下情况下，封面信可能有助于介绍您提出的更改：
- 系列中有大量的提交；
- 更改对项目的其余部分有深远影响；
- RFC 1；
- 每当您觉得它有助于介绍您的工作、您的选择、审查过程等。

#### 22.5.4 维护分支的补丁
在维护分支上修复错误时，应首先在主分支上修复错误。此类补丁的提交日志可以包含一条提交后注释，指定受影响的分支。
```
package/foo: fix stuff

Signed-off-by: Your Real Name <your@email.address>
---
Backport to: 2020.02.x， 2020.05.x
(2020.08.x not affected as the version was bumped)
```
这些更改将由维护者将其回溯到受影响的分支。

然而，有些错误可能仅适用于特定的版本，例如因为它使用了一个旧版本的软件包。在这种情况下，补丁应基于维护分支，并且补丁主题前缀必须包含维护分支的名称（例如"[PATCH 2020.02.x]"）。这可以使用git format-patch的--subject-prefix选项完成：
```
$ git format-patch --subject-prefix "PATCH 2020.02.x" \
    -M -s -o outgoing origin/2020.02.x
```
然后按照上述所述使用git send-email发送补丁。

#### 22.5.5 补丁修订更改日志
当请求改进时，每个提交的新版本应包含每个提交之间的修改的变更日志。请注意，当您的补丁系列由封面信引入时，除了每个提交中的变更日志外，封面信中还可以添加总体变更日志。重新制作补丁系列的最佳方法是交互式变基：git rebase -i origin/master。有关更多信息，请参阅git手册。

将此变更日志添加到每个提交时，请在编辑提交消息时添加Signed-off-by部分之下的---和您的变更日志。

尽管变更日志在邮件线程中对审阅者可见，在patchwork中也可见，但是当补丁合并时，git会自动忽略---之下的行。这是预期的行为：变更日志不应永远保留在项目的git历史记录中。

以下是推荐的布局：
```
Patch title: short explanation， max 72 chars

A paragraph that explains the problem， and how it manifests itself. If
the problem is complex， it is OK to add more paragraphs. All paragraphs
should be wrapped at 72 characters. 

A paragraph that explains the root cause of the problem. Again， more
than one paragraph is OK.

Finally， one or more paragraphs that explain how the problem is solved.
Don't hesitate to explain complex solutions in detail.

Signed-off-by: John DOE <john.doe@example.net>

---
Changes v2 -> v3: 
    - foo bar (suggested by Jane) 
    - bar buz
Changes v1 -> v2: 
    - alpha bravo (suggested by John) 
    - charly delta
```

任何补丁修订版本都应包含版本号。版本号由字母v和大于或等于2的整数组成（例如"PATCH v2"，"PATCH v3"......）。

使用git format-patch的--subject-prefix选项可以轻松处理此问题：
```
$ git format-patch --subject-prefix "PATCH v4" \
    -M -s -o outgoing origin/master
```

自git版本1.8.1以来，您还可以使用-v <n>（其中<n>是版本号）：
```
$ git format-patch -v4 -M -s -o outgoing origin/master
```

当您提供补丁的新版本时，请在patchwork中将旧版本标记为已废弃。您需要在patchwork上创建一个帐户，以便能够修改您的补丁的状态。请注意，您只能更改自己提交的补丁的状态，这意味着您在patchwork中注册的电子邮件地址应与您用于发送补丁到邮件列表的地址相匹配。

提交补丁到邮件列表时，您还可以添加--in-reply-to <message-id>选项。要回复的邮件的ID可以在patchwork的"Message Id"标签下找到。in-reply-to的优点是patchwork将自动将上一个版本的补丁标记为已废弃。

### 22.6 报告问题/错误或寻求帮助
在报告任何问题之前，请在邮件列表归档中查看是否有人已经报告和/或修复了类似的问题。

无论您选择通过在错误跟踪器中打开错误还是通过发送邮件到邮件列表来报告错误或寻求帮助，都需要提供一些详细信息，以帮助人们重现并找到问题的解决方案。

尽量以帮助他人的角度思考；在那种情况下，您需要什么？

以下是在这种情况下提供的一些详细信息的简短列表：
- 主机机器（操作系统/版本）
- Buildroot的版本
- 构建失败的目标
- 构建失败的软件包
- 失败的命令及其输出
- 您认为可能相关的任何信息

此外，您应该添加.config文件（或如果您知道如何添加，可以添加一个defconfig；参见第9.3节）。

如果这些细节中的一些太大了，请毫不犹豫地使用pastebin服务。请注意，并非所有可用的pastebin服务在下载原始粘贴时都会保留Unix风格的行终止符。以下pastebin服务已知能正常工作：- https://gist.github.com/ - http://code.bulix.org/


### 22.7 使用运行时测试框架
Buildroot包含一个基于Python脚本和QEMU运行时执行的运行时测试框架。该框架的目标如下：
- 构建一个明确定义的Buildroot配置
- 可选地验证构建输出的某些属性
- 可选地在Qemu下启动构建结果，并验证给定功能是否按预期工作

使用运行时测试框架的入口点是support/testing/run-tests工具，该工具具有一系列在工具的帮助-h描述中详细记录的选项。一些常见的选项包括设置下载文件夹、输出文件夹、保留构建输出，以及对于多个测试用例，您可以为每个测试用例设置JLEVEL。

下面是一个运行测试用例的示例步骤：
- 首先，让我们看看所有的测试用例选项。可以通过执行support/testing/run-tests -l来列出这些测试用例。在测试开发期间，可以在控制台上逐个运行这些测试用例，也可以选择性地作为一组子集进行运行。
```
$ support/testing/run-tests -l
List of tests
test_run (tests.utils.test_check_package.TestCheckPackage)
test_run (tests.toolchain.test_external.TestExternalToolchainBuildrootMusl) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainBuildrootuClibc) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainCCache) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainCtngMusl) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainLinaroArm) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainSourceryArmv4) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainSourceryArmv5) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainSourceryArmv7) ... ok
[snip]
test_run (tests.init.test_systemd.TestInitSystemSystemdRoFull) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRoIfupdown) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRoNetworkd) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRwFull) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRwIfupdown) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRwNetworkd) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRo) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRoNet) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRw) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRwNet) ... ok

Ran 157 tests in 0.021s

OK
```

- 然后运行一个 test 案例
```
$ support/testing/run-tests -d dl -o output_folder -k tests.init.test_busybox. ←-
    TestInitSystemBusyboxRw
15:03:26 TestInitSystemBusyboxRw Starting
15:03:28 TestInitSystemBusyboxRw Building
15:08:18 TestInitSystemBusyboxRw Building done
15:08:27 TestInitSystemBusyboxRw Cleaning up
.
Ran 1 test in 301.140s

OK
```
标准输出指示测试是否成功。默认情况下，测试的输出文件夹会被自动删除，除非使用-k选项来保留输出目录。


#### 22.7.1 创建一个测试用例
在Buildroot存储库中，测试框架位于support/testing/目录下的conf、infra和tests文件夹中。所有的测试用例都存放在tests文件夹下，并按照表示测试类别的不同文件夹进行组织。了解如何创建测试用例的最好方法是查看一些基本的文件系统支持/测试/tests/fs/和init支持/测试/tests/init/测试脚本。这些测试提供了基本测试的良好示例，包括检查构建结果和进行运行时测试。还有其他更高级的案例，使用嵌套的br2-external文件夹提供框架和额外的软件包。

创建一个基本的测试用例包括：
- 定义一个继承自infra.basetest.BRTest的测试类
- 定义测试类的config成员，用于为该测试用例构建Buildroot配置。它可以选择依赖于运行时测试基础设施提供的配置片段: infra.basetest.BASIC_TOOLCHAIN_CONFIG用于获取基本的架构/工具链配置，infra.basetest.MINIMAL_CONFIG用于不构建任何文件系统。使用infra.basetest.BASIC_TOOLCHAIN_CONFIG的优势在于提供了一个相匹配的Linux内核映像，可以在Qemu中启动生成的映像而无需在测试用例的一部分中构建Linux内核映像，从而大大减少了测试用例所需的构建时间。
- 实现一个def test_run(self):函数，在构建完成后实现要运行的实际测试。它们可以是通过使用run_cmd_on_host()辅助函数在主机上运行命令来验证构建输出的测试。或者它们可以使用测试用例中可用的Emulator对象self.emulator在Qemu中引导生成的系统。例如，self.emulator.boot()允许在Qemu中引导系统，self.emulator.login()允许登录，self.emulator.run()允许在Qemu中运行shell命令。

创建测试脚本后，将自己添加到DEVELOPERS文件中，成为该测试用例的维护者。


#### 22.7.2 调试测试用例
当运行一个测试用例时，output_folder将包含以下内容。
```
$ ls output_folder/
TestInitSystemBusyboxRw/
TestInitSystemBusyboxRw-build.log
TestInitSystemBusyboxRw-run.log
```
TestInitSystemBusyboxRw/是Buildroot的输出目录，只有在传递-k选项时才会保留。

TestInitSystemBusyboxRw-build.log是Buildroot构建的日志。

TestInitSystemBusyboxRw-run.log是Qemu引导和测试的日志。只有在构建成功且测试用例涉及在Qemu下引导时，该文件才会存在。

如果您想手动运行Qemu对构建结果进行手动测试，TestInitSystemBusyboxRw-run.log的前几行包含要使用的Qemu命令行。

您还可以在output_folder中进行当前源代码的修改（例如，用于调试目的），然后重新运行标准的Buildroot make目标（以便使用新的修改重新生成完整的映像），然后重新运行测试。


#### 22.7.3 运行时测试和Gitlab CI
所有的运行时测试都会定期由Buildroot Gitlab CI基础设施执行，参见.gitlab.yml和https://gitlab.com/buildroot.org/-buildroot/-/jobs。

您还可以使用Gitlab CI来测试您的新测试用例，或者在Buildroot中进行更改后验证现有的测试是否继续工作。

为了实现这一点，您需要在Gitlab上创建Buildroot项目的分支，并能够将分支推送到您在Gitlab上的Buildroot分支。

您推送的分支的名称将决定是否触发Gitlab CI流水线，以及为哪些测试用例触发。

在下面的示例中，分支名称的<name>部分是您选择的任意字符串。

- 要触发所有run-test测试用例的作业，推送一个以-runtime-tests结尾的分支:

    $ git push gitlab HEAD:<name>-runtime-tests

- 要触发一个或多个测试用例的作业，推送一个以完整测试用例名称结尾的分支（tests.init.test_busybox.TestInitSystemBusyboxRo）
或以测试类别名称结尾的分支（tests.init.test_busybox）：

    $ git push gitlab HEAD:<name>-<test case name>
    
运行一个测试的示例:

    $ git push gitlab HEAD:foo-tests.init.test_busybox.TestInitSystemBusyboxRo

运行几个属于同一组的测试的示例:

    $ git push gitlab HEAD:foo-tests.init.test_busybox
    $ git push gitlab HEAD:foo-tests.init



## Chapter 23、DEVELOPERS文件和get-developers
主要的Buildroot目录中包含一个名为DEVELOPERS的文件，列出了与Buildroot的各个领域相关的开发人员。通过这个文件，get-developers工具可以：
- 通过解析补丁并将修改的文件与相关开发人员进行匹配，计算应该发送补丁的开发人员列表。具体详情请参见第22.5节。
- 查找负责特定架构或软件包的开发人员，以便在该架构或软件包发生构建失败时通知他们。这是与Buildroot的自动构建基础设施进行交互完成的。

我们要求在Buildroot中添加新软件包、新板卡或一般新功能的开发人员在DEVELOPERS文件中注册自己。例如，我们期望开发人员在贡献新软件包时，在补丁中包含对DEVELOPERS文件的适当修改。

DEVELOPERS文件的格式在文件本身中有详细的文档说明。

位于utils/目录中的get-developers工具允许针对各种任务使用DEVELOPERS文件：
- 当将一个或多个补丁作为命令行参数传递时，get-developers将返回适当的git send-email命令。如果传递了-e选项，将只打印适合git send-email --cc-cmd的电子邮件地址格式。
- 当使用-a <arch>命令行选项时，get-developers将返回负责给定架构的开发人员列表。
- 当使用-p <package>命令行选项时，get-developers将返回负责给定软件包的开发人员列表。
- 当使用-c命令行选项时，get-developers将查看Buildroot代码库中所有版本控制的文件，并列出没有任何开发人员处理的文件。此选项的目的是帮助完善DEVELOPERS文件。
- 当使用-v命令行选项时，它会验证DEVELOPERS文件的完整性，并对不匹配的项目发出警告。



## Chapter 24、发布工程
### 24.1 发布
Buildroot项目每季度发布一次，并每月进行错误修复的发布。每年的第一个发布是长期支持（LTS）发布。
- 季度发布：2020.02、2020.05、2020.08和2020.11
- 错误修复发布：2020.02.1、2020.02.2，...
- LTS发布：2020.02、2021.02，...

发布的支持持续到下一个发布的第一个错误修复版本，例如，当发布了2020.08.1时，2020.05.x就到了生命周期终结。

LTS发布的支持持续到下一个LTS的第一个错误修复版本，例如，当发布了2021.02.1时，2020.02.x就到了生命周期终结。

### 24.2 开发
每个发布周期包括在主分支上进行两个月的开发和一个月的稳定期，然后进行发布。在此阶段，不会向主分支添加新功能，只进行错误修复。

稳定期从标记-rc1开始，直到发布之前的每周都会标记另一个候选版本。

为了在稳定期间处理新功能和版本升级，可以为这些功能创建一个next分支。一旦当前发布完成，next分支就会合并到主分支，并在那里继续下一个发布的开发周期。




----------------------


# Part IV 附录

## Chapter 25、makedev语法文档
在Buildroot中，makedev语法用于定义权限的更改，或者要创建和如何创建设备文件，以避免调用mknod。

这种语法派生自makedev实用程序，更详细的文档可以在package/makedevs/README文件中找到。

它采用以空格分隔的字段列表形式，每行一个文件；
|name|type|mode|uid|gid|major|minor|start|inc|count|
|-|-|-|-|-|-|-|-|-|-|

字段包括:
- name是要创建/修改的文件的路径
- type是文件的类型，可以是以下之一:
    - f：普通文件
    - d：目录
    - r：递归目录
    - c：字符设备文件
    - b：块设备文件
    - p：命名管道
- mode是常规权限设置（只允许使用数字值）
- uid和gid是要设置在该文件上的UID和GID；可以是数字值或实际名称
- major和minor用于设备文件，对于其他文件设置为-
- start、inc和count用于创建一批文件，可以通过循环减少，从start开始，按inc递增计数器直到达到count

假设您想要更改给定文件的权限；使用这种语法，您需要编写：
```
/usr/bin/foo f 755 0 0 - - - - -
/usr/bin/bar f 755 root root - - - - -
/data/buz f 644 buz-user buz-group - - - - -
```

另外，如果您想要递归更改目录的所有者/权限，您可以编写（将UID设置为foo，GID设置为bar，并为目录/usr/share/myapp及其所有文件和目录设置访问权限为rwxr-x---）：
```
/usr/share/myapp r 750 foo bar - - - - -
```

另一方面，如果您想要创建设备文件/dev/hda以及对应的15个分区文件，您需要为/dev/hda编写：
```
/dev/hda b 640 root root 3 0 0 0 -
```

然后为/dev/hda的分区对应的设备文件，/dev/hdaX，其中X从1到15：
```
/dev/hda b 640 root root 3 1 1 1 15
```

如果启用了BR2_ROOTFS_DEVICE_TABLE_SUPPORTS_EXTENDED_ATTRIBUTES，将支持扩展属性。
这可以在描述文件的行之后添加以|xattr开头的行来完成。目前，仅支持capability作为扩展属性。
|xattr|capability|
|-|-|

- |xattr是指示扩展属性的“标志”
- capability是要添加到先前文件的能力
如果您想要将cap_sys_admin能力添加到二进制文件foo，您将编写：
```
/usr/bin/foo f 755 root root - - - - -
|xattr cap_sys_admin+eip
```

您可以通过使用多个|xattr行向文件添加多个能力。如果您想要将cap_sys_admin和cap_net_admin能力添加到二进制文件foo，您将编写：
```
/usr/bin/foo f 755 root root - - - - -
|xattr cap_sys_admin+eip
|xattr cap_net_admin+eip
```


## Chapter 26、Makeusers语法文档
创建用户的语法受到上述makedev语法的启发，但是它是特定于Buildroot的。

添加用户的语法是一个以空格分隔的字段列表，每行一个用户；字段包括:
|username|uid|group|gid|password|home|shell|groups|comment|
|-|-|-|-|-|-|-|-|-|


其中:
- username是用户的所需用户名（也称为登录名）。它不能为root，并且必须是唯一的。如果设置为-，则只会创建一个组。
- uid是用户的所需UID。它必须是唯一的，不能为0。如果设置为-1或-2，则Buildroot将计算一个唯一的UID，其中-1表示来自[100. . . 999]的系统UID，-2表示来自[1000. . . 1999]的用户UID。
- group是用户主组的所需名称。它不能是root。如果该组不存在，将创建它。
- gid是用户主组的所需GID。它必须是唯一的，不能为0。如果设置为-1或-2，并且该组不存在，则Buildroot将计算一个唯一的GID，其中-1表示来自[100. . . 999]的系统GID，-2表示来自[1000. . . 1999]的用户GID。
- password是使用crypt(3)编码的密码。如果以!为前缀，则禁用登录。如果以=为前缀，则将其解释为明文，并将进行crypt编码（使用MD5）。如果以！=为前缀，则密码将进行crypt编码（使用MD5），并且登录将被禁用。如果设置为*，则不允许登录。如果设置为-，则不设置密码值。
- home是用户的所需主目录。如果设置为-，将不创建主目录，用户的主目录将为/。不允许显式将home设置为/。
- shell是用户的所需shell。如果设置为-，则将/bin/false设置为用户的shell。
- groups是逗号分隔的附加组列表，用户应该是这些组的成员。如果设置为-，则用户将不是任何附加组的成员。缺少的组将以任意gid创建。
- comment（也称为GECOS字段）是几乎自由格式的文本。

每个字段的内容都有一些限制:
- 除了comment之外，所有字段都是强制的。
- 除了comment之外，字段不得包含空格。
- 任何字段都不能包含冒号(:)。

如果home不是-，则主目录及其下的所有文件将属于该用户及其主组。

例如：
```
foo -1 bar -1 !=blabla /home/foo /bin/sh alpha，bravo Foo user
```
这将创建以下用户：
- username（也称为登录名）为：foo
- uid由Buildroot计算
- 主组为：bar
- 主组gid由Buildroot计算
- 明文密码为：blabla，将进行crypt(3)编码，并禁用登录。
- home为：/home/foo
- shell为：/bin/sh
- foo还是alpha和bravo组的成员
- comment为：Foo用户

```
test 8000 wheel -1 = - /bin/sh - Test user
```
这将创建以下用户：
- username（也称为登录名）为：test
- uid为：8000
- 主组为：wheel
- 主组gid由Buildroot计算，并使用根文件系统模板中定义的值
- 密码为空（即没有密码）。
- home为/，但不属于test用户
- shell为：/bin/sh
- test不是任何其他组的成员
- comment为：Test用户

### 26.1 自动UID和GID的注意事项
在更新Buildroot或添加/删除配置中的软件包时，自动UID和GID可能会发生变化。如果使用该用户或组创建了持久文件，这可能会导致问题：升级后，它们将突然具有不同的所有者。
因此，建议将自动生成的ID永久化。可以通过添加一个包含生成的ID的用户表来实现。只需要对实际创建持久文件的UID执行此操作，例如数据库。



## Chapter 27、从旧的Buildroot版本迁移
某些版本引入了向后不兼容性。本节解释了这些不兼容性，并为每个不兼容性解释了完成迁移所需的操作。
### 27.1 一般方法
要从旧的Buildroot版本迁移，请执行以下步骤。
1. 对于所有的配置，在旧的Buildroot环境中进行构建。运行make graph-size。将graphs/file-size-stats.csv保存在不同的位置。运行make clean以删除其余部分。
2. 查看下面的特定迁移说明，并对外部软件包和自定义构建脚本进行必要的调整。
3. 更新Buildroot。
4. 从现有的.config开始运行make menuconfig。
5. 如果在Legacy菜单中启用了任何选项，请检查其帮助文本，取消选择它，并保存配置。
6. 要获取更多详细信息，请查看您需要的软件包的git提交消息。进入packages目录并运行git log <旧版本>.. -- <您的软件包>。
7. 在新的Buildroot环境中进行构建。
8. 修复外部软件包中的构建问题（通常是由于更新的依赖关系）。
9. 运行make graph-size。
10. 将新的file-size-stats.csv与原始文件进行比较，以检查是否没有消失的必需文件，并且是否没有出现新的不必要的大文件。
11. 对于在自定义叠加层中覆盖Buildroot创建的文件的配置（和其他）文件，请检查Buildroot生成的文件中是否有需要传播到自定义文件的更改。

### 27.2 迁移到2016.11
在Buildroot 2016.11之前，一次只能使用一个br2-external树。从Buildroot 2016.11开始，可以同时使用多个br2-external树（详见第9.2节）。

然而，这意味着旧的br2-external树不能直接使用。需要进行一个小的更改：给你的br2-external树添加一个名称。

这可以通过以下几个简单的步骤完成：• 首先，在你的br2-external树的根目录下创建一个名为external.desc的新文件，其中只有一行定义了你的br2-external树的名称：

    $ echo 'name: YOUR_TREE_NAME' > external.desc

注意：选择名称时要小心：它必须是唯一的，并且只能由ASCII字符集[A-Za-z0-9_]中的字符组成。• 接下来，在你的br2-external树中将每个BR2_EXTERNAL的出现都改为新的变量：

    $ find . -type f | xargs sed -i 's/BR2_EXTERNAL/BR2_EXTERNAL_YOUR_TREE_NAME_PATH/g'

现在，你的br2-external树可以在Buildroot 2016.11及更高版本中使用了。

注意：这个更改使得你的br2-external树与2016.11之前的Buildroot不兼容。

### 27.3 迁移到2017.08
在Buildroot 2017.08之前，主机软件包安装在$(HOST_DIR)/usr目录下（例如，autotools的--prefix=$(HOST_DIR)/usr）。

从Buildroot 2017.08开始，它们直接安装在$(HOST_DIR)目录下。

每当一个软件包安装一个可执行文件，并且该可执行文件与$(HOST_DIR)/lib目录中的库链接时，它必须具有指向该目录的RPATH。

不再接受指向$(HOST_DIR)/usr/lib的RPATH。
