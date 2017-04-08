#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <vector>
#include "Position.hpp"
#include "Map.hpp"

namespace arcade
{
namespace game
{
class AEntity
{
public:
  AEntity();
  AEntity(size_t size);
  AEntity(AEntity const &other) = default;
  virtual ~AEntity();

  AEntity &operator=(AEntity const &other) = default;

  size_t size() const;
  Position &operator[](size_t n);
  Position const &operator[](size_t n) const;
  void push(Position pos, size_t n = 1);
  bool isTouch(Position pos) const;
  virtual void display(Map &map, double ratio = 0.0) const = 0;

  void setDir(Direction dir);

  Direction getDir() const;

  Position const &last() const;

protected:
  std::vector<Position> m_pos;
  Direction m_dir;
};
}
}

#endif // !AENTITY_HPP_