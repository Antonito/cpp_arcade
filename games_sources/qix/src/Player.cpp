#include <cmath>
#include "Player.hpp"

namespace arcade
{
namespace game
{
namespace qix
{
Player::Player()
{
}

Player::~Player()
{
}

void Player::display(Map &map, double ratio) const
{
  //ratio = 1 / (1 + std::exp(-ratio + 1.0));
  static_cast<void>(ratio);
  for (size_t i = 0; i < m_pos.size(); ++i)
  {
    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

    tile.setColor(Color::Red);
  }
}

void Player::move(Map &map)
{
  if (m_pos.size() == 0 || !next().inMap(map) || map.at(0, next().x, next().y).getType() == TileType::OBSTACLE || map.at(0, next().x, next().y).getType() == TileType::BLOCK)
  {
    return;
  }
  m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
  m_pos.erase(m_pos.end() - 1);
}
}
}
}