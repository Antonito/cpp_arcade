#include <iostream>
#include "TCPSocket.hpp"
#include "GenLibrary.hpp"

int		main()
{
#if 0
	GenLibrary lib("./toto.dll");

	std::function<int(char const *)> func = lib.getFunction<int(char const *)>("my_print");
	std::cout << func("Is it working ? Ret: ") << std::endl;
#endif
#if 1
	Network::TCPSocket	connection(12345, "127.0.0.1", true, Network::ASocket::NONBLOCKING);
	
#else
	Network::TCPSocket	connection(12345, 32, Network::ASocket::NONBLOCKING);
#endif

	std::cout << "Connected: " << connection.openConnection() << std::endl;
#if defined(_WIN32)
	while (1)
	{
		sockaddr_in_t csin = { 0 };
		int sinsize = sizeof(sockaddr_in_t);
		int client = accept(connection.getSocket(), reinterpret_cast<sockaddr_t *>(&csin), &sinsize);
		if (client != -1)
		{
			std::cout << "New client !" << std::endl;

			closesocket(client);
		}
	}
#else
	::read(0, (char [1]){}, 1);
#endif
	return (0);
}
