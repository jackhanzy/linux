#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include <list>
#include <string.h>
#include "socket.h"

namespace Original
{

struct ClientSession
{
public:
	ClientSession(int fd, const std::string & addr, short p)
	{
		conn_fd = fd;
		ip_addr = addr;
		port = port;
	}
	socket_t conn_fd;
	std::string ip_addr;
	short port;
};

class SocketServer
{
public:
	SocketServer();
	~SocketServer();
	static const int RECV_BUFF_SIZE = 65535;
	static const int SEND_BUFF_SIZE = 65535;
public:
	bool Init(const char* addr, short port);

	bool SendData(socket_t fd, void * data, size_t size);

	bool RecvData(socket_t fd, void * data, size_t size);
private:
	Socket * m_pSocket;

	std::list<ClientSession*> m_lstClient;

	char *m_buffRecv;
	char *m_buffSend;
};

}
#endif
