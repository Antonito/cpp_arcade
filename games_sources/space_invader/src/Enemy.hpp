#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "AMovable.hpp"

namespace arcade
{
  namespace game
  {
    namespace spaceinvader
    {
      class Enemy : public AMovable
      {

      public:
	Enemy();
	Enemy(Enemy const &other) = default;
	virtual ~Enemy();
	virtual void display(Map &map, double ratio = 0.0) const;
	virtual void move(Map &map);
      };
    }
  }
}
#endif // !ENEMY_HPP_
