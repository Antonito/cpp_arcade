#include <cassert>
#include <iostream>
#include <sys/select.h>
#include "GameServer.hpp"

namespace arcade
{
  GameServer::GameServer(int16_t port, uint32_t maxClients) :
    m_sock(port, maxClients, Network::ASocket::SocketType::BLOCKING)
  {
    // TODO : Port 0
    std::cout << "Running server on port " <<  m_sock.getPort() << std::endl;

    // Check the max number of file descriptors that select() can handle
    if (maxClients > FD_SETSIZE)
      {
	std::cout << "[WARN] Too many possible clients" << std::endl;
      }
  }

  GameServer::~GameServer()
  {
    std::cout << "Stopping server..." << std::endl;
  }

  void	GameServer::handleIO(fd_set const &readfds)
  {
    for (GameClient const &client : m_clients)
      {
	sock_t	cur;

	cur = client.getSock();
	if (FD_ISSET(cur, &readfds))
	  {
	    // There's data to read
	  }
      }
  }

  bool GameServer::run()
  {
    assert(m_running == false);
    m_running = true;
    // TODO: Start thread
    return (true);
  }

  void GameServer::stop()
  {
    assert(m_running == true);
    m_running = false;
    // TODO: Wait end of thread
  }

  void	GameServer::_server()
  {
#if defined(DEBUG)
    std::cout << "Started server loop" << std::endl;
#endif
    while (m_running)
      {
	fd_set		readfds;
	sock_t		maxSock;
	int	        ret;
	struct timeval	tv;

	FD_ZERO(&readfds);

	// Loop over all clients
	for (GameClient const &client : m_clients)
	  {
	    sock_t cur;

	    cur = client.getSock();
	    FD_SET(cur, &readfds);
	    if (cur > maxSock)
	      maxSock = cur;
	  }

	// No Timeout
	tv.tv_usec = 0;
	tv.tv_sec = 0;

	ret = select(maxSock + 1, &readfds, NULL, NULL, &tv);
	if (ret == -1)
	  {
	    // Error
	    std::cerr << "SelectFailed: " << errno << std::endl;
	  }
	else if (ret == 0)
	  {
	    // Connection
#if defined(DEBUG)
	    std::cout << "New client requesting connection" << std::endl;
#endif
	  }
	else
	  {
	    // Handle I/O
#if defined(DEBUG)
	    std::cout << "Handling I/O operation" << std::endl;
#endif
	  }
      }
#if defined(DEBUG)
    std::cout << "Stopped server loop" << std::endl;
#endif
  }

  bool GameServer::addClient()
  {
    return (false);
  }

  bool GameServer::removeClient(Network::IClient &client)
  {
    client.disconnect();
    return (false);
  }

  bool  GameServer::isRunning() const
  {
    return (m_running);
  }
}
