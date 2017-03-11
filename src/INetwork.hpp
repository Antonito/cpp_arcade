#ifndef INETWORK_H_
#define INETWORK_H_

#include <cstdint>

// TODO: TCP only right now, later UDP
namespace Network
{
	class INetwork
	{
	public:
		virtual ~INetwork() {};
		// Create Host
		// Create Client
		virtual bool sendPacket(uint8_t const *buff, size_t len) = 0;
		virtual bool readPacket() = 0;
	};
}

#endif // !INETWORK_H_
