#include "Mamba.h"

int main( int argc, char* argv[] )
{
    khaki::EventLoop loop;
	khaki::TcpServer server(&loop, "127.0.0.1", 9527);
	khaki::Log::getLog().setLogLevel(khaki::Log::LogLevel::E_LOG_DEBUG);
	
	server.handlerRead([](const khaki::TcpClientPtr& con){
		con->send(con->getBuf());
	});

	server.start();

	loop.loop();
	return 0;
}