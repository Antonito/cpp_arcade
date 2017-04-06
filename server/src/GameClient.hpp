#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include "GenNetwork.hpp"
#include "IClient.hpp"

namespace arcade
{
  class GameClient : public Network::IClient
  {
  public:
    GameClient();
    virtual ~GameClient();
    virtual bool disconnect();

    sock_t getSock() const;
  private:
    sock_t	m_sock;
  };
}

#endif // !GAMECLIENT_HPP_
