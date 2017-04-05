#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <cstdlib>
#include "AGame.hpp"

namespace arcade
{
class Snake : public AGame
{
  struct t_pos
  {
    ssize_t x;
    ssize_t y;
  };

  enum e_dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

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
  bool isDead(t_pos const &) const;
  bool onSnake(t_pos const &) const;
  void didEat();
  void placeFood();

  t_pos m_food;
  std::vector<t_pos> m_pos;
  e_dir m_dir;
  bool m_eat;
  size_t m_lastTick;
  size_t m_curTick;
};
}

#endif // !SNAKE_HPP_
