#include <cmath>
#include "Player.hpp"

namespace arcade
{
namespace game
{
namespace nibbler
{
Player::Player()
{
}

Player::~Player()
{
}

void Player::display(Map &map, double ratio) const
{
  Position diff;

  ratio -= 1.0;
  for (size_t i = 0; i < m_pos.size() - 1; ++i)
  {
    Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

    // Head
    if (i == 0)
    {
      diff = Position(0, 0) + m_dir;
      tile.setColor(Color::Yellow);
      tile.setSprite(4);
      tile.setSpritePos(static_cast<int>(m_dir));
    }
    // Body
    else
    {
      diff = m_pos[i] - m_pos[i + 1];
      tile.setColor(Color::Red);
      tile.setSprite(5);
    }

    tile.setShiftX(diff.x * ratio);
    tile.setShiftY(diff.y * ratio);
  }
}
}
}
}