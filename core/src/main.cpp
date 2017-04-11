#include <iostream>
#include <memory>
#include "TCPSocket.hpp"
#include "GenLibrary.hpp"
#include "Core.hpp"
#include "Logger.hpp"

int main(int ac, char **av)
{
  std::string lib;

  // Print usage
  if (ac != 2)
    {
      std::cout << "Usage: " << av[0] << " path_to_graphic_lib.so"
                << std::endl;
#if defined(_WIN32)
      system("pause");
#endif
      return (0);
    }

  lib = av[1];

  // SRAND
  srand(time(NULL));

  // Launching of the Core
  try
    {
      std::unique_ptr<arcade::Core> core = std::make_unique<arcade::Core>();
      Nope::Log::Logger::start();

#if defined(DEBUG)
      // Set the log level to DEBUG
      Nope::Log::Logger::logLevel = Nope::Log::LogLevel::LOG_DEBUG;
#else
      // Set the log level to WARNING
      Nope::Log::Logger::logLevel = Nope::Log::LogLevel::LOG_WARNING;
#endif

      core->launch(lib);
    }
  catch (std::exception e)
    {
      std::cerr << "Fatal error : " << e.what() << std::endl;
      exit(1);
    }
  return (0);
}
