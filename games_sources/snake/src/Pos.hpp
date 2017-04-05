#ifndef POS_HPP_
#define POS_HPP_

#include <stdint.h>
#include "Map.hpp"

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
  Pos(){};
  Pos(ssize_t x, ssize_t y);
  Pos(Pos const &other) = default;
  ~Pos();
  Pos &operator=(Pos const &other) = default;
  bool operator==(Pos const &other) const;
  void move(Dir dir);
  bool inMap(Map &map);
  void setX(ssize_t);
  void setY(ssize_t);
  ssize_t getX() const;
  ssize_t getY() const;

private:
  ssize_t m_x;
  ssize_t m_y;
};
}

#endif // !POS_HPP_