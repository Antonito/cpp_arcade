#include <cstdlib>
#include <iostream>
#include "GameServer.hpp"

int	main(int ac, char **av)
{
  arcade::GameServer	srv(0, 64);
  bool			leave;

  static_cast<void>(ac);
  static_cast<void>(av);
  std::cout << "Arcade Game Server" << std::endl;
  srv.run();

  // Server's shell
  do
    {
      std::string	input;

      std::cout << "> ";
      std::cin >> input;
      if (input == "stop")
	{
	  leave = true;
	  std::cout << "Requested end of service." << std::endl;
	  srv.stop();
	}
      else if (input == "help")
	{
	  std::cout << "Available commands: stop" << std::endl;
	}
    } while (leave != true);

  srv.wait();
  return (EXIT_SUCCESS);
}
