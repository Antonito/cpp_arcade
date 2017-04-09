#ifndef WINDOWERROR_HPP_
#define WINDOWERROR_HPP_

#include "AException.hpp"

namespace arcade
{
  class WindowError : public AException
  {
  public:
    WindowError(std::string const &msg = "");
  };
}

#endif // !WINDOWERROR_HPP_
