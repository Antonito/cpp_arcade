#include <cassert>
#include "TCPSocket.hpp"

namespace Network
{
	TCPSocket::TCPSocket(uint16_t port, std::string const &host) : ASocket(port, host)
	{

	}

	TCPSocket::TCPSocket(uint16_t port, uint32_t maxClients) : ASocket(port, maxClients)
	{

	}

	TCPSocket::~TCPSocket()
	{

	}

	bool		TCPSocket::openConnection()
	{
		char const	enable = 1;
		bool		ret;

		assert(!isStarted());
		m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
		if (m_socket == -1)
		{
			// TODO: Exception
		}
		if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		{
			// TODO: Exception
		}
		m_addr.sin_port = htons(m_port);
		m_addr.sin_family = AF_INET;
		if (getMode() == ASocket::SERVER)
		{
			ret = hostConnection();
		}
		else
		{
			ret = connectToHost();
		}
		return (ret && isStarted());
	}

	bool		TCPSocket::send(void const *data, size_t len)
	{
		assert(isStarted());
#if defined(__linux__) || defined(__APPLE__)
		if (::send(m_socket, static_cast<char const *>(data), len, 0) < 0)
#elif defined(_WIN32)
		if (::send(m_socket, static_cast<char const *>(data), static_cast<int>(len), 0) < 0)
#endif
		{
			// TODO: Handle errno
			return (false);
		}
		return (true);
	}

	bool		TCPSocket::rec(void **buffer, size_t rlen, ssize_t *buff_len)
	{
		assert(isStarted());
		*buffer = new uint8_t[rlen]; // TODO: Smart ptr ?
#if defined(__linux__) || defined(__APPLE__)
		*buff_len = ::recv(m_socket, static_cast<char *>(*buffer), rlen, 0);
#elif defined(_WIN32)
		*buff_len = ::recv(m_socket, static_cast<char *>(*buffer), static_cast<int>(rlen), 0);
#endif
		if (*buff_len < 0)
		{
			// TODO: Handle errno
			*buff_len = 0;
			return (false);
		}
		return (true);
	}

	bool				TCPSocket::connectToHost()
	{
		struct hostent	*hostinfo;

		assert(m_socket != -1);
		// TODO: gethostbyname is deprecated, use something else
		hostinfo = gethostbyname(m_host.c_str());
		if (!hostinfo)
		{
			// TODO: Exception, log ?
			return (false);
		}
		m_addr.sin_addr = *reinterpret_cast<in_addr_t *>(hostinfo->h_addr);
		if (connect(m_socket, reinterpret_cast<sockaddr_t *>(&m_addr), sizeof(m_addr)) == -1)
		{
			// TODO: Exception
		}
		return (true);
	}

	bool				TCPSocket::hostConnection()
	{
		assert(m_socket != -1);
		m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(m_socket, reinterpret_cast<sockaddr_t *>(&m_addr), sizeof(m_addr)) == -1)
		{
			// TODO: Exception
		}
		if (listen(m_socket, m_maxClients) == -1)
		{
			// TODO: Exception
		}
		return (true);
	}
}