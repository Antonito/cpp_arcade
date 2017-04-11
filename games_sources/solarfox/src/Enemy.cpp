#include <cmath>
#include "Enemy.hpp"

namespace arcade
{
  namespace game
  {
    namespace solarfox
    {
      Enemy::Enemy()
      {
      }

      Enemy::~Enemy()
      {
      }

      void Enemy::display(Map &map, double ratio) const
      {
	// ratio = 1 / (1 + std::exp(-ratio + 1.0));
	static_cast<void>(ratio);
	for (size_t i = 0; i < m_pos.size(); ++i)
	  {
	    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

	    tile.setColor(Color::Red);
	  }
      }

      void Enemy::move(Map &map)
      {
	if (m_pos.size() == 0 || !next().inMap(map))
	  {
	    return;
	  }
	m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
	m_pos.erase(m_pos.end() - 1);
      }

      std::unique_ptr<AEntity> Enemy::shoot() const
      {
	std::unique_ptr<EvilShoot> shoot = std::make_unique<EvilShoot>();

	shoot->push(m_pos[0] + m_shootDir);
	shoot->setDir(m_shootDir);
	return (shoot);
      }

      void Enemy::setShootDir(Direction dir)
      {
	m_shootDir = dir;
      }

      Direction Enemy::getShootDir() const
      {
	return (m_shootDir);
      }
    }
  }
}