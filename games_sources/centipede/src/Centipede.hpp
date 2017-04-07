#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Pos.hpp"
#include "Shoot.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Pos.hpp"

namespace arcade
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

  virtual WhereAmI *getWhereAmI() const;

private:
  void placeObstacles();

  std::vector<Obstacle> m_obstacles;
  std::vector<Enemy> m_centipedes;
  Player m_player;
  Shoot m_shoot;
  bool isShot;

  size_t m_lastTickPlayer;
  size_t m_lastTickCenti;
  size_t m_lastTickShoot;
  size_t m_curTick;
};
}

#endif // !CENTIPEDE_HPP_
