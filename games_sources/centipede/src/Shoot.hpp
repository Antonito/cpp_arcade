#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "AMovable.hpp"

namespace arcade
{
  namespace game
  {
    namespace centipede
    {
      class Shoot : public AMovable
      {

      public:
	Shoot();
	Shoot(Shoot const &other) = default;
	virtual ~Shoot();
	virtual void display(Map &map, double ratio = 0.0) const;
	virtual void move(Map &map);

	void     setCurTile(TileType);
	TileType getCurTile() const;

      private:
	TileType m_curTile;
      };
    }
  }
}
#endif // !SHOOT_HPP_
