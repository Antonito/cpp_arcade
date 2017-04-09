#include <sys/socket.h>
#include <cstring>
#include "GameClient.hpp"
#include "Packet.hpp"

namespace arcade
{
  GameClient::GameClient(sock_t socket, sockaddr_in_t const &in) :
    m_sock(socket), m_in(in), m_buffSize(0),
    m_buff(std::make_unique<uint8_t[]>(GameClient::buffSize)),
    m_write(false), m_lastActionDate(std::chrono::system_clock::from_time_t(0)),
    m_recQueue(), m_sendQueue(), m_authenticated(false), m_game(NetworkGames::NO_GAME)
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

    // Fill buffer
    std::pair<uint32_t, std::shared_ptr<uint8_t>> pair = m_sendQueue.back();

    // Send buffer
    ret = send(m_sock, pair.second.get(), pair.first, 0);
    m_lastActionDate = std::chrono::system_clock::now();
    if (ret == -1)
      {
	return (ClientAction::FAILURE);
      }
    m_sendQueue.pop();
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
    if (m_buffSize < sizeof(NetworkPacket))
      {
	return (ClientAction::FAILURE);
      }

    // Build packet
    std::shared_ptr<uint8_t> pck(new uint8_t[m_buffSize], std::default_delete<uint8_t[]>());
    std::memcpy(pck.get(), m_buff.get(), m_buffSize);
    m_recQueue.push(std::pair<uint32_t, std::shared_ptr<uint8_t>>(m_buffSize, pck));
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

  bool GameClient::hasDataToSend() const
  {
    return (!m_sendQueue.empty());
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

  void GameClient::authenticate()
  {
    m_authenticated = true;
  }

  bool GameClient::isAuthenticated() const
  {
    return (m_authenticated);
  }

  NetworkGames	GameClient::getGame() const
  {
    return (m_game);
  }

  void		GameClient::setGame(NetworkGames game)
  {
    m_game = game;
  }

  void		        GameClient::sendData(std::pair<uint32_t, std::shared_ptr<uint8_t>> const &pck)
  {
    m_sendQueue.push(pck);
  }

  std::queue<std::pair<uint32_t, std::shared_ptr<uint8_t>>>	&GameClient::getRecQueue()
  {
    return (m_recQueue);
  }
}
