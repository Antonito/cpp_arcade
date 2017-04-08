#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <cstdlib>
#include "AGame.hpp"

namespace arcade
{
namespace game
{
namespace snake
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
  Player m_player;
  Fruit m_fruit;
  Direction m_tmpDir;
  size_t m_lastTick;
  size_t m_curTick;
};
}
}
}

extern "C" void Play(void);

#endif // !SNAKE_HPP_
