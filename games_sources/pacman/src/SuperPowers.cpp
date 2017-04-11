#include "SuperPowers.hpp"

namespace arcade
{
namespace game
{
namespace pacman
{
SuperPowers::SuperPowers()
{
}

void SuperPowers::display(Map &map, double ratio) const
{
  static_cast<void>(ratio);
  for (Position const &p : m_pos)
  {
    Tile &tile = map.at(1, p.x, p.y);

    tile.setColor(Color::Yellow);
    // tile.setSprite(m_sprite);
  }
}

SuperPowers::~SuperPowers()
{
}
}
}
}