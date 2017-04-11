#ifndef EVILSHOOT_HPP_
#define EVILSHOOT_HPP_

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
class EvilShoot : public AMovable
{

public:
  EvilShoot();
  EvilShoot(EvilShoot const &other) = default;
  virtual ~EvilShoot();
  virtual void display(Map &map, double ratio = 0.0) const;
  virtual void move(Map &map);

  void setCurTile(TileType);
  TileType getCurTile() const;

private:
  TileType m_curTile;
};
}
}
}
#endif // !EVILSHOOT_HPP_
