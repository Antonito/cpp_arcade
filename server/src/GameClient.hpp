#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include <cstdint>
#include <memory>
#include <chrono>
#include <queue>
#include "GenNetwork.hpp"
#include "IClient.hpp"
#include "NetworkPacket.hpp"

namespace arcade
{
  class GameClient : public Network::IClient
  {
  public:
    static size_t constexpr buffSize = 4096;
    static size_t constexpr timeOut = 60; // Seconds

    GameClient(sock_t sock);
    virtual ~GameClient();
    virtual bool disconnect();
    virtual IClient::ClientAction write();
    virtual IClient::ClientAction read();
    virtual bool hasTimedOut() const;
    bool canWrite() const;
    bool hasDataToSend() const;

    std::queue<std::pair<uint32_t, std::shared_ptr<uint8_t>>>	&getRecQueue();
    void		        sendData(std::pair<uint32_t, std::shared_ptr<uint8_t>> const &pck);

    NetworkGames	getGame() const;
    void		setGame(NetworkGames game);

    bool operator==(GameClient const &);
    sock_t getSock() const;
    void authenticate();
    bool isAuthenticated() const;

  private:
    sock_t	m_sock;
    size_t	m_buffSize;
    std::unique_ptr<uint8_t[]> m_buff;
    bool m_write;
    std::chrono::time_point<std::chrono::system_clock> m_lastActionDate;
    std::queue<std::pair<uint32_t, std::shared_ptr<uint8_t>>>	m_recQueue;
    std::queue<std::pair<uint32_t, std::shared_ptr<uint8_t>>>	m_sendQueue;
    bool	m_authenticated;
    NetworkGames	m_game;
  };
}

#endif // !GAMECLIENT_HPP_
