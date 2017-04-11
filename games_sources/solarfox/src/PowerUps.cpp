#include "PowerUps.hpp"

namespace arcade
{
  namespace game
  {
    namespace solarfox
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
	    // tile.setSprite(m_sprite);
	  }
      }

      PowerUps::~PowerUps()
      {
      }
    }
  }
}