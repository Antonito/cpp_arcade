#ifndef OBSTACLES_HPP_
#define OBSTACLES_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
namespace game
{
namespace centipede
{
class Obstacles : public AEntity
{

public:
  Obstacles();
  Obstacles(Obstacles const &other) = default;
  virtual ~Obstacles();
  virtual void display(Map &map, double ratio = 0.0) const;

  void hit();
  size_t getPv() const;
  void setPv(size_t pv);

private:
  size_t m_sprite;
  size_t m_pv;
};
}
}
}
#endif // !OBSTACLES_HPP_
