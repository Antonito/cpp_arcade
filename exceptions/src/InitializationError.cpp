#include "InitializationError.hpp"

namespace arcade
{
  InitializationError::InitializationError(std::string const &msg) : AException("InitializationError: ", msg)
  {
  }
}
