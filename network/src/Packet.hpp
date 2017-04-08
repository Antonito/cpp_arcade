#ifndef _PACKET_HPP_
#define _PACKET_HPP_

#include "NetworkPacket.hpp"

namespace arcade
{
  namespace Network
  {
    ///
    /// \struct NetworkGameEvent
    /// \brief Network Game Event
    ///
    template <size_t len>
    struct NetworkGameEvent
    {
      uint32_t		buffLen = len;
      uint8_t		data[len];
    };

    ///
    /// \struct NetworkEntityEvent
    /// \brief Network Entity Event
    ///
    template <typename T>
    struct NetworkEntityEvent
    {
      struct
      {
	ssize_t	x;
	ssize_t	y;
      }		pos;
      uint8_t	dir;
      T		data;
    };

    ///
    /// \struct NetworkPlayerEvent
    /// \brief Network Player Event
    ///
    struct NetworkPlayerEvent
    {
      struct
      {
	ssize_t	x;
	ssize_t	y;
      }		pos;
      uint8_t	dir;
      size_t	life;
    };

    ///
    /// \struct NetworkPacketData
    /// \brief Network packet data
    ///
    template <size_t gameEventLen, typename EntityDataType>
    struct NetworkPacketData
    {
      NetworkPacketData() : action{}, game{}
      {
      };

      arcade::NetworkAction			action;
      union
      {
	bool					auth;
	NetworkPlayerEvent			player;
	NetworkGameEvent<gameEventLen>		game;
	NetworkEntityEvent<EntityDataType>	entity;
      };
    };
  }
}

#endif // !_PACKET_HPP
