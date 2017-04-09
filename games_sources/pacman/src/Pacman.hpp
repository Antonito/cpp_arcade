#ifndef Pacman_HPP_
#define Pacman_HPP_

#include <cstdlib>
#include <ostream>
#include "AGame.hpp"
#include "Player.hpp"
#include "PowerUps.hpp"
#include "SuperPowers.hpp"
#include "Enemy.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace pacman
{
class Pacman : public AGame
{

public:
  Pacman();
  Pacman(Pacman const &other);
  ~Pacman();

  Pacman &operator=(Pacman const &other);

  virtual void notifyEvent(std::vector<Event> &&events);

  virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

  virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

  virtual void process();

#if defined(__linux__)
  virtual void WhereAmI(std::ostream &) const;
#endif
private:
  void checkEnemy();
  void checkPowerUps();
  void checkSuperPowers();
  void unsetSuperPowers();

  Player m_player;
  PowerUps m_powerups;
  SuperPowers m_superPowers;
  std::vector<Enemy> m_enemy;

  Direction m_nextDir;
  bool m_hasEat;
  size_t m_lastTick;
  size_t m_curTick;
  size_t m_eatTime;
};
}
}
}

extern "C" void Play(void);

#endif // !Pacman_HPP_
