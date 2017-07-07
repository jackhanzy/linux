#include "socket.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/socket.h>

#include <string.h>
#include <stdlib.h>

namespace Original
{

socket_t Socket::GetSocket()
{
	return m_socket;
}

bool Socket::Socket::TCPSocket()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == m_socket)
	{
		return false;
	}
	return true;
}

bool Socket::Socket::UDPSocket()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == m_socket)
	{
		return false;
	}
	return true;
}

bool Socket::Close()
{
	if (-1 == close(m_socket))
	{
		return false;
	}
	return true;
}

bool Socket::Shutdown(int how)
{
	if(how < SHUTDOWN_RD || how > SHUTDOWN_RDWR)
	{
		return false;
	}
	if (-1 == shutdown(m_socket, how))
	{
		return false;
	}
	return true;
}

bool Socket::Connect(const char* str_addr, short port)
{
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(str_addr);
	addr.sin_port = htons(port);
	if (-1 == connect(m_socket, (sockaddr*)&addr, sizeof(sockaddr)))
	{
		if (errno != EINPROGRESS)
		{
			return false;
		}
	}
	return true;
}

bool Socket::Bind(const char* str_addr, short port)
{
	sockaddr_in sa;
	
	memset(&sa, 0, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(str_addr);
	sa.sin_port = htons(port);

	int res = bind(m_socket, (const sockaddr*)&sa, sizeof(sa));

	if (-1 == res)
	{
		return false;
	}
			
	return true;
}

bool Socket::Listen(int backlog)
{
	if (-1 == listen(m_socket, backlog))
	{
		return false;
	}
	return true;
}

bool Socket::Accept(socket_t* new_sock, std::string * remote_addr, short * remote_port)
{
	sockaddr_in sa;
	socklen_t len = sizeof(sa);
	bzero(&sa, len);

	socket_t sock = accept(m_socket, (sockaddr*)&sa, &len);
	if (-1 == sock)
	{
		return false;
	}
	*new_sock = sock;
	if (remote_addr)
	{
		char addr[20];
		inet_ntop(AF_INET, &sa.sin_addr, addr, 20);
		size_t addr_size = strlen(addr);
		remote_addr->assign(addr, addr_size);
	}
	if (remote_port)
	{
		*remote_port = ntohs(sa.sin_port);
	}
	return true;
}

bool Socket::GetSocketName(std::string& str_addr, short& port)
{
	sockaddr_in	sa;
	socklen_t len = sizeof(sockaddr);

	int res = getsockname(m_socket, (sockaddr*)&sa, &len);
	if (res == -1)
	{
		return false;
	}
	char* s = inet_ntoa(sa.sin_addr);
	str_addr.assign(s, strlen(s));
	port = ntohs(sa.sin_port);
	return true;
}

bool Socket::GetPeerName(std::string& str_addr, short& port)
{
	str_addr.clear();
	sockaddr_in	sa;
	socklen_t len = sizeof(sa);

	int res = getpeername(m_socket, (sockaddr*)&sa, &len);
	if (res == -1)
	{
		return false;
	}
	char* s = inet_ntoa(sa.sin_addr);
	str_addr.assign(s, strlen(s));
	port = ntohs(sa.sin_port);
	return true;
}

bool Socket::SetNonBlock()
{
	int flags = fcntl(m_socket, F_GETFL);
	if (-1 == flags)
	{
		return false;
	}
	if (-1 == fcntl(m_socket, F_SETFL, flags | O_NONBLOCK))
	{
		return false;
	}
	return true;
}

bool Socket::SetBolck()
{
	int flags = fcntl(m_socket, F_GETFL);
	if (-1 == flags)
	{
		return false;
	}
	if (-1 == fcntl(m_socket, F_SETFL, flags & ~O_NONBLOCK))
	{
		return false;
	}
	return true;
}

bool Socket::SetRefuseAddr()
{
	int flag = 1;

	int res = setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, 
		(const char*)&flag, sizeof(flag));
		
	if (-1 == res)
	{
		return false;
	}
	
	return true;
}

}
