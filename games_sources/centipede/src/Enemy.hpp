#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "AEntity.hpp"
#include "Obstacle.hpp"

namespace arcade
{
class Enemy : public AEntity
{

public:
  Enemy(){};
  Enemy(Pos &pos, Dir dir, size_t tail);
  Enemy(Enemy const &other) = default;
  virtual ~Enemy();
  Enemy &operator=(Enemy const &other) = default;
  virtual bool move(Map &map);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map) const;

  void rotate(Map &map);
  bool touchObstacle(Map &Map, std::vector<Obstacle> const &obtacles);
  Dir getDir() const;
  void setDir(Dir dir);

private:
  Dir m_dir;
  std::vector<Pos> m_tail;
};
}

#endif // !ENEMY_HPP_