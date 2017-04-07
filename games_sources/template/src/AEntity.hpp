
#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <vector>
#include <cstddef>
#include <memory>
#include "Pos.hpp"
#include "Map.hpp"

namespace arcade
{
class Shoot;
class AEntity
{
public:
  AEntity();
  AEntity(AEntity const &) = default;
  virtual ~AEntity(){};
  AEntity &operator=(AEntity const &other) = default;
  virtual bool move(Map &map, Dir dir) = 0;
  virtual bool hit(Shoot const &shoot) = 0;
  virtual void display(Map &map, double ratio) const = 0;
  Pos const &getPos() const;

protected:
  Pos m_pos;
};
}

#endif // !AENTITY_HPP_
