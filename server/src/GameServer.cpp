#include <cassert>
#include <iostream>
#include <sys/select.h>
#include "GameServer.hpp"

namespace arcade
{
  GameServer::GameServer(int16_t port, uint32_t maxClients) :
    m_sock(port, maxClients, Network::ASocket::SocketType::BLOCKING),
    m_running(false), m_mutex()
  {
    m_sock.openConnection();
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
    if (FD_ISSET(m_sock.getSocket(), &readfds))
      {
	// New Connection
#if defined(DEBUG)
	std::cout << "New connection" << std::endl;
#endif
      }
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
    assert(m_running == false && m_thread.joinable() == false);
    m_running = true;
    m_mutex.lock();
    m_thread = std::thread(&GameServer::_server, this);
    return (true);
  }

  void GameServer::stop()
  {
    assert(m_running == true && m_thread.joinable() == true);
    m_running = false;
    m_thread.join();
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
	FD_SET(m_sock.getSocket(), &readfds);
	for (GameClient const &client : m_clients)
	  {
	    sock_t cur;

	    cur = client.getSock();
	    FD_SET(cur, &readfds);
	    if (cur > maxSock)
	      maxSock = cur;
	  }

	// Timeout of 5sec
	tv.tv_usec = 0;
	tv.tv_sec = 5;

	ret = select(maxSock + 1, &readfds, NULL, NULL, &tv);
	if (ret == -1)
	  {
	    // Error
	    std::cerr << "SelectFailed: " << errno << std::endl;
	  }
	else if (ret > 0)
	  {
	    // Handle I/O
#if defined(DEBUG)
	    std::cout << "Handling I/O operation" << std::endl;
#endif
	    handleIO(readfds);
	  }
	else
	  {
	    // Timeout
#if defined(DEBUG)
	    std::cout << "Timed out" << std::endl;
#endif
	  }
      }
    m_mutex.unlock();
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

  void GameServer::wait()
  {
    m_mutex.lock();
    m_mutex.unlock();
  }
}
