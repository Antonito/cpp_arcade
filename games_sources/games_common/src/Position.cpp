#include <iostream>
#include "Position.hpp"

namespace arcade
{
namespace game
{
Position::Position() : x(0),
                       y(0)
{
}

Position::Position(ssize_t x, ssize_t y) : x(x), y(y)
{
}

Position::~Position()
{
}

bool Position::operator==(Position const &other) const
{
  return (x == other.x && y == other.y);
}

bool Position::operator!=(Position const &other) const
{
  return (!this->operator==(other));
}

Position Position::operator+(Position const &other) const
{
  return (Position(x + other.x, y + other.y));
}

Position &Position::operator+=(Position const &other)
{
  this->x += other.x;
  this->y += other.y;
  return (*this);
}

Position Position::operator-(Position const &other) const
{
  return (Position(x - other.x, y - other.y));
}

Position &Position::operator-=(Position const &other)
{
  this->x -= other.x;
  this->y -= other.y;
  return (*this);
}

Position Position::operator+(Direction dir) const
{
  Position pos(x, y);

  switch (dir)
  {
  case Direction::UP:
    pos.y -= 1;
    break;
  case Direction::DOWN:
    pos.y += 1;
    break;
  case Direction::LEFT:
    pos.x -= 1;
    break;
  case Direction::RIGHT:
    pos.x += 1;
    break;
  }
  return (pos);
}

Position &Position::operator+=(Direction dir)
{
  switch (dir)
  {
  case Direction::UP:
    this->y -= 1;
    break;
  case Direction::DOWN:
    this->y += 1;
    break;
  case Direction::LEFT:
    this->x -= 1;
    break;
  case Direction::RIGHT:
    this->x += 1;
    break;
  }
  return (*this);
}

Position Position::operator-(Direction dir) const
{
  Position pos(x, y);

  switch (dir)
  {
  case Direction::UP:
    pos.y += 1;
    break;
  case Direction::DOWN:
    pos.y -= 1;
    break;
  case Direction::LEFT:
    pos.x += 1;
    break;
  case Direction::RIGHT:
    pos.x -= 1;
    break;
  }
  return (pos);
}

Position &Position::operator-=(Direction dir)
{
  switch (dir)
  {
  case Direction::UP:
    this->y += 1;
    break;
  case Direction::DOWN:
    this->y -= 1;
    break;
  case Direction::LEFT:
    this->x += 1;
    break;
  case Direction::RIGHT:
    this->x -= 1;
    break;
  }
  return (*this);
}

bool Position::inMap(Map &map)
{
  return (x >= 0 && static_cast<size_t>(x) < map.getWidth() && y >= 0 && static_cast<size_t>(y) < map.getHeight());
}
}
}