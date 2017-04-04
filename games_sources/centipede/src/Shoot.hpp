#ifndef SHOOT_HPP_
#define SHOOT_HPP_

// include Pos

namespace arcade
{
class Shoot
{

public:
  Shoot(Pos &);
  Shoot(Shoot const &other);
  ~Shoot();
  Shoot &operator=(Shoot const &other);
  void place(Map &map);
  void move(Map &map);

private:
  Pos m_pos;
  Dir m_dir;
};
}

#endif // !SHOOT_HPP_