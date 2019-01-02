# 一、  Linux core dump ulimit
如果想让系统在信号中断造成的错误时产生core文件, 我们需要在shell中按如下设置:
这些需要有root权限, 在ubuntu下每次重新打开中断都需要重新输入上面的第一条命令, 来设置core大小为无限.
```
1. ulimit -c unlimited			//设置core大小为无限，写入 /etc/profile 永久生效
2. ulimit unlimited				//设置文件大小为无限，写入 /etc/profile 永久生效
```

3. 更改dumpdump 文件core的默认文件名
原因：缺省情况下，内核在coredump时所产生的core文件放在与该程序相同的目录中，并且文件名固定为core。很显然，如果有多个程序产生core文件，或者同一个程序多次崩溃，就会重复覆盖同一个core文件。
方法：
/etc/sysctl.conf文件中，对sysctl变量kernel.core_pattern的设置。
```
kernel.core_pattern = /path_to_core/core_%e_%p_%s_%t				//程序名，进程PID，导致coredump的信号，发生时间
kernel.core_uses_pid = 0
```
4. linux下可用 apport-cli path-to-file/x.crash 文件查看（如果启用了的话）