#include <cmath>
#include "Enemy.hpp"

namespace arcade
{
  namespace game
  {
    namespace spaceinvader
    {
      Enemy::Enemy()
      {
      }

      Enemy::~Enemy()
      {
      }

      void Enemy::display(Map &map, double) const
      {
	for (size_t i = 0; i < m_pos.size(); ++i)
	  {
	    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

	    tile.setColor(Color::Blue);
	    tile.setSprite(0);
	  }
      }

      void Enemy::move(Map &map)
      {
	Direction tmpDir;
	bool      check = true;

	tmpDir = m_dir;
	if (m_pos.size() == 0)
	  {
	    return;
	  }
	for (Position &pos : m_pos)
	  {
	    Position tmp;

	    tmp = pos + m_dir;
	    if (!tmp.inMap(map))
	      {
		check = false;
		break;
	      }
	  }
	if (check)
	  {
	    for (Position &pos : m_pos)
	      {
		pos += m_dir;
	      }
	  }
	else
	  {
	    m_dir = Direction::DOWN;
	    for (Position &pos : m_pos)
	      {
		pos += m_dir;
	      }
	    if (tmpDir == Direction::RIGHT)
	      m_dir = Direction::LEFT;
	    else if (tmpDir == Direction::LEFT)
	      m_dir = Direction::RIGHT;
	  }
      }
    }
  }
}
