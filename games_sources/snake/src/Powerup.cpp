#include <iostream>
#include "Powerup.hpp"

namespace arcade
{

Powerup::Powerup(Pos const &pos, Map &map)
{
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::POWERUP);
    m_taken = false;
    m_sprite = rand() % 4;
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
  map.at(1, m_pos.getX(), m_pos.getY()).setSprite(m_sprite);
}

void Powerup::replace(Map &map, Pos const &pos)
{
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::EMPTY);
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::POWERUP);
    m_sprite = rand() % 4;
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