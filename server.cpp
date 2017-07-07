#include "socket_server.h"
using namespace Original;

int main()
{
	SocketServer server;
	server.Init("127.0.0.1", 666);
	return 0;
}
