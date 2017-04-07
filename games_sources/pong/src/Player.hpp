#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <cstddef>
#include <memory>
#include "Pos.hpp"
#include "Map.hpp"

namespace arcade
{
class Player
{

public:
  Player(){};
  Player(Pos const &pos, Dir dir);
  Player(Player const &other) = default;
  ~Player();
  Player &operator=(Player const &other) = default;
  void move(Map &map, Dir dir);
  void display(Map &map) const;

  Dir getDir() const;
  Pos const &getPos() const;

private:
  Pos m_pos;
  Dir m_dir;
};
}

#endif // !PLAYER_HPP_