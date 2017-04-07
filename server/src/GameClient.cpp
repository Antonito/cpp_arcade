#include <sys/socket.h>
#include "GameClient.hpp"

namespace arcade
{
  GameClient::GameClient(sock_t socket) :
    m_sock(socket), m_buffSize(0),
    m_buff(std::make_unique<uint8_t[]>(GameClient::buffSize)),
    m_write(false), m_lastActionDate(std::chrono::system_clock::from_time_t(0))
  {
  }

  GameClient::~GameClient()
  {
    disconnect();
  }

  bool GameClient::disconnect()
  {
    closesocket(m_sock);
    m_sock = -1;
    return (true);
  }

  GameClient::ClientAction GameClient::write()
  {
    ssize_t ret;

    ret = send(m_sock, m_buff.get(), m_buffSize, 0);
    m_lastActionDate = std::chrono::system_clock::now();
    if (ret == -1)
      {
	return (ClientAction::FAILURE);
      }
    m_write = false;
    return (ClientAction::SUCCESS);
  }

  GameClient::ClientAction GameClient::read()
  {
    ssize_t ret;

    ret = recv(m_sock, m_buff.get(), GameClient::buffSize, 0);
    m_lastActionDate = std::chrono::system_clock::now();
    if (ret == -1)
      {
	return (ClientAction::FAILURE);
      }
    else if (!ret)
      {
	return (ClientAction::DISCONNECT);
      }
    m_buffSize = ret;
    m_write = true;
    return (ClientAction::SUCCESS);
  }

  bool GameClient::hasTimedOut() const
  {
    if (m_lastActionDate == std::chrono::system_clock::from_time_t(0))
      return (false);
    size_t elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
      (std::chrono::system_clock::now() - m_lastActionDate).count();
    return (elapsed_seconds >= GameClient::timeOut);
  }

  bool GameClient::canWrite() const
  {
    return (m_write);
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
