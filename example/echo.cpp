#include "../khaki.h"
#include <iostream>

int main( int argc, char* argv[] )
{
	khaki::EventLoop loop;
	khaki::TcpServer server = khaki::TcpServer(&loop, "127.0.0.1", 9527);
	server.handlerRead([](const khaki::TcpClientPtr& con){
		con->send(con->getBuf());
	});
	server.start();

	loop.loop();
	return 0;
}