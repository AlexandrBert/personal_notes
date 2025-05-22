# Makefile 

## GNU make 概述
make 是一个命令工具，它解释 Makefile 中的指令（应该说是规则）。在 Makefile
文件中描述了整个工程所有文件的编译顺序、编译规则。

**在 Makefile 中可以使用系统 shell 所提供的任何命令来完成想要的工作**。Makefile（在其它的系统上可能是另外的文件名）在绝大多数的 IDE 开发环境中都在使用，已经成为一种工程的编译方法。

**重复执行 make 命令时，会扫描目录下的文件修改时间，如果第一次完成 make 后未清除生成的 .o 文件，第二次 make 时不会编译所有的文件，只会编译有修改的部分以及依赖修改文件的部分。**

## Makefile 简介
在执行 make 之前，需要一个命名为 Makefile 的特殊文件来告诉 make 需要做什么、怎么做。通常，make 工具主要被用来进行工程编译和程序链接。

### Makefile 书写格式
1. 一般格式:
```Makefile
TARGET... : PREREQUISITES... 
    COMMAND
```
- `target`：规则的目标。通常是最后需要生成的文件名或者为了实现这个目的而必需的中间过程文件名。可以是.o文件、也可以是最后的可执行程序的文件名等。另外，目标也可以是一个make执行的动作的名称，如目标“clean”，我们称这样的目标是“伪目标”。参考4.6 Makefile伪目标 一节；

- `prerequisites`：规则的依赖。生成规则目标所需要的文件名列表。通常一个目标依赖于一个或者多个文件。

- `command`：规则的命令行。是规则所要执行的动作（任意的 shell 命令或者是可在 shell 下执行的程序）。它限定了 make 执行这条规则时所需要的动作。 

2. 书写注意事项
- 一个规则可以有多个命令行，每一条命令占一行。注意：每一个命令行必须以`[Tab]`字符开始，`[Tab]`字符告诉 make 此行是一个命令行。
- 较长行使用反斜线（\）来分解为多行，但需要注意：**反斜线之后不能有空格**。

3. `伪目标`：
Makefile中把那些没有任何依赖只有执行动作的目标称为“伪目标”（`phony targets`）。

4. 默认的情况下，make执行的是Makefile中的第一个规则，此规则的第一个目标称之为“最终目的”或者“终极目标”

### 指定变量 object
使用一个变量“objects”、“OBJECTS”、“objs”、“OBJS”、“obj”或者“OBJ”来作为所有的.o 文件的列表的替代。在使用到这些文件列表的地方，使用此变量来代替。
```Makefile
# 例如下面写法，设置一个变量object
# “objects”作为一个变量，它代表所有的.o文件的列表。
objects = main.o kbd.o command.o display.o \ 
    insert.o search.o files.o utils.o

# 在定义了此变量后，我们就可以在需要使用这些.o文件列表的地方使用“$(objects)”来表示它，
objects = main.o kbd.o command.o display.o \ 
    insert.o search.o files.o utils.o 
edit : $(objects) 
    cc -o edit $(objects) 
……
…… 
clean : 
    rm edit $(objects)
```

## Makefile 内容

在一个完整的 Makefile 中，包含了 5 个东西：显式规则、隐含规则、变量定义、指示符和注释。

- **显式规则**：它描述了在何种情况下如何更新一个或者多个被称为目标的文件（Makefile 的目标文件）。书写 Makefile 时需要明确地给出目标文件、目标的依赖文件列表以及更新目标文件所需要的命令（有些规则没有命令，这样的规则只是纯粹的描述了文件之间的依赖关系）。
- **隐含规则**：它是make根据一类目标文件（典型的是根据文件名的后缀）而自动推导出来的规则。make根据目标文件的名，自动产生目标的依赖文件并使用默认的命令来对目标进行更新（建立一个规则）。
- 变量定义：使用一个字符或字符串代表一段文本串，当定义了一个变量以后，Makefile后续在需要使用此文本串的地方，通过引用这个变量来实现对文本串的使用。
- **Makefile 指示符**：指示符指明在 make 程序读取 makefile 文件过程中所要执行的一个动作。其中包括：
    - 读取一个文件，读取给定文件名的文件，将其内容作为makefile文件的一部分。
    - 决定（通常是根据一个变量的得值）处理或者忽略Makefile中的某一特定部分。
    - 定义一个多行变量。
