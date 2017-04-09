#ifndef BALL_HPP_
#define BALL_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "Player.hpp"

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
  void updatePosition(Player const &p, size_t mapHeight, double time);
  int getBallDir() const;
  void setBallPos(Position const &p);
  void reset(Position const &p);
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
