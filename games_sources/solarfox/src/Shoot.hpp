#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "AMovable.hpp"

namespace arcade
{
namespace game
{
namespace solarfox
{
class Shoot : public AMovable
{

public:
  Shoot();
  Shoot(Shoot const &other) = default;
  virtual ~Shoot();
  virtual void display(Map &map, double ratio = 0.0) const;
  virtual void move(Map &map);

  void setCurTile(TileType);
  TileType getCurTile() const;
  void setRange(size_t);
  size_t getRange() const;

private:
  TileType m_curTile;
  size_t m_range;
};
}
}
}
#endif // !SHOOT_HPP_
