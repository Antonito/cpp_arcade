#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AEntity.hpp"
#include "Shoot.hpp"
#include "Protocol.hpp"

namespace arcade
{
class Player : public AEntity
{

public:
  Player(){};
  Player(Pos const &pos, Dir dir, size_t tail);
  Player(Player const &other) = default;
  virtual ~Player();
  Player &operator=(Player const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map, double ratio = 0.0) const;

  Dir getDir() const;
  bool touchTail(Pos const &pos) const;

  WhereAmI *getWhereAmI() const;

private:
  bool eat(Map &map);
  Dir m_dir;
  std::vector<Pos> m_tail;
};
}

#endif // !PLAYER_HPP_