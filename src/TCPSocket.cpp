#include <cerrno>
#include <cassert>
#if defined(__linux__) || defined(__APPLE__)
#include <netdb.h>
#endif
#include "TCPSocket.hpp"

namespace Network
{
	TCPSocket::TCPSocket(uint16_t port, std::string const &host, SocketType type) : ASocket(port, host, type)
	{
	}

	TCPSocket::TCPSocket(uint16_t port, uint32_t maxClients, SocketType type) : ASocket(port, maxClients, type)
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
		if (setSocketType() == false)
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

	bool		TCPSocket::sendBlocking(void const *data, size_t len) const
	{
		assert(getType() == ASocket::BLOCKING);
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

	bool		TCPSocket::sendNonBlocking(void const *data, size_t len) const
	{
		uint8_t	const	*msg = static_cast<uint8_t const *>(data);
		size_t			off = 0;
		ssize_t			ret;
		bool			success = true;

		assert(getType() == ASocket::NONBLOCKING);
		for (;;)
		{
#if defined(__linux__) || defined(__APPLE__)
			ret = ::send(m_socket, reinterpret_cast<char const *>(msg + off), len - off, 0);
#elif defined(_WIN32)
			ret = ::send(m_socket, reinterpret_cast<char const *>(msg + off), static_cast<int>(len - off), 0);
#endif
			if (ret == -1 || ret == len - off)
			{
				if (ret == -1 && errno != EWOULDBLOCK && errno != EAGAIN)
				{
					success = false;
				}
				break;
			}
			off += ret;
		}
		return (success);
	}

	bool		TCPSocket::send(void const *data, size_t len) const
	{
		assert(isStarted());
		if (getType() == ASocket::BLOCKING)
		{
			return (sendBlocking(data, len));
		}
		return (sendNonBlocking(data, len));
	}

	bool		TCPSocket::recBlocking(void **buffer, size_t rlen, ssize_t *buffLen) const
	{
		assert(getType() == ASocket::BLOCKING);
		*buffer = new uint8_t[rlen]; // TODO: Smart ptr ?
#if defined(__linux__) || defined(__APPLE__)
		*buffLen = ::recv(m_socket, static_cast<char *>(*buffer), rlen, 0);
#elif defined(_WIN32)
		*buffLen = ::recv(m_socket, static_cast<char *>(*buffer), static_cast<int>(rlen), 0);
#endif
		if (*buffLen < 0)
		{
			// TODO: Handle errno
			*buffLen = 0;
			return (false);
		}
		return (true);
	}

	bool		TCPSocket::recNonBlocking(void **buffer, size_t rlen, ssize_t *buffLen) const
	{
		ssize_t	ret;
		uint8_t *buf;
		bool	success = true;

		assert(getType() == ASocket::NONBLOCKING);
		*buffer = new uint8_t[rlen];
		buf = static_cast<uint8_t *>(*buffer);
		*buffLen = 0;
		for (;;)
		{
#if defined(__linux__) || defined(__APPLE__)
			ret = ::recv(m_socket, reinterpret_cast<char *>(buf + *buffLen), rlen - *buffLen, 0);
#elif defined(_WIN32)
			ret = ::recv(m_socket, reinterpret_cast<char *>(buf + *buffLen), static_cast<int>(rlen - *buffLen), 0);
#endif
			if (ret == -1)
			{
				if (errno != EWOULDBLOCK && errno != EAGAIN)
				{
					success = false;
				}
				break;
			}
			else if (ret == 0)
			{
				*buffLen = 0;
				break;
			}
			if (static_cast<size_t>(*buffLen + ret) >= rlen)
			{
				success = !(static_cast<size_t>(*buffLen + ret) > rlen);
				break;
			}
			*buffLen += ret;
		}
		return (success);
	}

	bool		TCPSocket::rec(void **buffer, size_t rlen, ssize_t *buffLen) const
	{
		assert(isStarted());
		if (getType() == ASocket::BLOCKING)
		{
			return (recBlocking(buffer, rlen, buffLen));
		}
		return (recNonBlocking(buffer, rlen, buffLen));
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
		m_addr.sin_addr = *reinterpret_cast<_in_addr_t *>(hostinfo->h_addr);
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
