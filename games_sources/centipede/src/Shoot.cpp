#include <iostream>
#include "Shoot.hpp"

namespace arcade
{

Shoot::Shoot(Pos const &pos, Map &map)
{
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::MY_SHOOT);
    m_shot = true;
}

Shoot::~Shoot()
{
}

bool Shoot::move(Map &map, Dir dir)
{
    if (shot)
    {
        map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::EMPTY);
        m_pos.move(dir);
        map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::MY_SHOOT);
    }
    return false;
}

bool Shoot::hit(Shoot const &shoot)
{
    return false;
}

void Shoot::display(Map &map) const
{
    if (shot)
        map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Yellow);
}

Dir getDir() const
{
    return (m_dir);
}

bool isShot() const
{
    return (m_shot);
}
}