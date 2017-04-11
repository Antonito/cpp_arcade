#include "AllocationError.hpp"

namespace arcade
{
  AllocationError::AllocationError(std::string const &msg)
      : AException("AllocationError: ", msg)
  {
  }
}
