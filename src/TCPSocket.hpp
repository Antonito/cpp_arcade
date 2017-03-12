#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include "ASocket.hpp"

namespace Network
{
	class TCPSocket : public ASocket
	{
	public:
		TCPSocket(uint16_t port, std::string const &host);
		TCPSocket(uint16_t port, uint32_t maxClients);
		virtual ~TCPSocket();
		virtual bool		send(void const *data, size_t len);
		virtual bool		rec(void **buffer, size_t rlen, ssize_t *buff_len);
		virtual bool		openConnection();

	protected:
		virtual bool				connectToHost();
		virtual bool				hostConnection();
	};
}

#endif // !TCPSOCKET_HPP_
