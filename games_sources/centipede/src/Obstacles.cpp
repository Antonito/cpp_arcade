#include "Obstacles.hpp"

namespace arcade
{
namespace game
{
namespace centipede
{
Obstacles::Obstacles()
{
}

void Obstacles::display(Map &map, double ratio) const
{
  for (Position const &p : m_pos)
  {
    Tile &tile = map.at(1, p.x, p.y);

    tile.setColor(Color::Green);
    // tile.setSprite(m_sprite);
  }
}

void Obstacles::hit()
{
  if (m_pv > 0)
    m_pv -= 1;
}

size_t Obstacles::getPv() const
{
  return (m_pv);
}

void Obstacles::setPv(size_t pv)
{
  m_pv = pv;
}

Obstacles::~Obstacles()
{
}
}
}
}