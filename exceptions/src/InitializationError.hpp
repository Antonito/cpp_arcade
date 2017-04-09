#ifndef INITIALIZATIONERROR_HPP_
#define INITIALIZATIONERROR_HPP_

#include "AException.hpp"

namespace arcade
{
  class InitializationError : public AException
  {
  public:
    InitializationError(std::string const &msg = "");
  };
}

#endif // !INITIALIZATIONERROR_HPP_
