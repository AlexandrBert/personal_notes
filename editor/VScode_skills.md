# VSCODE 运行环境配置 #
## Windows端运行GCC ##
### MinGW-w64 ###
以前要在 Windows 端运行 GCC 或者 make 环境需要用到 MinGW 这个工具，现在已经停止更新，更换为 MinGW-w64 项目。

#### 下载： ####
下载地址：[https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)


- 在线安装版本安装可能失败，所以选择完整的安装版本:

> **MinGW-W64 GCC-8.1.0**
> 
> 
> - x86_64-win32-seh

- 运行exe软件选择对应安装的版本的设置:

> **Version:** 指的是 gcc 的版本，如果没有特殊的需求，一般选择最高的版本号即可。最高版本是8.1.0 ，选中它即可
> 
> **Architechture:** 电脑系统是 64位的，选择 x86_64；如果是 32位 系统，则选择 i686
> 
> **Threads:** 如果是 Windows ，选择 win32 ，如果是 Linux、Unix、Mac OS 等其他操作系统要选择 posix
> 
> **Exception：** seh 是新发明的，而 sjlj 则是古老的。seh 性能比较好，但不支持 32位。 sjlj 稳定性好，支持 32位。建议64位操作系统选择seh。

- 将下载的文件夹解压，放到自己设定的目录下，并将解压的 bin 目录添加到 Windows 系统的环境变量 path 中：

> 假设解压后放在 ` C:\Program Files\mingw64 ` 目录，则在系统环境变量中添加一个环境变量 ` C:\Program Files\mingw64\bin ` 。

- 完成上述步骤后，通过命令行 `gcc -v` 以及 `gdb -v` 就可以查看是否安装成功，这一步需要重新打开 VScode 才会生效。



## 工作区独立编码 ##
由于不同的项目所用的默认编码格式不同，所以选择在不同的工作区使用不同的编码格式，可以通过设置工作区下 `.vscode` 文件夹中的文件 `settings.json` 文件进行修改单独的工作区设置，直接根据现有格式在工作区目录下添加配置即可。

具体的设置变量名可以通过先查看首选项设置中的英文名称，在`帮助文档` 路径或网站: [getstarted/settings](https://code.visualstudio.com/docs/getstarted/settings) 搜索查看。

如想要改变每个工作区的默认编码，可以在 `settings.json` 文件中添加：

>`"files.encoding": "utf8"`

修改完成后重新打开文件就发现编码自动转换成功了。

也可以通过首选项设置中的工作区编码修改，但是可能有其他原因会导致不生效，保险起见最好直接修改 `settings.json` 文件。

## 快捷键

1. 代码块快捷折叠和展开：
- 要操作光标所在文件中的所有代码块：

    - 折叠所有 `Ctrl+K+0`
    - 展开所有 `Ctrl+K+J`
- 仅仅操作光标所处代码块内的代码：

    - 折叠 `Ctrl+Shift+[`
    - 展开 `Ctrl+Shift+]`