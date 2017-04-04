#ifndef POS_HPP_
#define POS_HPP_

#include <stdint.h>

namespace arcade
{
enum class Dir : uint16_t
{
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3
};

class Pos
{

public:
  explicit Pos(ssize_t x, ssize_t y);
  Pos(Pos const &other);
  ~Pos();
  Pos &operator=(Pos const &other);
  void up();
  void down();
  void left();
  void right();
  ssize_t getX() const;
  ssize_t getY() const;

private:
  ssize_t m_x;
  ssize_t m_y;
};
}

#endif // !POS_HPP_