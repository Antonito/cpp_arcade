#include <cmath>
#include "Shoot.hpp"

namespace arcade
{
  namespace game
  {
    namespace solarfox
    {
      Shoot::Shoot()
      {
      }

      Shoot::~Shoot()
      {
      }

      void Shoot::display(Map &map, double ratio) const
      {
	// ratio = 1 / (1 + std::exp(-ratio + 1.0));
	static_cast<void>(ratio);
	for (size_t i = 0; i < m_pos.size(); ++i)
	  {
	    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

	    tile.setColor(Color::Yellow);
	  }
      }

      void Shoot::move(Map &map)
      {
	m_range -= 1;
	map.at(0, m_pos[0].x, m_pos[0].y).setType(m_curTile);
	if (m_pos.size() == 0 || !next().inMap(map))
	  {
	    return;
	  }
	m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
	m_pos.erase(m_pos.end() - 1);
	m_curTile = map.at(0, m_pos[0].x, m_pos[0].y).getType();
	map.at(0, m_pos[0].x, m_pos[0].y).setType(TileType::MY_SHOOT);
      }

      void Shoot::setCurTile(TileType tile)
      {
	m_curTile = tile;
      }

      void Shoot::setRange(ssize_t range)
      {
	m_range = range;
      }

      TileType Shoot::getCurTile() const
      {
	return (m_curTile);
      }

      ssize_t Shoot::getRange() const
      {
	return (m_range);
      }
    }
  }
}