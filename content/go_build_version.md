Title: Golang 动态生成版本信息
Date: 2018-11-05 14:52
Category: Golang
Tags: Golang
Author: Chen Kai
Summary: Golang 动态生成版本信息

在编译Golang 的时候, 可以通过环境变量配置版本信息.然后通过os.Getenv 来读取变量, 设置版本, 也可以通过在编译的时候通过编译参数设置版本,
```Golang
package main

import "fmt"

var Version = "Version default"

func main() {
	fmt.Println("Version is:", Version)
}
```
go run -ldflags "-X main.Version=1.5" hello.go

然后运行的时候,就可以获得版本
