# SSH 服务器搭建错误

## SSH 服务器搭建

1. 在系统中安装 SSH 服务器必须的软件包，如 sshd 或 openssh-server 等。
2. 安装好后可执行文件会安装在 /usr/sbin 目录；
3. SSH 相关的配置文件安装在 /etc/ssh 目录下，包含 root 账户远程登录的 sshd_config 文件等。

## 错误 1：
```bash
Error loading host key "/etc/ssh/ssh_host_rsa_key": incorrect passphrase supplied to decrypt private key
Could not load host key: /etc/ssh/ssh_host_rsa_key
Error loading host key "/etc/ssh/ssh_host_ecdsa_key": incorrect passphrase supplied to decrypt private key
Could not load host key: /etc/ssh/ssh_host_ecdsa_key
Error loading host key "/etc/ssh/ssh_host_ed25519_key": incorrect passphrase supplied to decrypt private key
Could not load host key: /etc/ssh/ssh_host_ed25519_key
```

这个错误表示 `SSH` 主机密钥(`/etc/ssh/ssh_host_rsa_key`、`/etc/ssh/ssh_host_ecdsa_key`、`/etc/ssh/ssh_host_ed25519_key`)解密时提供的密码错误。
一般可能的原因和解决方法:
1. 密钥文件密码错误。检查密钥文件密码是否正确。
2. 密钥文件权限错误。检查密钥文件权限是否为600。
3. 密钥文件损坏。删除密钥文件,重新生成新的密钥对。
4. `SSH` 配置错误。检查 `sshd_config` 配置是否正确。

解决方法:
1. 删除旧的密钥文件:
```bash
rm /etc/ssh/ssh_host_rsa_key
```
2. 重新生成 `SSH` 主机密钥:
```bash
$ ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N '' 
$ ssh-keygen -t rsa -f /etc/ssh/ssh_host_ecdsa_key -N ''
$ ssh-keygen -t rsa -f /etc/ssh/ssh_host_ed25519_key -N ''
```
3. 修改密钥文件权限:
```bash
chmod 600 /etc/ssh/ssh_host_rsa_key
chmod 600 /etc/ssh/ssh_host_ecdsa_key
chmod 600 /etc/ssh/ssh_host_ed25519_key
```
4. 重启 `SSH` 服务:
```bash
systemctl restart sshd 
# 或 /etc/init.d/ssh restart
```
5. 检查 `SSH` 日志查找其他错误信息。
一般来说,删除旧密钥并重新生成新的无密码密钥对可以解决这个问题。

## 错误 2：无法使用 root 账户远程登录

这个错误是由于 `SSHD` 服务的配置文件中，没有开启 `ssh` 远程使用 `root` 账户登录的权限。

解决方法：

1. 在 `/etc/ssh/sshd_config` 文件修改权限，开启远程登录 `root` 的权限。
```bash
# Authentication:

#LoginGraceTime 2m
#PermitRootLogin prohibit-passworda //将这一句注释并修改为 yes
PermitRootLogin yes
```
