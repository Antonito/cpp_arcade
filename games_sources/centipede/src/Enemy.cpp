#include <cmath>
#include "Enemy.hpp"

namespace arcade
{
namespace game
{
namespace centipede
{
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::display(Map &map, double ratio) const
{
  //ratio = 1 / (1 + std::exp(-ratio + 1.0));
  for (size_t i = 0; i < m_pos.size(); ++i)
  {
    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

    tile.setColor(Color::Blue);
  }
}

void Enemy::move(Map &map)
{
  Direction tmpDir;

  tmpDir = m_dir;
  if (m_pos.size() == 0)
  {
    return;
  }
  if (!next().inMap(map) || map.at(0, next().x, next().y).getType() == TileType::OBSTACLE)
  {
    if (m_pos[0].y == map.getHeight() - 1)
      m_fallDir = Direction::UP;
    else if (m_pos[0].y == 0)
      m_fallDir = Direction::DOWN;
    m_dir = m_fallDir;
    m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
    m_pos.erase(m_pos.end() - 1);
    if (tmpDir == Direction::RIGHT)
      m_dir = Direction::LEFT;
    else if (tmpDir == Direction::LEFT)
      m_dir = Direction::RIGHT;
  }
  else
  {
    m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
    m_pos.erase(m_pos.end() - 1);
  }
}
}
}
}