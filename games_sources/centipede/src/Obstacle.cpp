#include "Obstacle.hpp"

namespace arcade
{
  namespace game
  {
    namespace centipede
    {
      Obstacle::Obstacle()
      {
      }

      void Obstacle::display(Map &map, double ratio) const
      {
	static_cast<void>(ratio);
	for (Position const &p : m_pos)
	  {
	    Tile &tile = map.at(1, p.x, p.y);

	    tile.setColor(Color::Green);
	    // tile.setSprite(m_sprite);
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