#include <cassert>
#include <algorithm>
#include <iostream>
#include "GameServer.hpp"

namespace arcade
{
  GameServer::GameServer(int16_t port, uint32_t maxClients) :
    m_fact(), m_sock(port, maxClients, Network::ASocket::SocketType::BLOCKING),
    m_running(false), m_mutex()
  {
    m_sock.openConnection();
    std::cout << "Running server on port " <<  m_sock.getPort() << std::endl;

    // Check the max number of file descriptors that select() can handle
    if (maxClients > FD_SETSIZE)
      {
	std::cout << "[WARN] Too many possible clients" << std::endl;
	maxClients = FD_SETSIZE;
      }
  }

  GameServer::~GameServer()
  {
    std::cout << "Stopping server..." << std::endl;
  }

  void	GameServer::handleIO(int max, fd_set const &readfds, fd_set const &writefds,
			     fd_set const &exceptfds)
  {
    int	i = 0;
    if (FD_ISSET(m_sock.getSocket(), &readfds))
      {
	// New Connection
#if defined(DEBUG)
	std::cout << "New connection" << std::endl;
#endif
	addClient();
	++i;
      }
    for (std::unique_ptr<GameClient> const &client : m_clients)
      {
	sock_t	cur;

	if (i >= max)
	  break;
	cur = client->getSock();
	if (FD_ISSET(cur, &readfds))
	  {
	    GameClient::ClientAction action;

	    // There's data to read
	    action = client->read();
	    if (action == GameClient::ClientAction::DISCONNECT)
	      {
		// The client asked for a disconnection
		removeClient(*client);
	      }
	    ++i;
	  }
	else if (FD_ISSET(cur, &writefds))
	  {
	    // You can write to this socket
	    client->write();
	    ++i;
	  }
	else if (FD_ISSET(cur, &exceptfds))
	  {
	    // There's an error
	    removeClient(*client);
	    ++i;
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
	fd_set		readfds, writefds, exceptfds;
	sock_t		maxSock;
	int	        ret;
	struct timeval	tv;

	do
	  {
	    FD_ZERO(&readfds);
	    FD_ZERO(&writefds);

	    // Loop over all clients
	    FD_SET(m_sock.getSocket(), &readfds);
	    maxSock = m_sock.getSocket();
	    for (std::unique_ptr<GameClient> const &client : m_clients)
	      {
		sock_t cur;

		// Check timeout
		if (client->hasTimedOut())
		  {
		    removeClient(*client);
		    continue;
		  }

		// Add to list
		cur = client->getSock();
		FD_SET(cur, &readfds);
		FD_SET(cur, &exceptfds);
		if (client->canWrite())
		  FD_SET(cur, &writefds);
		if (cur > maxSock)
		  maxSock = cur;
	      }

	    // Timeout of 5sec
	    tv.tv_usec = 0;
	    tv.tv_sec = 15;

	    ret = select(maxSock + 1, &readfds, &writefds, &exceptfds, &tv);
	  } while (ret == -1 && errno == EINTR);
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
	    handleIO(ret, readfds, writefds, exceptfds);
	  }
	else
	  {
	    // Timeout
#if defined(DEBUG)
	    std::cout << "Timed out [Connected: " << m_clients.size()<< "]" << std::endl;
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
    sockaddr_in_t	in = {};
    socklen_t		len = sizeof(in);
    int			sock;

    sock = accept(m_sock.getSocket(), reinterpret_cast<sockaddr_t *>(&in), &len);
    if (sock != -1)
      {
	m_clients.push_back(std::make_unique<GameClient>(sock));
	return (true);
      }
    return (false);
  }

  bool GameServer::removeClient(Network::IClient &client)
  {
    GameClient &gclient = dynamic_cast<GameClient &>(client);

    gclient.disconnect();
    m_clients.erase(std::remove_if(m_clients.begin(), m_clients.end(),
				   [&](std::unique_ptr<GameClient> const &e)
				   {
				     return (*e == gclient);
				   }));
    return (true);
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
