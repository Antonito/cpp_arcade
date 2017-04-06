#include "GameClient.hpp"

namespace arcade
{
  GameClient::GameClient()
  {
  }

  GameClient::~GameClient()
  {
  }

  bool GameClient::disconnect()
  {
    return (true);
  }

  sock_t GameClient::getSock() const
  {
    return (m_sock);
  }
}
