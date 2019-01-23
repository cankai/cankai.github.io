### 调度器 MPG
https://i6448038.github.io/2017/12/04/golang-concurrency-principle/
传统并发，多线程共享内存，C++ Java 等语言在多线程开发中的常规方法，Golang 也支持这种传统模式， 但Golang 通常使用另外一种方式，就是CSP 模型，也就是Golang 提倡的”不要通过共享内存来通信，要通过通信来共享内存“，

Go的CSP并发模型，是通过goroutine和channel来实现的。
go fun();来生成一个goroutine
channel <- data 来发送数据，data <- channel 来取数据。
在发送数据的时候， goroutine 都会阻塞， 直到取得或者发送数据。
Golang 使用MPG模式来实现CSP
M指的是Machine，一个M直接关联了一个内核线程。
P指的是”processor”，代表了M所需的上下文环境，也是处理用户级代码逻辑的处理器。
G指的是Goroutine，其实本质上也是一种轻量级的线程。
