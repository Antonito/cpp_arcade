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
    namespace blockade_local
    {
      class Player : public AMovable
      {

      public:
	Player();
	Player(Player const &other) = default;
	virtual ~Player();
	virtual void display(Map &map, double ratio = 0.0) const;

      private:
	Position m_endPos;
      };
    }
  }
}
#endif // !PLAYER_HPP_
