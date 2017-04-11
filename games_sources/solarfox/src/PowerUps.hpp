#ifndef POWERUPS_HPP_
#define POWERUPS_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace solarfox
{
class PowerUps : public AEntity
{

public:
  PowerUps();
  PowerUps(PowerUps const &other) = default;
  virtual ~PowerUps();
  virtual void display(Map &map, double ratio = 0.0) const;
};
}
}
}
#endif // !POWERUPS_HPP_
