#include "ASocket.hpp"

namespace Network
{
	ASocket::ASocket(uint16_t port, uint32_t maxClients) : m_socket(-1), m_port(port), m_maxClients(maxClients), m_curClients(0)
	{
	}

	ASocket::ASocket(ASocket const &other) : m_socket(other.m_socket), m_port(other.m_port), m_maxClients(other.m_maxClients), m_curClients(other.m_curClients)
	{
	}

	ASocket::~ASocket()
	{
	}

	ASocket &ASocket::operator=(ASocket const &other)
	{
		if (this != &other)
		{
			m_socket = other.m_socket;
			m_port = other.m_port;
			m_maxClients = other.m_maxClients;
			m_curClients = other.m_curClients;
		}
		return (*this);
	}

	bool		ASocket::isStarted() const
	{
		return (m_socket != -1);
	}

	sock_t ASocket::getSocket() const
	{
		return (m_socket);
	}

	uint16_t ASocket::getPort() const
	{
		return (m_port);
	}

	uint32_t ASocket::getMaxClients() const
	{
		return (m_maxClients);
	}

	uint32_t ASocket::getCurClients() const
	{
		return (m_curClients);
	}
}
}