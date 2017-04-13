# C++ Network Library

## Khaki
仅仅是为了学习和自己使用而写的
参考handy和muduo
还在改进中

```c
#include "../khaki.h"
#include <iostream>

int main( int argc, char* argv[] )
{
	khaki::EventLoop loop;
	khaki::TcpServer server(&loop, "127.0.0.1", 9527);

	server.handlerRead([](const khaki::TcpClientPtr& con){
		con->send(con->getBuf());
	});

	server.start();

	loop.loop();
	return 0;
}
```