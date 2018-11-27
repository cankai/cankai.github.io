Title: 处理xargs 带空格的文件
Date: 2018-11-05 10:15
Category: Shell
Tags: Shell, Linux, xargs
Slug: xargs
Author: Chen Kai
Summary: xargs处理带空格的文件名

需要批量处理一批文件可以使用find + xargs 来处理, 但当文件名包含有空格的时候,就好报错,因为空格会被处理为文件名的分割符符, 然后报文件不存在,可以使用print0参数来处理, print0输出的find 文件是以null 为分割, xargs 也可以通过-0, 接收处理以null 为分隔符的输入, 于是就可以正确解决了.
```shell
find . -type f -print0 | xargs -0 rm -rf
```
