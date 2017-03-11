#include <iostream>
#include "GenLibrary.hpp"

int		main()
{
	GenLibrary lib("./toto.dll");

	std::function<int(char const *)> func = lib.getFunction<int(char const *)>("my_print");
	std::cout << func("Is it working ? Ret: ") << std::endl;
	system("pause");
	return (0);
}
