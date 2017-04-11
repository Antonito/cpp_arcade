#include <cstdlib>
#include <iostream>
#include "GameServer.hpp"

int	main(int ac, char **av)
{
  arcade::GameServer	srv(0, 64);
  bool			leave = false;

  static_cast<void>(ac);
  static_cast<void>(av);
  std::cout << "Arcade Game Server" << std::endl;
  srv.run();

  // Server's shell
  do
    {
      std::string	input;

      std::cout << "> ";
      std::getline(std::cin, input);
      if (input == "stop")
	{
	  leave = true;
	  std::cout << "Requested end of service." << std::endl;
	  srv.stop();
	}
      else if (input == "list clients")
	{
	  std::vector<std::unique_ptr<arcade::GameClient>> const &clients = srv.getClients();
	  std::cout << clients.size() << " clients" << std::endl;
	  for (std::unique_ptr<arcade::GameClient> const &client : clients)
	    {
	      // TODO: Print client informations (ip ?)
	      static_cast<void>(client);
	    }
	}
      else if (input == "help")
	{
	  std::cout << "Available commands: stop | list clients" << std::endl;
	}
    } while (leave != true);

  srv.wait();
  return (EXIT_SUCCESS);
}
