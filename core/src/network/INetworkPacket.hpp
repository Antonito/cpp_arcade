#ifndef INETWORK_PACKET_HPP
#define INETWORK_PACKET_HPP

#include <cstdint>

class INetworkPacket
{
public:
  virtual void serialize(uint8_t *&data) = 0;
  virtual void deserialize(uint8_t *&data) = 0;
};

#endif // !INETWORK_PACKET_HPP
