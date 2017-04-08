#include "Fruit.hpp"

namespace arcade
{
namespace game
{
namespace snake
{
Fruit::Fruit()
{
  this->updateSprite();
}

void Fruit::display(Map &map, double ratio) const
{
    for (Position const &p : m_pos)
    {
      Tile &tile = map.at(1, p.x, p.y);

      tile.setColor(Color::Green);
      tile.setSprite(m_sprite);
    }
}

void Fruit::updateSprite()
{
  m_sprite = rand() % 4;
}

Fruit::~Fruit()
{
}
}
}
}