#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include "ASocket.hpp"

namespace Network
{
	class TCPSocket : public ASocket
	{
	public:
		TCPSocket(uint16_t port, uint32_t maxClients);
		virtual ~TCPSocket();
	};
}

#endif // !TCPSOCKET_HPP_