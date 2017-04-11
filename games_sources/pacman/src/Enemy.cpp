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

    tile.setColor(Color::Red);
  }
}

void Enemy::move(Map &map)
{
  Direction tmp;
  ssize_t nb_dir;

  tmp = m_dir;
  nb_dir = 0;
  if (m_pos.size() == 0 || !m_pos[0].inMap(map))
  {
    return;
  }

  for (size_t i = 0; i < 4; i++)
  {
    m_dir = static_cast<Direction>(i);
    if (map.at(0, next().x, next().y).getType() != TileType::BLOCK)
      nb_dir += 1;
  }
  m_dir = tmp;
  while (map.at(0, next().x, next().y).getType() == TileType::BLOCK || nb_dir > 2)
  {
    if (nb_dir > 2)
    {
      if (tmp == Direction::UP || tmp == Direction::DOWN)
        m_dir = static_cast<Direction>(2 + rand() % 2);
      if (tmp == Direction::RIGHT || tmp == Direction::LEFT)
        m_dir = static_cast<Direction>(rand() % 2);
    }
    else
      m_dir = static_cast<Direction>(rand() % 4);
    nb_dir -= 1;
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