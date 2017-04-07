#include <cstdlib>
#include <iostream>
#include "GameServer.hpp"

int	main(int ac, char **av)
{
  arcade::GameServer	srv(0, 64);

  std::cout << "Arcade Game Server" << std::endl;
  srv.run();
  srv.wait();
  return (EXIT_SUCCESS);
}
