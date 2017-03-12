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
		// Remove it ?
	};
}

#endif // !INETWORK_H_
