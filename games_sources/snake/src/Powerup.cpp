#include <iostream>
#include "Powerup.hpp"

namespace arcade
{

Powerup::Powerup(Pos const &pos, Map &map)
{
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::POWERUP);
    m_taken = false;
}

Powerup::~Powerup()
{
}

bool Powerup::move(Map &map, Dir dir)
{
    return false;
}

bool Powerup::hit(Shoot const &shoot)
{
    return false;
}

void Powerup::display(Map &map) const
{
    map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Green);
}

void Powerup::replace(Map &map, Pos const &pos)
{
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::EMPTY);
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::POWERUP);
}

void Powerup::setTaken(bool taken)
{
    m_taken = taken;
}

bool Powerup::isTaken() const
{
    return (m_taken);
}
}