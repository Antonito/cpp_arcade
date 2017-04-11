#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#if defined(__linux__) || (__APPLE__)
#include <sys/select.h>
#endif
#include "IServer.hpp"
#include "TCPSocket.hpp"
#include "GameClient.hpp"
#include "PacketFactory.hpp"

namespace arcade
{
  class GameServer : public Network::IServer
  {
  public:
    GameServer(int16_t port, uint32_t maxClients);
    GameServer(GameServer const &);
    virtual ~GameServer();

    virtual bool run();
    virtual void stop();
    virtual bool addClient();
    virtual bool removeClient(Network::IClient &client);

    std::vector<std::unique_ptr<GameClient>> const &getClients() const;

    bool isRunning() const;
    void wait();

  private:
    void _server();
    void authenticateClient(GameClient &client);
    void handleGames(std::unique_ptr<GameClient> const &client) const;
    void handleIO(int sock, fd_set const &readfds, fd_set const &writefds,
                  fd_set const &exceptfds);

    Network::PacketFactory                   m_fact;
    Network::TCPSocket                       m_sock;
    std::vector<std::unique_ptr<GameClient>> m_clients;
    std::atomic<bool>                        m_running;
    std::thread                              m_thread;
    std::mutex                               m_mutex;
  };
}

#endif // !GAMESERVER_HPP_
