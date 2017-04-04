#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// include Pos

namespace arcade
{
class Player
{

public:
  Player(Pos &);
  Player(Player const &other);
  ~Player();
  Player &operator=(Player const &other);
  void place(Map &map);
  Shoot shoot() const;
  void move(Map &map);
  void powerUp();

private:
  Pos m_pos;
  Dir m_dir;
};
}

#endif // !PLAYER_HPP_