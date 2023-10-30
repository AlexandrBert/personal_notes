# **CMake简单使用教程**

## 安装CMake

在虚拟机中，如 Ubuntu20.04 中直接使用指令安装 CMake:

```bash
$ sudo apt install cmake
#查看版本确定是否安装成功
$ cmake -version
#安装成功返回CMake信息
$ cmake version 3.16.3
$ CMake suite maintained and supported by Kitware (kitware.com/cmake).

```

## CMake的使用

1. 在工程目录下创建一个 `CMakeLists.txt` 文件，使用CMake前需要编写该文件，主要内容包括：
   
   ```CMake
   # 项目所需最低Cmake版本
   cmake_minimum_required(VERSION 3.12)

   #[[第一个字段是项目名称；
   第二个是通过VERSION指定版本号，格式为major.minor.patch.tweak；
   ]]
   project(mysystem VERSION 1.0.0 LANGUAGES C CXX)

   # 源文件与可执行文件
   add_executable(helloc main.cpp)

   ```