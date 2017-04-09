#ifndef CAPABILITYERROR_HPP_
#define CAPABILITYERROR_HPP_

#include "AException.hpp"

namespace arcade
{
  class CapabilityError : public AException
  {
  public:
    CapabilityError(std::string const &msg = "");
  };
}

#endif // !CAPABILITYERROR_HPP_
