#ifndef RESSOURCEERROR_HPP_
#define RESSOURCEERROR_HPP_

#include "AException.hpp"

namespace arcade
{
  class RessourceError : public AException
  {
  public:
    RessourceError(std::string const &msg = "");
  };
}

#endif // !RESSOURCEERROR_HPP_
