#include <cmath>
#include "Player.hpp"

namespace arcade
{
namespace game
{
namespace centipede
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
  for (size_t i = 0; i < m_pos.size(); ++i)
  {
    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

    tile.setColor(Color::Yellow);
  }
}

void Player::move(Map &map)
{
  map.at(0, m_pos[0].x, m_pos[0].y).setType(TileType::EMPTY);
  if (m_pos.size() == 0 || !next().inMap(map))
  {
    return;
  }
  m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
  map.at(0, m_pos[0].x, m_pos[0].y).setType(TileType::MY_SHOOT);
  m_pos.erase(m_pos.end() - 1);
}
}
}
}