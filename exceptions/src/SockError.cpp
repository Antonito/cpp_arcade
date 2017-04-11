#include "SockError.hpp"

namespace arcade
{
  namespace Network
  {
    SockError::SockError(std::string const &msg)
        : AException("SocketError: ", msg)
    {
    }
  }
}
