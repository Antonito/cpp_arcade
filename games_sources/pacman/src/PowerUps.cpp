#include "PowerUps.hpp"

namespace arcade
{
  namespace game
  {
    namespace pacman
    {
      PowerUps::PowerUps()
      {
      }

      void PowerUps::display(Map &map, double ratio) const
      {
	static_cast<void>(ratio);
	for (Position const &p : m_pos)
	  {
	    Tile &tile = map.at(1, p.x, p.y);

	    tile.setColor(Color::Green);
	    tile.setSprite(3);
	  }
      }

      PowerUps::~PowerUps()
      {
      }
    }
  }
}
