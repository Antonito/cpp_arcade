#ifndef AMOVABLE_HPP_
#define AMOVABLE_HPP_

#include "AEntity.hpp"
#include "Position.hpp"
#include "Map.hpp"

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

      virtual void     move(Map &);
      virtual Position next() const;
    };
  }
}

#endif // !AMOVABLE_HPP_