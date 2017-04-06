#include <iostream>
#include "Player.hpp"

namespace arcade
{

Player::Player(Pos const &pos, Dir dir, size_t tail) : m_dir(dir)
{
    m_pos = pos;
    for (size_t i = 0; i < tail; i++)
    {
        m_tail.push_back(m_pos);
    }
}

Player::~Player()
{
}

bool Player::move(Map &map, Dir dir)
{
    Pos tmpPos;

    tmpPos = m_pos;
    m_pos.move(dir);
    if (m_pos.inMap(map))
    {
        if (!eat(map))
            m_tail.pop_back();
        m_tail.insert(m_tail.begin(), tmpPos);
        return false;
    }
    else
        return true;
}

bool Player::hit(Shoot const &shoot)
{
    return false;
}

void Player::display(Map &map) const
{
    map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Blue);

    for (Pos const &p : m_tail)
    {
        map.at(1, p.getX(), p.getY()).setColor(Color::Red);
    }
}

bool Player::eat(Map &map)
{
    if (map.at(1, m_pos.getX(), m_pos.getY()).getType() == TileType::POWERUP)
        return true;
    return false;
}

bool Player::touchTail(Pos const &pos) const
{
    for (Pos const &p : m_tail)
    {
        if (pos == p)
            return true;
    }
    return false;
}

Dir Player::getDir() const
{
    return (m_dir);
}
}