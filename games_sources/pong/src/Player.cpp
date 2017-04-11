#include <cmath>
#include "Player.hpp"

namespace arcade
{
  namespace game
  {
    namespace pong
    {
      Player::Player() : m_mult(0)
      {
      }

      Player::~Player()
      {
      }

      void Player::display(Map &map, double ratio) const
      {
	ratio -= 1.0;

	if (ratio >= 0.0)
	  {
	    m_mult = 0;
	  }

	for (size_t i = 0; i < m_pos.size(); ++i)
	  {
	    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

	    tile.setColor(Color::White);
	    tile.setShiftY(ratio * m_mult);
	  }
      }

      void Player::move(Map &)
      {
	m_mult = 0;

	if (m_dir == Direction::UP)
	  {
	    m_mult = -1;
	  }
	else if (m_dir == Direction::DOWN)
	  {
	    m_mult = 1;
	  }

	for (Position &p : m_pos)
	  {
	    p.y += m_mult;
	  }
      }
    }
  }
}
