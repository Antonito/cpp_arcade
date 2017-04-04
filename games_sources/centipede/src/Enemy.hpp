#ifndef ENENY_HPP_
#define ENENY_HPP_

// include Pos

namespace arcade
{
class Enemy
{

public:
  Enemy(Pos &pos, Dir dir);
  Enemy(Enemy const &other);
  ~Enemy();
  Enemy &operator=(Enemy const &other);
  void updateDir(Dir dir);
  void updatePos(Map &map);
  void move(Map &map);
  Shoot shoot() const;

private:
  Pos m_pos;
  Dir m_dir;
};
}

#endif // !ENENY_HPP_