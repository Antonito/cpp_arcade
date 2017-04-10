#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "IShooter.hpp"
#include "Shoot.hpp"
#include "AMovable.hpp"

namespace arcade
{
namespace game
{
namespace solarfox
{
class Enemy : public AMovable, public IShooter
{

public:
  Enemy();
  Enemy(Enemy const &other) = default;
  virtual ~Enemy();
  virtual void display(Map &map, double ratio = 0.0) const;
  virtual void move(Map &map);
  virtual std::unique_ptr<AEntity> shoot() const;
};
}
}
}
#endif // !ENEMY_HPP_
