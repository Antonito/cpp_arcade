#ifndef FRUIT_HPP_
#define FRUIT_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    namespace snake
    {
      class Fruit : public AEntity
      {

      public:
	Fruit();
	Fruit(Fruit const &other) = default;
	virtual ~Fruit();
	virtual void display(Map &map, double ratio = 0.0) const;
	void updateSprite();

      private:
	size_t m_sprite;
      };
    }
  }
}
#endif // !FRUIT_HPP_
