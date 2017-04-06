#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "Pos.hpp"
#include "Powerup.hpp"
#include "Shoot.hpp"

namespace arcade
{
class Snake : public AGame
{

public:
  Snake();
  Snake(Snake const &other);
  ~Snake();

  Snake &operator=(Snake const &other);

  virtual void notifyEvent(std::vector<Event> &&events);

  virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

  virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

  virtual void process();

#if defined(__linux__)
  virtual WhereAmI *getWhereAmI() const;
#endif
private:
  Pos placeFood();

  Powerup m_food;
  Player m_player;
  Dir m_dir;
  size_t m_lastTick;
  size_t m_curTick;
};
}

#endif // !SNAKE_HPP_
