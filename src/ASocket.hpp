#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_

#include <string>
#include "ISocket.hpp"

// TODO: Add IPv4 / IPV6 selection, blocking / non-blocking selection, SSL / TLS
namespace Network
{
	class ASocket : public ISocket
	{
	public:
		enum SocketMode {SERVER, CLIENT};
		virtual			~ASocket();
		virtual bool	closeConnection();

		bool			isStarted() const;
		sock_t			getSocket() const;
		uint16_t		getPort() const;
		uint32_t		getMaxClients() const;
		uint32_t		getCurClients() const;
		enum SocketMode	getMode() const;

	protected:
		ASocket();
		ASocket(uint16_t port, std::string const &host);
		ASocket(uint16_t port, uint32_t maxClients);
		ASocket(ASocket const &other);
		ASocket &operator=(ASocket const &);

		sock_t			m_socket;
		uint16_t		m_port;
		std::string		m_host;
		uint32_t		m_maxClients;
		uint32_t		m_curClients;
		sockaddr_in_t	m_addr;

#if defined(_WIN32)
	private:
		static uint32_t	m_nbSockets;
		static bool		m_WSAInited;
		bool initWSA() const;
		void deinitWSA() const;
#endif
	};
}

#endif // !ASOCKET_HPP_
