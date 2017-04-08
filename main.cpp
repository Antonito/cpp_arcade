#include <cstddef>
#include <iostream>
#include <cstring>
#include <memory>
#include "TCPSocket.hpp"
#include "PacketFactory.hpp"

int	main()
{
  arcade::Network::PacketFactory	fact;
  uint16_t	port;

  // Ask port
  std::cout << "Port: ";
  std::cin >> port;
  std::cout << std::endl;

  arcade::Network::TCPSocket	sock(port, "localhost", false, arcade::Network::ASocket::SocketType::BLOCKING);
  std::cout << "Created socket" << std::endl;

  if (!sock.openConnection())
    {
      std::cout << "Cannot connect to server." << std::endl;
      return (EXIT_FAILURE);
    }
  std::cout << "Connected" << std::endl;

  // Authenticate
  std::unique_ptr<arcade::NetworkPacket> pck = fact.create<1, bool>(arcade::NetworkGames::PONG,
								    [&](arcade::Network::NetworkPacketData<1, bool> &p){
								      p.action = arcade::NetworkAction::HELLO_EVENT;
								      p.auth = false;
								    });
  size_t const len = sizeof(arcade::NetworkPacketHeader) + sizeof(uint32_t);
  std::unique_ptr<uint8_t[]> rawPck = std::make_unique<uint8_t[]>(len + ntohl(pck->len));
  //std::unique_ptr<uint8_t[]> rawPck(new uint8_t[len + ntohl(pck->len)]);
  std::memcpy(rawPck.get(), pck.get(), len);
  std::memcpy(reinterpret_cast<uint8_t *>(rawPck.get()) + len, pck->data, ntohl(pck->len));
  if (sock.send(rawPck.get(), len + ntohl(pck->len)) < 0)
    {
      return (EXIT_FAILURE);
    }

  bool isLogged = false;
  do
    {
      uint8_t	*data;
      ssize_t	buffSize;

      std::cout << "Reading" << std::endl;
      if (sock.rec(reinterpret_cast<void **>(&data), sizeof(arcade::Network::NetworkPacketData<0, uint8_t>) + sizeof(uint32_t) + sizeof(arcade::NetworkPacketHeader), &buffSize) < 0)
	{
	  std::cout << "Cannot read from socket" << std::endl;
	  return (EXIT_FAILURE);
	}
      delete [] data;
      if (buffSize == 0)
	{
	  std::cout << "Client Disconnected" << std::endl;
	  return (EXIT_FAILURE);
	}
      std::cout << "Read: " << buffSize << std::endl;
    } while (!isLogged);
  return (EXIT_SUCCESS);
}
