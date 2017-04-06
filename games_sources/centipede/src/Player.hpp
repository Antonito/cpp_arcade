#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AEntity.hpp"
#include "Shoot.hpp"
namespace arcade
{
class Player : public AEntity
{

public:
  Player(){};
  Player(Pos const &pos, Dir dir);
  Player(Player const &other) = default;
  virtual ~Player();
  Player &operator=(Player const &other) = default;
  virtual bool move(Map &map, Dir dir);
  virtual bool hit(Shoot const &shoot);
  virtual void display(Map &map) const;

  Dir getDir() const;

private:
  bool eat(Map &map);
  Dir m_dir;
};
}

#endif // !PLAYER_HPP_