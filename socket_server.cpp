#include "socket_server.h"

#include <iostream>

namespace Original
{

SocketServer::SocketServer()
{
	m_pSocket = new Socket;
	m_buffRecv = new char[RECV_BUFF_SIZE];
	m_buffSend = new char[SEND_BUFF_SIZE];
	memset(m_buffRecv, 0, RECV_BUFF_SIZE);
	memset(m_buffSend, 0, SEND_BUFF_SIZE);
}

SocketServer::~SocketServer()
{
	delete m_pSocket;
}

bool SocketServer::Init(const char* addr, short port)
{
	if (!m_pSocket->TCPSocket())
	{
		std::cerr << "open tcp socket failed" << std::endl;
		return false;
	}
	if (!m_pSocket->Bind(addr, port))
	{
		std::cerr << "bind socket failed" << std::endl;
		return false;
	}
	if (!m_pSocket->Listen(1000))
	{
		std::cerr << "listen socket failed" << std::endl;
		return false;
	}

	std::cout << "server start" << std::endl;

	int conn_fd = 0;
	std::string ip_addr;
	short remote_port = 0;
	if (!m_pSocket->Accept(&conn_fd, &ip_addr, &remote_port))
	{
		std::cerr << "accept socket failed" << std::endl;
		return false;
	}

	//std::cout << "new connectin fd " << conn_fd << " ip address " << ip_addr << " port " << remote_port << std::endl;
	ClientSession * session = new ClientSession(conn_fd, ip_addr, remote_port);
	m_lstClient.push_back(session);

	return true;
}

}
