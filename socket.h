#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>

namespace Original
{
typedef int socket_t;

class Socket
{
public:
	enum
	{
		SHUTDOWN_RD = 0,
		SHUTDOWN_WR = 1,
		SHUTDOWN_RDWR = 2,
	};
public:
	bool TCPSocket();
	bool UDPSocket();
	bool Close();
	bool Shutdown(int how);

	bool Connect(const char* str_addr, short port);
	bool Bind(const char* str_addr, short port);
	bool Listen(int backlog);
	bool Accept(socket_t* new_sock, std::string * remote_addr, short * remote_port);

	bool GetSocketName(std::string& str_addr, short& port);
	bool GetPeerName(std::string& str_addr, short& port);

	bool SetNonBlock();
	bool SetBolck();

	bool SetRefuseAddr();
public:
	socket_t GetSocket();
private:
	socket_t m_socket;
};
}
#endif