- **注释**：Makefile 中“#”字符后的内容被作为是注释内容（和 shell 脚本一样）处理。如果此行的第一个非空字符为“#”，那么此行为注释行。注释行的结尾如果存在反斜线（\），那么下一行也被作为注释行。一般在书写 Makefile 时推荐将注释作为一个独立的行，而不要和 Makefile 的有效行放在一行中书写。当在 Makefile 中需要使用字符“#”时，可以使用反斜线加“#”（\#）来实现（对特殊字符“#”的转义），其表示将“#”作为一字符而不是注释的开始标志。

1. 包含其它makefile文件
    >include FILENAMES...

    Makefile 中包含其它文件所需要使用的关键字是“include”，和 c 语言对头文件的包含方式一致。
    - 有多个不同的程序，由不同目录下的几个独立的Makefile来描述其重建规则。需要使用一组通用的变量定义或者模式规则。通用的做法是将这些共同使用的变量或者模式规则定义在一个文件中（没有具体的文件命名限制），在需要使用的 Makefile 中使用指示符“include”来包含此文件。
    - 当根据源文件自动产生依赖文件时；我们可以将自动产生的依赖关系保存在另外一个文件中，主Makefile使用指示符“include”包含这些文件。

    如果指示符“ include ”指定的文件不是以斜线开始（绝对路径，如/usr/src/Makefile...），而且当前目录下也不存在此文件；make将根据文件名试图在以下几个目录下查找：首先，查找使用命令行选项“-I”或者“--include-dir” 指定的目录，如果找到指定的文件，则使用这个文件；否则继续依此搜索以下几个目录（如果其存在）：“/usr/gnu/include”、“/usr/local/include”和“/usr/include”。

    **使用“-include”来代替“include”，可以忽略由于包含文件不存在或者无法创建时的错误提示。为了和其它的 make 程序进行兼容。也可以使用“sinclude”来代替“-include”。**
    
2. 变量 MAKEFILE_LIST

    make 程序在读取多个 makefile 文件时，包括由环境变量“MAKEFILES”指定、命令行指、当前工作下的默认的以及使用指示符“include”指定包含的，在对这些文件进行解析执行之前 make 读取的文件名将会被自动依次追加到变量“MAKEFILE_LIST”的定义域中。

    通过测试此变量的最后一个字来获取当前 make 程序正在处理的makefile 文件名。具体地说就是在一个 makefile 文件中如果使用指示符“include”包含另外一个文件之后，变量“MAKEFILE_LIST”的最后一个字只可能是指示符“include”指定所要包含的那个文件的名字。
    ```makefile
    name1 := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)) 
    include inc.mk 
    name2 := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)) 
    all: 
        @echo name1 = $(name1) 
        @echo name2 = $(name2)
    # 运行结果:
    # name1 = Makefile 
    # name2 = inc.mk
    ```

## Makefile 函数

### origin 函数
函数“origin”和其他函数不同，函数“origin”的动作不是操作变量（它的参数）。它只是获取此变量（参数）相关的信息，告诉我们这个变量的出处（定义方式）。

1. 函数语法：
    ```makefile
    # 语法
    $(origin VARIABLE)

    # 举例
    # 出处： buildroot-2023.05.01 目录中的 Makefile：line 36；
    # 作用：用于检查当前的Makefile是否在命令行中定义了O变量。如果O变量是在命令行中定义的，那么ifneq将把O的值设置为当前目录下的output文件夹。
    ifneq ("$(origin O)", "command line")
    O := $(CURDIR)/output
    endif
    ```

2. 函数返回

    返回“VARIABLE”的定义方式。用字符串表示。函数的返回情况有以下几种：
    - `undefined` ：变量“VARIABLE”没有被定义。
    - `default` ：变量“VARIABLE”是一个默认定义（内嵌变量）。比如一些隐式变量"CC""MAKE""RM".
    - `environment` ：变量“VARIABLE”是一个系统环境变量，并且make没有使用命令行选项“-e” （Makefile中不存在同名的变量定义，此变量没有被替代）。
    - `environment override` ：变量“VARIABLE”是一个系统环境变量，并且make使用了命令行选项“-e”。Makefile中存在一个同名的变量定义，使用“make -e”时环境变量值替代了文件中的变量定义。
    - `file` ：变量“VARIABLE”在某一个 makefile 文件中定义。
    - `command line` ：变量“VARIABLE”在命令行中定义。
    - `override` ：变量“VARIABLE”在 makefile 文件中定义并使用“override”指示符声明。
    - `automatic` ：变量“VARIABLE”是自动化变量。

