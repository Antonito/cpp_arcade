#include "PacketError.hpp"

namespace arcade
{
	namespace Network
	{
		PacketError::PacketError(std::string const &msg) : AException("PacketetError: ", msg)
		{
		}
	}
}
