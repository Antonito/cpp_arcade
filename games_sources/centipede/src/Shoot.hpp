#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include "AEntity.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"

namespace arcade
{
class Shoot : public AEntity
{

public:
  Shoot(){};
  Shoot(Pos const &pos, Dir dir, Map &map);
  Shoot(Shoot const &other) = default;
  virtual ~Shoot();
  Shoot &operator=(Shoot const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map) const;

  bool touchCenti(std::vector<Enemy> &centipedes, std::vector<Obstacle> &obstacles, Map &map);
  bool touchObstacles(std::vector<Obstacle> &obstacles);
  Dir getDir() const;
  bool isShot() const;

private:
  Dir m_dir;
  bool m_shot;
};
}

#endif // !SHOOT_HPP_