#ifndef POWERUP_HPP_
#define POWERUP_HPP_

// include Pos

namespace arcade
{
class Powerup
{

public:
  Powerup(Pos &);
  Powerup(Powerup const &other);
  ~Powerup();
  Powerup &operator=(Powerup const &other);
  void place(Map &map);
  void move(Map &map);
  void destroy(Map &map);

private:
  Pos m_pos;
};
}

#endif // !POWERUP_HPP_