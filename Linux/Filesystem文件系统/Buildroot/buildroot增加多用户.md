# Buildroot 配置多用户登录

## 1. 创建并使能多用户表文件
### 1.1 创建文件并指定目录
自定义一个 `users_table.txt` 文件；或者采用官方的建议：创建一个 `board/<manufacturer>/<boardname>/device_table.txt` ；

使用 `make menuconfig` 添加 `users_table.txt` 的路径；
```
System configuration  --->
    (./boe_custom/users_table.txt) Path to the users table
```
或者打开 config 文件添加路径到 `BR2_ROOTFS_USERS_TABLES` ;
```config
BR2_ROOTFS_USERS_TABLES="./boe_custom/users_table.txt"
```

### 1.2 添加用户
在 `users_table.txt` 文件中添加用户，每行一个用户；
```txt
gateway -1 boeos -1 =gateway /home/gateway /bin/sh - Gateway user
```

## 2. `users_table.txt` 文件语法
通过搜索整个工程目录，在 `docs/manual/custom-users-tables.txt` 文件中致命文件语法在 `xref：makeuser-syntax` 语法介绍文件中，位于 `docs/manual/makeuser-syntax.txt` ：

### 2.1 用户创建语法说明
用户创建的语法受 `makedev` 语法的启发，但专门为 Buildroot 设计。

添加用户使用空格分隔的字段列表，每行一个用户;字段如下：

|用户名(username)|uid|主组(group)|gid|密码(password)|主目录(home)|shell|附加组(groups)|注释(comment)|
|-|-|-|-|-|-|-|-|-|

其中：

- `username` (也称登录名)：用户的期望登录名。不能是"root"，必须唯一。如果设置为"-"，则只创建一个组。

- `uid` ：用户的期望 UID 。必须唯一，不能是 0 。如果设置为 "-1" 或 "-2" ， Buildroot 将自动分配一个唯一的 UID :
    - "-1" 表示系统 UID 在 [100...999] 范围内；
    - "-2" 表示用户 UID 在 [1000...1999] 范围内。

- `group` ：用户主组的期望名称。不能是"root"。如果组不存在则创建。

- `gid` ：用户主组的期望 GID 。必须唯一，不能是 0 。如果设置为 "-1"或"-2" ，且组不存在，Buildroot 将自动分配一个唯一的 GID ，与 UID 规则相同。 

- `password` ：使用 `crypt(3)` 编码后的密码。
    - 如果前缀为 "`!`" ，则禁用登录。
    - 如果前缀为 "`=`" ，则将其解释为明文，并使用MD5进行加密。
    - 如果前缀为 "`!=`" ，则使用MD5对密码进行加密，并禁用登录。
    - 如果设置为 "`*`" ，则不允许登录。
    - 如果设置为 "`-`" ，则不设置密码值。

- `home` ：用户的期望主目录。如果设置为"-"，则不创建主目录，主目录为"/"。主目录不能显式设置为"/"。

- `shell` ：用户的期望shell。如果设置为"-"，则设为 "/bin/false"。

- `groups` ：逗号分隔的附加组列表。如果设置为"-"，则不加入任何附加组。缺失的组将使用任意GID自动创建。

- `comment` ：描述用户的注释字段。

每个字段的内容还有一些限制：
- 除注释外，所有字段都是必需的。
- 除注释外，字段不能包含空格。
- 字段不能包含冒号(：)。

如果主目录不是-，则主目录及以下所有文件都将属于该用户和其主组。

### 2.2 示例
这里是两个用户创建示例的翻译：

#### 2.2.1 示例 1
```
    foo -1 bar -1 !=blabla /home/foo /bin/sh alpha，bravo Foo user
```
第一个示例：
- `username` (登录名称)是： foo ；
- `uid` 会由 Buildroot 计算；
- main `group` 是： bar  ；
- 主组 `gid` 会由 Buildroot 计算；
- 明文 `password` 是： blabla ，会使用 `crypt(3)` 进行编码，且被禁止登录；
- `home` 目录是： /home/foo ；
- 登录 `shell` 是： /bin/sh ；
- foo 也是附加 `groups` alpha 和 bravo 的成员；
- `comment` 是： Foo user 。

#### 2.2.2 示例 2
```
    test 8000 wheel -1 = - /bin/sh - Test user
```
第二个示例：
- `username` (登录名称)是：test ；
- `uid` 是：8000 ；
- main `group` 是：wheel ；
- 主组 `gid` 会由 Buildroot 计算，并使用根文件系统骨架中定义的值；
- `password` 为空(即没有密码)；
- `home` 目录是：/但test不属于这个目录；
- 登录 `shell` 是：/bin/sh ；
- test 不是任何附加 `groups` 的成员 ；
- `comment` 是：Test user；

自动UID和GID的注意事项：

当升级Buildroot或者向配置中添加或者删除包时，自动UID和GID可能会改变。如果之前使用该UID或GID创建了持久文件，升级后它们可能会突然改变所有者。

所以，最好永久记录自动生成的ID。可以在用户表中添加生成的ID。只需要对实际创建持久文件的UID做此操作，例如数据库UID。