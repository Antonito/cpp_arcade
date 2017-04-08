#include <cmath>
#include "Player.hpp"

namespace arcade
{
namespace game
{
namespace snake
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
    for (size_t i = 1; i < m_pos.size(); ++i)
    {
      Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);
      Position diff = m_pos[i - 1] - m_pos[i];

      tile.setColor(Color::Red);
      tile.setSprite(5);
      tile.setShiftX(diff.x * ratio);
      tile.setShiftY(diff.y * ratio);
    }
    Tile &head = map.at(1, m_pos[0].x, m_pos[0].y);
    Position diff = Position(0, 0) + m_dir;

    head.setColor(Color::Yellow);
    head.setSprite(4);
    head.setShiftX(diff.x * ratio);
    head.setShiftY(diff.y * ratio);
}
}
}
}