#include <cstdlib>
#include <iostream>
#include "GameServer.hpp"

int	main(int ac, char **av)
{
  arcade::GameServer	srv(12345, 64);

  std::cout << "Arcade Game Server" << std::endl;
  return (EXIT_SUCCESS);
}
