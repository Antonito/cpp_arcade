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
  Enemy(Pos const &pos, Dir dir, size_t tail);
  Enemy(Enemy const &other) = default;
  virtual ~Enemy();
  Enemy &operator=(Enemy const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map, double ratio = 0.0) const;

  void rotate(Map &map);
  Enemy splitCentipede(Pos &pos, std::vector<Obstacle> &obstacles, Map &map);
  bool touchObstacle(Map &Map, std::vector<Obstacle> const &obtacles);
  bool touchTail(Pos &pos);
  Dir getDir() const;
  void setDir(Dir dir);
  void setTail(std::vector<Pos> const &tail);

private:
  Dir m_dir;
  std::vector<Pos> m_tail;
};
}

#endif // !ENEMY_HPP_