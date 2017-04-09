#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <cstdlib>
#include <ostream>
#include "AGame.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace centipede
{
class Centipede : public AGame
{

public:
  Centipede();
  Centipede(Centipede const &other);
  ~Centipede();

  Centipede &operator=(Centipede const &other);

  virtual void notifyEvent(std::vector<Event> &&events);

  virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

  virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

  virtual void process();

#if defined(__linux__)
  virtual void WhereAmI(std::ostream &) const;
#endif
private:
  Position placeObstacle(Map const &map) const;
  void checkShoot();
  Player m_player;
  std::vector<Obstacle> m_obstacles;
  std::vector<Enemy> m_enemy;
  Shoot m_shoot;
  bool m_hasShot;
  size_t m_lastTick;
  size_t m_curTick;
};
}
}
}

extern "C" void Play(void);

#endif // !CENTIPEDE_HPP_
