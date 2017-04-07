#include <iostream>
#include "Player.hpp"
#include "Shoot.hpp"

namespace arcade
{

Player::Player(Pos const &pos, Dir dir) : m_dir(dir)
{
    m_pos = pos;
}

Player::~Player()
{
}

bool Player::move(Map &map, Dir dir)
{
    m_pos.move(dir);
    return true;
}

bool Player::hit(Shoot const &shoot)
{
    return false;
}

Shoot Player::shoot(Map &map) const
{
    Pos shoot_pos;

    shoot_pos = m_pos;
    shoot_pos.move(m_dir);

    return (Shoot(shoot_pos, m_dir, map));
}

void Player::display(Map &map, double ratio) const
{
    //map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Blue);
    map.at(1, m_pos.getX(), m_pos.getY()).setSprite(0);
}

Dir Player::getDir() const
{
    return (m_dir);
}
}