### 模式替换函数—patsubst
1. 函数语法：
    ```makefile
    # 语法
    $(patsubst PATTERN,REPLACEMENT,TEXT)

    # 举例
    # 出处： buildroot-2023.05.01 目录中的 Makefile：line 56；
    # 作用：这个命令的作用是将文件名中的百分号（%）替换为对应的路径部分（%/），然后将点（.）替换为对应的文件扩展名（%）。最后，将结果赋值给 O 变量。这在 Makefile 中用于生成目标文件的完整路径。
    override O := $(patsubst %/,%,$(patsubst %.,%,$(O)))
    ```
2. 函数功能  
    搜索“TEXT”中以空格分开的单词，将符合模式“PATTERN”替换为“REPLACEMENT”。参数“PATTERN”中可以使用模式通配符“%”来代表一个单词中的若干字符。如果参数“REPLACEMENT”中也包含一个“%”，那么“REPLACEMENT”中的“%”将是“TATTERN”中的那个“%”所代表的字符串。在“TATTERN”和“REPLACEMENT”中，只有第一个“%”被作为模式字符来处理，之后出现的不再作模式字符（作为一个字符）。在参数中如果需要将第一个出现的“%”作为字符本身而不作为模式字符时，可使用反斜杠“\”进行转义处理（转义处理的机制和使用静态模式的转义一致。
3. 返回值：替换后的新字符串。
4. 函数说明：参数“TEXT”单词之间的多个空格在处理时被合并为一个空格，并忽略前导和结尾空格。

### 取首单词函数—firstword
1. 函数语法：
    ```makefile
    # 语法
    $(firstword TEXT)

    # 举例，返回值为“foo”。函数“firstword”实现的功能等效于“$(word 1, NAMES…)”。
    $(firstword foo bar)
    ```
2. 函数功能  
    返回字符串中第一个单词。
3. 返回值：第一个单词。

### 取尾单词函数—lastword
1. 函数语法：
    ```makefile
    # 语法
    $(lastword TEXT)

    # 举例，返回值为“bar”。函数“lastword”实现的功能等效于“$(word -1, NAMES…)”。
    $(lastword foo bar)
    ```
2. 函数功能  
    返回字符串中最后一个单词。
3. 返回值：最后一个单词。

### 取单词函数—word
1. 函数语法：
    ```makefile
    # 语法
    $(word NUMBER, TEXT)
    $(word NUMBER1, NUMBER2, TEXT)
    ```
2. 函数功能  
    返回字符串中第 NUMBER 个单词。
3. 返回值：第 NUMBER 个单词。

### 取单词函数—words
1. 函数语法：
    ```makefile
    # 语法
    $(words TEXT)
    ```
2. 函数功能  
    返回字符串中的单词数。
3. 返回值：单词数。

### 取单词函数—wordlist
1. 函数语法：
    ```makefile
    # 语法
    $(wordlist FIRST, LAST, TEXT)
    ```
2. 函数功能  
    返回字符串中第 FIRST 到第 LAST 个单词。
3. 返回值：第 FIRST 到第 LAST 个单词。

### 打印错误函数——error
1. 函数语法：
    ```makefile
    # 语法
    $(error TEXT)
    # 示例
    $(error You have make '$(RUNNING_MAKE_VERSION)' installed. GNU make >= $(MIN_MAKE_VERSION) is required)
    ```
2. 函数功能  
    打印错误信息，并退出。
3. 返回值：无。

### 打印警告函数——warning
1. 函数语法：
    ```makefile
    # 语法
    $(warning TEXT)
    ```





## shell 函数

Makefile 中可以调用系统的 shell 指令，如 Linux 系统中就会是 bash 指令，如 buildroot 的 Makefile 开头就是判断 shell 指令类型：
```makefile
# we want bash as shell
SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	 else if [ -x /bin/bash ]; then echo /bin/bash; \
	 else echo sh; fi; fi)
```

在 shell 指令中，可以使用下面格式来调用 shell 指令。
```makefile
$(shell command)
```

### realpath 函数
它用于将一个或多个路径转换为其绝对路径。换句话说，realpath会解析路径中的符号链接和软链接，并返回目标文件的绝对路径。

调用示例：
```makefile
CANONICAL_O := $(shell mkdir -p $(O) >/dev/null 2>&1)$(realpath $(O))
```

## Windows函数
### findstring 函数

可以在一个或多个文本文件中搜索指定的文本字符串，并返回包含该字符串的文件名。

示例：
```makefile
# gcc fails to build when the srcdir contains a '@'
ifneq ($(findstring @,$(CANONICAL_O)),)
$(error The build directory can not contain a '@')
endif
```


