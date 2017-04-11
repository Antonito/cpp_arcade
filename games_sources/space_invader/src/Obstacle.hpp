#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace spaceinvader
{
class Obstacle : public AEntity
{

public:
  Obstacle();
  Obstacle(Obstacle const &other) = default;
  virtual ~Obstacle();
  virtual void display(Map &map, double ratio = 0.0) const;

  void hit();
  size_t getPv() const;
  void setPv(size_t pv);

private:
  size_t m_pv;
};
}
}
}
#endif // !OBSTACLE_HPP_
