#include <iostream>
#include "TCPSocket.hpp"
#include "GenLibrary.hpp"
#include "Core.hpp"
#include "Logger.hpp"

int		main()
{
	// Test of the dynamic library (.so or .dll)
#if 0
	GenLibrary lib("./toto.dll");

	std::function<int(char const *)> func = lib.getFunction<int(char const *)>("my_print");
	std::cout << func("Is it working ? Ret: ") << std::endl;
#endif

	// Test of the network
#if 0
#if 1
	arcade::Network::TCPSocket	connection(12345, "127.0.0.1", true, arcade::Network::ASocket::BLOCKING);
#else
	Network::TCPSocket	connection(12345, 32, Network::ASocket::BLOCKING);
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
#endif

	//Launching of the Core
	arcade::Core core;
	Nope::Log::Logger::start();

	core.launch();
	return (0);
}
