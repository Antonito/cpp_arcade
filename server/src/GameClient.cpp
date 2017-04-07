#include <sys/socket.h>
#include "GameClient.hpp"

namespace arcade
{
  GameClient::GameClient(sock_t socket) :
    m_sock(socket), m_buffSize(0),
    m_buff(std::make_unique<uint8_t[]>(GameClient::buffSize))
  {
  }

  GameClient::~GameClient()
  {
  }

  bool GameClient::disconnect()
  {
    return (true);
  }

  GameClient::ClientAction GameClient::read()
  {
    ssize_t ret;

    ret = recv(m_sock, m_buff.get(), GameClient::buffSize, 0);
    if (ret == -1)
      {
	return (ClientAction::FAILURE);
      }
    else if (!ret)
      {
	return (ClientAction::DISCONNECT);
      }
    m_buffSize = ret;
    return (ClientAction::SUCCESS);
  }

  bool GameClient::operator==(GameClient const &other)
  {
    return (m_sock == other.m_sock && m_buffSize == other.m_buffSize);
  }

  sock_t GameClient::getSock() const
  {
    return (m_sock);
  }
}
