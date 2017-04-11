#ifndef SUPERPOWERS_HPP_
#define SUPERPOWERS_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    namespace pacman
    {
      class SuperPowers : public AEntity
      {

      public:
	SuperPowers();
	SuperPowers(SuperPowers const &other) = default;
	virtual ~SuperPowers();
	virtual void display(Map &map, double ratio = 0.0) const;
      };
    }
  }
}
#endif // !SUPERPOWERS_HPP_
