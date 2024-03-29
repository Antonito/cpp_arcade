#include "Obstacle.hpp"

namespace arcade
{
  namespace game
  {
    namespace spaceinvader
    {
      Obstacle::Obstacle()
      {
      }

      void Obstacle::display(Map &map, double) const
      {
	for (Position const &p : m_pos)
	  {
	    Tile &tile = map.at(1, p.x, p.y);

	    tile.setColor(Color::Green);
	    tile.setSprite(3);
	  }
      }

      void Obstacle::hit()
      {
	if (m_pv > 0)
	  m_pv -= 1;
      }

      size_t Obstacle::getPv() const
      {
	return (m_pv);
      }

      void Obstacle::setPv(size_t pv)
      {
	m_pv = pv;
      }

      Obstacle::~Obstacle()
      {
      }
    }
  }
}
