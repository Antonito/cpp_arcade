#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include "IServer.hpp"
#include "TCPSocket.hpp"
#include "GameClient.hpp"

namespace arcade
{
  class GameServer : public Network::IServer
  {
  public:
    GameServer(int16_t port, uint32_t maxClients);
    GameServer(GameServer const &);
    virtual ~GameServer();

    virtual bool        run();
    virtual void	stop();
    virtual bool	addClient();
    virtual bool	removeClient(Network::IClient &client);

    bool		isRunning() const;
    void		wait();
  private:
    void		_server();
    void		handleIO(fd_set const &readfds);

    Network::TCPSocket			m_sock;
    std::vector<GameClient>		m_clients;
    std::atomic<bool>			m_running;
    std::thread				m_thread;
    std::mutex				m_mutex;
  };
}

#endif // !GAMESERVER_HPP_
