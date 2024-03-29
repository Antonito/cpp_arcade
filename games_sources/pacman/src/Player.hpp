#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "AMovable.hpp"

namespace arcade
{
  namespace game
  {
    namespace pacman
    {
      class Player : public AMovable
      {

      public:
	Player();
	Player(Player const &other) = default;
	virtual ~Player();
	virtual void display(Map &map, double ratio = 0.0) const;
	virtual void move(Map &map);

	void      setNextDir(Direction);
	Direction getNextDir() const;

      private:
	Direction m_nextDir;
      };
    }
  }
}
#endif // !PLAYER_HPP_
