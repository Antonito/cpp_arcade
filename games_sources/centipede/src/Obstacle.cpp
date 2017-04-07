#include <iostream>
#include "Obstacle.hpp"
#include "Shoot.hpp"

namespace arcade
{

Obstacle::Obstacle(Map &map, bool destructible,
                   Pos const &pos, ssize_t pv) : m_destructible(destructible), m_pv(pv)
{
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::OBSTACLE);
}

Obstacle::~Obstacle()
{
}

bool Obstacle::move(Map &map, Dir dir)
{
    return false;
}

bool Obstacle::hit(Shoot const &shoot)
{
    if (m_destructible)
    {
        if (m_pos == shoot.getPos())
        {
            m_pv -= 1;
            return true;
        }
    }
    return false;
}

void Obstacle::display(Map &map) const
{
    map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Green);
}

ssize_t Obstacle::getPv() const
{
    return (m_pv);
}
}