#include <iostream>
#include "Player.hpp"

namespace arcade
{

Player::Player(Pos const &pos, Dir dir) : m_dir(dir)
{
    m_pos = pos;
}

Player::~Player()
{
}

void Player::move(Map &map, Dir dir)
{
    m_pos.move(dir);
}

void Player::display(Map &map) const
{
    map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Blue);
}

Dir Player::getDir() const
{
    return (m_dir);
}

Pos const &Player::getPos() const
{
    return (m_pos);
}
}