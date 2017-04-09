#ifndef BALL_HPP_
#define BALL_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace pong
{
class Ball : public AEntity
{
public:
  Ball();
  Ball(Ball const &other) = default;
  virtual ~Ball();
  virtual void display(Map &map, double ratio = 0.0) const;
  void updatePosition(Player const &p, double time);

private:
  double m_x;
  double m_y;
  double m_speed;
  double m_dirX;
  double m_dirY;
};
}
}
}
#endif // !BALL_HPP_
