#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <cstdlib>
#include "AGame.hpp"

namespace arcade
{

class Centipede : public AGame
{
  enum e_dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

  struct t_pos
  {
    ssize_t x;
    ssize_t y;
  };

  struct t_centipede
  {
    std::vector<t_pos> part;
    e_dir dir;
  };

  struct t_obstacle
  {
    t_pos pos;
    ssize_t life;
  };

public:
  Centipede();
  Centipede(Centipede const &other);
  ~Centipede();

  Centipede &operator=(Centipede const &other);

  virtual void notifyEvent(std::vector<Event> &&events);

  virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

  virtual std::vector<std::unique_ptr<ISprite>> &&getSpritesToLoad() const;

  virtual void process();

  virtual WhereAmI *getWhereAmI() const;

private:
  bool touchObstacle(t_centipede const &, t_pos &);
  bool touchTarget();
  void moveCentipedes();
  void placeObstacles();
  void splitCentipede(size_t, size_t);

  std::vector<t_obstacle> m_obstacles;
  std::vector<t_centipede> m_centipedes;
  bool isShot;
  t_pos m_pos;
  t_pos m_shoot;
};
}

#endif // !CENTIPEDE_HPP_
