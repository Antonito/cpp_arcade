#ifndef PONGPACKET_HPP_
#define PONGPACKET_HPP_

#include <cstdint>

namespace arcade
{
  namespace game
  {
    namespace pong
    {
      // Network exchanged by pong game
      struct PongPacket
      {
	struct
	{
	  int32_t	x;
	  int32_t	y;
	}		pos;
	struct
	{
	  float		x;
	  float		y;
	}		ball;
	uint8_t	id;
      };
    }
  }
}

#endif // !PONGPACKET_HPP_
