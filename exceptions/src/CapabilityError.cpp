#include "CapabilityError.hpp"

namespace arcade
{
  CapabilityError::CapabilityError(std::string const &msg)
      : AException("CapabilityError: ", msg)
  {
  }
}
