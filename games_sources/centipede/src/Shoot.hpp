#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include "AEmtity.hpp"

namespace arcade
{
class Shoot : public AEntity
{

public:
  Shoot(){};
  Shoot(Pos const &pos, Dir);
  Shoot(Shoot const &other) = default;
  virtual ~Shoot();
  Shoot &operator=(Shoot const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map);

  Dir getDir() const;
  bool isShot() const;

private:
  Dir m_dir;
  bool m_shot;
};
}

#endif // !SHOOT_HPP_