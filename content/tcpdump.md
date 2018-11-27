Title: tcpdump 的使用
Date: 2017-08-13 11:27
Category: Linux
Tags: Linux
Slug: tcpdump
Author: Chen Kai
Summary: tcpdump 是Linux下最常用的抓包与分析工具，下面对工具进行一些总结。

tcpdump 是Linux下最常用的抓包与分析工具，下面对工具进行一些总结。

### 1、基本使用
tcpdump 通常需要root 权限，所以执行命令的时候需要切换到root 用户。
### 2、使用语法
如果不加配置的使用，tcpdump 会将本机的所有数据包都抓下来，不便于分析，因此可以添加一些过滤选项，来抓取所需要的数据包。
-i 选择所需要抓取的网卡，可以通过ifconfig 来查看所有网卡，并选择所需要的，例：tcpdump -i en0 表示第一块网卡；tcpdump -i lo0 表示回环地址，当监听的地址为127.0.0.1 的时候，需要选择lo0
host 过滤主机ip；例：tcpdump -i en0 host 192.168.1.6 表示抓取所有地址为192.168.1.6 的数据。host 前还可以添加src 或者 dst 来限制源或目的地址。
port 过滤端口；例：tcpdump -i en0 host 192.168.1.6 and dst port 80 表示抓取所有地址为192.168.1.6 而且目的端口为80 的包
tcpdump 的语法支持and 和 or 还有（）操作，可以并列的使用多重选项，另外还支持协议过滤：tcpdump -i en0 tcp 表示只抓取tcp包。
因为有些时候抓包的速度很快，在终端上很快的刷新，人眼不好分析，所以有些时候需要将抓包定向到文件：tcpdump -i en0 -w a.cap 表示定向到a.cap 文件，然后通过wireshark 打开分析。数据包过多可以通过 -c 来控制抓包的个数。 tcpdump -i en0 -c 3 -w 3hand.cap

