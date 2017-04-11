#ifndef ISHOOTER_HPP_
#define ISHOOTER_HPP_

#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    class IShooter
    {
    public:
      virtual ~IShooter(){};

      virtual std::unique_ptr<AEntity> shoot() const = 0;
    };
  }
}

#endif // !ISHOOTER_HPP_