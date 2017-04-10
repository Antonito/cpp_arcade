#ifndef SolarFox_HPP_
#define SolarFox_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "PowerUps.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shoot.hpp"

namespace arcade
{
namespace game
{
namespace solarfox
{
class SolarFox : public AGame
{

public:
  SolarFox();
  SolarFox(SolarFox const &other);
  ~SolarFox();

  SolarFox &operator=(SolarFox const &other);

  virtual void notifyEvent(std::vector<Event> &&events);

  virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

  virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

  virtual void process();

#if defined(__linux__)
  virtual void WhereAmI(std::ostream &) const;
#endif
private:
  void checkPowerUps();

  Player m_player;
  PowerUps m_powerups;
  Shoot m_shoot;
  std::vector<Enemy> m_enemies;
  bool m_hasShot;

  size_t m_lastTick;
  size_t m_curTick;
};
}
}
}

extern "C" void Play(void);

#endif // !SolarFox_HPP_
