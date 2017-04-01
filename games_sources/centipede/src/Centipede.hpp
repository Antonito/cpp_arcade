#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <cstdlib>
#include "AGame.hpp"

namespace arcade
{

  class Centipede : public AGame
  {
    struct t_pos
    {
      int x;
      int y;
    };

    struct t_centipede
    {
      std::vector<t_pos> part;
      e_dir              dir;
    }

    struct t_obstacle
    {
      t_pos pos;
      int   life;
    }

    enum e_dir {
      UP,
      DOWN,
      LEFT,
      RIGHT,
    };

  public:
    Centipede();
    Centipede(Centipede const &other);
    ~Centipede();

    Centipede &operator=(Centipede const &other);

    virtual void notifyEvent(std::vector<Event> &&events);

    virtual std::vector<std::pair<std::string, SoundType > > getSoundsToLoad() const;

    virtual void process();

  private:
    void moveCentipedes();
    void placeObstacles();

    std::vector<t_obstacle>  m_obstacles;
    std::vector<t_centipede> m_centipedes;
    t_pos                    m_pos;
    bool                     m_eat;
  };
}

#endif // !CENTIPEDE_HPP_
