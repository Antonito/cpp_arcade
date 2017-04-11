#ifndef SPACEINVADER_HPP_
#define SPACEINVADER_HPP_

#include <cstdlib>
#include <ostream>
#include "AGame.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "Shoot.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace spaceinvader
{
class SpaceInvader : public AGame
{

public:
  SpaceInvader();
  SpaceInvader(SpaceInvader const &other);
  ~SpaceInvader();

  SpaceInvader &operator=(SpaceInvader const &other);

  virtual void notifyEvent(std::vector<Event> &&events);

  virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

  virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

  virtual void process();

#if defined(__linux__)
  virtual void WhereAmI(std::ostream &) const;
#endif
private:
  void checkShoot();

  Player m_player;
  std::vector<Obstacle> m_obstacles;
  Enemy m_enemy;
  Shoot m_shoot;

  bool m_hasShot;
  size_t m_lastTick;
  size_t m_lastShootTick;
  size_t m_curTick;
};
}
}
}

#if defined(__linux__)
extern "C" void Play(void);
#endif

#endif // !SPACEINVADER_HPP_
