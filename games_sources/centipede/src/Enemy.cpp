#include <iostream>
#include "Enemy.hpp"

namespace arcade
{

Enemy::Enemy(Pos const &pos, Dir dir, size_t tail) : m_dir(dir)
{
    m_pos = pos;
    for (size_t i = 0; i < tail; i++)
    {
        m_tail.push_back(m_pos);
    }
}

Enemy::~Enemy()
{
}

bool Enemy::move(Map &map, Dir dir)
{
    Pos tmpPos;

    tmpPos = m_pos;
    m_pos.move(dir);
    m_tail.pop_back();
    m_tail.insert(m_tail.begin(), tmpPos);
    return false;
}

void Enemy::rotate(Map &map)
{
    move(map, Dir::DOWN);
    if (m_dir == Dir::RIGHT)
    {
        m_dir = Dir::LEFT;
    }
    if (m_dir == Dir::LEFT)
    {
        m_dir = Dir::RIGHT
    }
}

bool touchObstacles(Map &map, std::vector<Obstacles> const &obstacles)
{
    size_t tmp_x;
    Pos next;

    if (m_dir == Dir::RIGHT)
        tmp_x = m_pos.getX() + 1;
    if (m_dir == Dir::LEFT)
        tmp_x = m_pos.getX() - 1;
    next = Pos(tmp_x, m_pos.getY());
    if (!next.inMap())
        return true;
    for (Obstacle const &o : obtacles)
    {
        if (next == o.getPos())
            return true;
    }
    return false;
}

bool Enemy::hit(Shoot const &shoot)
{
    return false;
}

void Enemy::display(Map &map) const
{
    map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Blue);

    for (Pos const &p : m_tail)
    {
        map.at(1, p.getX(), p.getY()).setColor(Color::Red);
    }
}

bool Enemy::eat(Map &map)
{
    if (map.at(1, m_pos.getX(), m_pos.getY()).getType() == TileType::POWERUP)
        return true;
    return false;
}

bool Enemy::touchTail(Pos const &pos) const
{
    for (Pos const &p : m_tail)
    {
        if (pos == p)
            return true;
    }
    return false;
}

Dir Enemy::getDir() const
{
    return (m_dir);
}
}