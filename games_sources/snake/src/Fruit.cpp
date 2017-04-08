#include "Fruit.hpp"

namespace arcade
{
namespace game
{
namespace snake
{
Fruit::Fruit(Pos const &pos)
{
}

void display(Map &map, double ratio) const
{
    for (Pos const &p : m_pos)
    {
        map->at(1, p.x, p.y).setColor(Color::Green);
    }
}
}
}
}