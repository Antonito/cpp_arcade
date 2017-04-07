#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include <cstdint>
#include <memory>
#include <chrono>
#include "GenNetwork.hpp"
#include "IClient.hpp"

namespace arcade
{
  class GameClient : public Network::IClient
  {
  public:
    static size_t constexpr buffSize = 4096;
    static size_t constexpr timeOut = 10;

    GameClient(sock_t sock);
    virtual ~GameClient();
    virtual bool disconnect();
    virtual IClient::ClientAction write();
    virtual IClient::ClientAction read();
    virtual bool hasTimedOut() const;
    bool canWrite() const;

    bool operator==(GameClient const &);
    sock_t getSock() const;
  private:
    sock_t	m_sock;
    size_t	m_buffSize;
    std::unique_ptr<uint8_t[]> m_buff;
    bool m_write;
    std::chrono::time_point<std::chrono::system_clock> m_lastActionDate;
  };
}

#endif // !GAMECLIENT_HPP_
