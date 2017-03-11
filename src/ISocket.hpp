#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

#include "GenNetwork.hpp"

namespace Network
{
	class ISocket
	{
	public:
		virtual ~ISocket() {};
		virtual bool		isStarted() const = 0;
		virtual sock_t		getSocket() const = 0;
		virtual uint16_t	getPort() const = 0;
		virtual uint32_t	getMaxClients() const = 0;
		virtual uint32_t	getCurClients() const = 0;
	};
}

#endif // !ISOCKET_HPP_
