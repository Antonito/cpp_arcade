#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace nibbler
{
class Obstacle : public AEntity
{

public:
  Obstacle();
  Obstacle(Obstacle const &other) = default;
  virtual ~Obstacle();
  virtual void display(Map &map, double ratio = 0.0) const;
};
}
}
}
#endif // !OBSTACLE_HPP_
