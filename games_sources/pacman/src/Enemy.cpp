#include <cmath>
#include "Enemy.hpp"

namespace arcade
{
namespace game
{
namespace pacman
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
  static_cast<void>(ratio);
  for (size_t i = 0; i < m_pos.size(); ++i)
  {
    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

    tile.setColor(Color::Blue);
  }
}

void Enemy::move(Map &map)
{
  if (m_pos.size() == 0 || !m_pos[0].inMap(map))
  {
    return;
  }
  m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
  m_pos.erase(m_pos.end() - 1);
}

void Enemy::kill()
{
  //go back home
}

void Enemy::setEatable(bool eat)
{
  m_eatable = eat;
}

void Enemy::setDead(bool dead)
{
  m_dead = dead;
}

void Enemy::setDeathTime(size_t time)
{
  m_deathTime = time;
}

bool Enemy::getEatable() const
{
  return (m_eatable);
}

bool Enemy::getDead() const
{
  return (m_dead);
}

size_t Enemy::getDeathTime() const
{
  return (m_deathTime);
}
}
}
}
