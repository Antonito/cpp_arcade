#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_

#include "ISocket.hpp"

namespace Network
{
	class ASocket : public ISocket
	{
	public:
		virtual ~ASocket() = 0;
		virtual bool		isStarted() const;
		virtual sock_t		getSocket() const;
		virtual uint16_t	getPort() const;
		virtual uint32_t	getMaxClients() const;
		virtual uint32_t	getCurClients() const;

	protected:
		ASocket(uint16_t port, uint32_t maxClients);
		ASocket(ASocket const &other);
		ASocket &operator=(ASocket const &);
		sock_t		m_socket;
		uint16_t	m_port;
		uint32_t	m_maxClients;
		uint32_t	m_curClients;
	};
}

#endif // !ASOCKET_HPP_
