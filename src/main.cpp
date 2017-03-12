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
	Network::TCPSocket	connection(12345, "127.0.0.1", true, Network::ASocket::NONBLOCKING);

	std::cout << "Connected: " << connection.openConnection() << std::endl;
#if defined(_WIN32)
	system("pause");
#else
	::read(0, (char [1]){}, 1);
#endif
	return (0);
}
