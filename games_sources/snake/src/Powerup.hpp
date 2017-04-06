#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "AEntity.hpp"
#include "Shoot.hpp"

namespace arcade
{
class Powerup : public AEntity
{

public:
  Powerup(){};
  Powerup(Pos const &pos, Map &map);
  Powerup(Powerup const &other) = default;
  virtual ~Powerup();
  Powerup &operator=(Powerup const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map) const;

  void setTaken(bool taken);
  void replace(Map &map, Pos const &pos);
  bool isTaken() const;

private:
  bool m_taken;
  size_t m_sprite;
};
}

#endif // !POWERUP_HPP_