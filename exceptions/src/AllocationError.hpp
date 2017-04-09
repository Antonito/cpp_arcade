#ifndef ALLOCATIONERROR_HPP_
#define ALLOCATIONERROR_HPP_

#include "AException.hpp"

namespace arcade
{
  class AllocationError : public AException
  {
  public:
    AllocationError(std::string const &msg = "");
  };
}

#endif // !ALLOCATIONERROR_HPP_
