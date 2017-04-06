#ifndef SHOOT_HPP_
#define SHOOT_HPP_

// include Pos

namespace arcade
{
class Shoot
{

public:
  Shoot(){};
  Shoot(Pos const &pos);
  Shoot(Shoot const &other);
  ~Shoot();
  Shoot &operator=(Shoot const &other);
  void place(Map &map);
  void move(Map &map);

  Pos getPos() const;
  Dir getDir() const;

private:
  Pos m_pos;
  Dir m_dir;
};
}

#endif // !SHOOT_HPP_