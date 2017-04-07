#ifndef AMOVABLE_HPP_
#define AMOVABLE_HPP_

#include "AEntity.hpp"
#include "Position.hpp"

namespace arcade
{
  namespace game
  {
    class AMovable : public AEntity
    {
    public:
      AMovable();
      AMovable(AMovable const &other) = default;
      virtual ~AMovable();

      AMovable &operator=(AMovable const &other) = default;

      void move(Direction dir);
    };
  }
}

#endif // !AMOVABLE_HPP_