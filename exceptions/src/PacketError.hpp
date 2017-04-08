#ifndef PACKETERROR_HPP_
#define PACKETERROR_HPP_

#include "AException.hpp"

namespace arcade
{
	namespace Network
	{
		class PacketError : public AException
		{
		public:
			PacketError(std::string const &msg = "");
		};
	}
}

#endif // !PACKETERROR_HPP_
