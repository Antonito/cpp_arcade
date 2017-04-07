#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <cstdlib>
#include "AEntity.hpp"

namespace arcade
{
class Obstacle : public AEntity
{

public:
  Obstacle(Map &map, bool destructible, Pos const &pos, ssize_t pv);
  Obstacle(Obstacle const &other) = default;
  virtual ~Obstacle();
  Obstacle &operator=(Obstacle const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map) const;

  ssize_t getPv() const;

private:
  ssize_t m_pv;
  bool m_destructible;
};
}

#endif // !OBSTACLE_HPP_