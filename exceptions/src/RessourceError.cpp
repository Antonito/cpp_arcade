#include "RessourceError.hpp"

namespace arcade
{
  RessourceError::RessourceError(std::string const &msg)
      : AException("RessourceError: ", msg)
  {
  }
}
