#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace snake
{
class Player : public AMovable
{

public:
  Player();
  Player(Player const &other) = default;
  virtual ~Player();
  virtual void display(Map &map, double ratio) const;
};
}
}
}
#endif // !PLAYER_HPP_
