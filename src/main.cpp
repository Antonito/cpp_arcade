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
	Network::TCPSocket	connection(12345, 5, Network::ASocket::NONBLOCKING);

	connection.openConnection();
	system("pause");
	return (0);
}
