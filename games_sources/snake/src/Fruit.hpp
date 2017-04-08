#ifndef FRUIT_HPP_
#define FRUIT_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace snake
{
class Fruit : public AEntity
{

public:
  Fruit(Pos const &pos);
  Fruit(Fruit const &other) = default;
  virtual ~Fruit();
  virtual void display(Map &map, double ratio) const;
};
}
}
}
#endif // !FRUIT_HPP_
