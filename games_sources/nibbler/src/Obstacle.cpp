#include "Obstacle.hpp"

namespace arcade
{
namespace game
{
namespace nibbler
{
Obstacle::Obstacle()
{
}

void Obstacle::display(Map &map, double ratio) const
{
  static_cast<void>(ratio);
  for (Position const &p : m_pos)
  {
    Tile &tile = map.at(1, p.x, p.y);

    tile.setColor(Color::Red);
    // tile.setSprite(m_sprite);
  }
}

Obstacle::~Obstacle()
{
}
}
}
}