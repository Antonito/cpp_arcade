#include "WindowError.hpp"

namespace arcade
{
  WindowError::WindowError(std::string const &msg) : AException("WindowError: ", msg)
  {
  }
}
