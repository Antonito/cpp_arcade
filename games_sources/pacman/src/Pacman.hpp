#ifndef Pacman_HPP_
#define Pacman_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "PowerUps.hpp"
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
  virtual WhereAmI *getWhereAmI() const;
#endif
private:
  Player m_player;
  PowerUps m_powerups;
  std::vector<Enemy> m_enemy;

  Direction m_nextDir;
  size_t m_lastTick;
  size_t m_curTick;
};
}
}
}

extern "C" void Play(void);

#endif // !Pacman_HPP_
