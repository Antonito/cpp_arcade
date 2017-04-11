#ifndef PLAYER_HPP_
#define PLAYER_HPP_

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
namespace spaceinvader
{
class Player : public AMovable, public IShooter
{

public:
  Player();
  Player(Player const &other) = default;
  virtual ~Player();
  virtual void display(Map &map, double ratio = 0.0) const;
  virtual void move(Map &map);
  virtual std::unique_ptr<AEntity> shoot() const;
};
}
}
}
#endif // !PLAYER_HPP_
