#if defined(__linux__) || defined(__APPLE__)
#include <fcntl.h>
#endif

#include <cassert>
#include "ASocket.hpp"

namespace Network
{
#if defined(_WIN32)
	uint32_t Network::ASocket::m_nbSockets = 0;
	bool Network::ASocket::m_WSAInited = false;
#endif

	ASocket::ASocket(SocketType type) : m_socket(-1), m_port(0), m_host(""), m_maxClients(0), m_curClients(0), m_addr{}, m_type(type)
	{
#if defined(_WIN32)
		// Do we need to load the network DLL ?
		if (!m_nbSockets && !initWSA())
		{
			// Unable to load the dll
			// TODO: Exception
			;
		}
		++m_nbSockets;
#endif
	}

	ASocket::ASocket(uint16_t port, std::string const &host, SocketType type) : ASocket(type)
	{
		m_port = port;
		m_host = host;
	}

	ASocket::ASocket(uint16_t port, uint32_t maxClients, SocketType type) : ASocket(type)
	{
		assert(maxClients);
		m_port = port;
		m_maxClients = maxClients;
	}

	ASocket::ASocket(ASocket const &other) : ASocket(other.m_type)
	{
		m_socket = other.m_socket;
		m_port = other.m_port;
		m_host = other.m_host;
		m_maxClients = other.m_maxClients;
		m_curClients = other.m_curClients;
		m_addr = other.m_addr;
	}

	ASocket::~ASocket()
	{
#if defined(_WIN32)
		assert(m_nbSockets);
		--m_nbSockets;
		if (!m_nbSockets)
		{
			// It is the last socket
			deinitWSA();
		}
#endif
	}

	bool	ASocket::closeConnection()
	{
		assert(m_socket != -1);
		if (!closesocket(m_socket))
		{
			m_socket = -1;
		}
		return (!isStarted());
	}

	ASocket &ASocket::operator=(ASocket const &other)
	{
		if (this != &other)
		{
			m_socket = other.m_socket;
			m_port = other.m_port;
			m_host = other.m_host;
			m_maxClients = other.m_maxClients;
			m_curClients = other.m_curClients;
			m_addr = other.m_addr;
			m_type = other.m_type;
		}
		return (*this);
	}

	bool	ASocket::isStarted() const
	{
		return (m_socket != -1);
	}

	sock_t	ASocket::getSocket() const
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

	ASocket::SocketMode	ASocket::getMode() const
	{
		if (m_maxClients != 0)
		{
			return (ASocket::SERVER);
		}
		return (ASocket::CLIENT);
	}

	ASocket::SocketType	ASocket::getType() const
	{
		return (m_type);
	}

	bool		ASocket::setSocketType() const
	{
		bool	ret;

		assert(isStarted());
#if defined(_WIN32)
		unsigned long lock = !(m_type == ASocket::BLOCKING);
		ret = ioctlsocket(m_socket, FIONBIO, &lock) == 0;
#else
		int		flags;

#if defined(O_NONBLOCK)
		flags = fcntl(m_socket, F_GETFL, 0);
		ret = false;
		if (flags >= 0)
		{
			flags = (m_type == ASocket::BLOCKING) ?
				(flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
			ret = fcntl(m_socket, F_SETFL, flags) == 0;
		}
#else
		flags = 1;
		ret = ioctl(m_socket, FIOBIO, &flags) == 0;
#endif

#endif
		return (ret);
	}

#if defined(_WIN32)
	bool ASocket::initWSA() const
	{
		WSADATA		wsa;

		assert(m_WSAInited == false);
		if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
		{
			// Initialization failed
			return (false);
		}
		m_WSAInited = true;
		return (true);
	}

	void ASocket::deinitWSA() const
	{
		assert(m_WSAInited == true);
		WSACleanup();
		m_WSAInited = false;
	}
#endif
}
