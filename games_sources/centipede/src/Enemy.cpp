#include <iostream>
#include "Enemy.hpp"
#include "Shoot.hpp"

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
    if (m_tail.size() == 0)
    {
        m_tail.pop_back();
        m_tail.insert(m_tail.begin(), tmpPos);
        return true;
    }
    return false;
}

void Enemy::rotate(Map &map)
{
    this->move(map, Dir::DOWN);
    if (m_dir == Dir::RIGHT)
    {
        m_dir = Dir::LEFT;
    }
    else if (m_dir == Dir::LEFT)
    {
        m_dir = Dir::RIGHT;
    }
}

bool Enemy::touchObstacle(Map &map, std::vector<Obstacle> const &obstacles)
{
    size_t tmp_x;
    Pos next;

    if (m_dir == Dir::RIGHT)
    {
        tmp_x = m_pos.getX() + 1;
    }
    if (m_dir == Dir::LEFT)
    {
        tmp_x = m_pos.getX() - 1;
    }
    next = Pos(tmp_x, m_pos.getY());

    if (!next.inMap(map))
    {
        return true;
    }
    for (Obstacle const &o : obstacles)
    {
        if (next == o.getPos())
            return true;
    }
    return false;
}

bool Enemy::hit(Shoot const &shoot)
{
    if (m_pos == shoot.getPos())
        return false;
    return false;
}

void Enemy::display(Map &map, double ratio) const
{
    map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Blue);

    for (Pos const &p : m_tail)
    {
        map.at(1, p.getX(), p.getY()).setColor(Color::Red);
    }
}

Enemy Enemy::splitCentipede(Pos &pos, std::vector<Obstacle> &obstacles, Map &map)
{
    size_t i;
    Enemy new_enemy(m_pos, Dir::UP, 0);

    i = 0;
    if (m_pos == pos)
    {
        std::cout << "START_TAIL" << std::endl;
        obstacles.push_back(Obstacle(map, true, m_pos, 5));
        m_pos = m_tail[0];
        m_tail.erase(m_tail.begin());
        std::cout << "START_TAIL_2" << std::endl;
        return (new_enemy);
    }
    else if (m_pos == m_tail.back())
    {
        std::cout << "END_TAIL" << std::endl;
        obstacles.push_back(Obstacle(map, true, m_tail.back(), 5));
        m_tail.erase(m_tail.begin() + m_tail.size());
        std::cout << "END_TAIL_2" << std::endl;
        return (new_enemy);
    }
    for (std::vector<Pos>::iterator it = m_tail.begin(); it != m_tail.end(); it++)
    {
        if (*it == pos)
        {
            std::cout << "POS_TAIL" << std::endl;
            obstacles.push_back(Obstacle(map, true, *it, 5));
            new_enemy = Enemy(*(it + 1), m_dir, 0);
            break;
        }
        i++;
    }
    new_enemy.setTail(std::vector<Pos>(m_tail.begin() + i + 2, m_tail.end()));
    m_tail.resize(i);
    return (new_enemy);
}

bool Enemy::touchTail(Pos &pos)
{
    if (m_pos == pos)
        return true;
    else if (m_pos == m_tail.back())
        return true;
    for (Pos const &p : m_tail)
    {
        if (p == pos)
        {
            return true;
        }
    }
    return false;
}

void Enemy::setDir(Dir dir)
{
    m_dir = dir;
}

void Enemy::setTail(std::vector<Pos> const &tail)
{
    m_tail = tail;
}

Dir Enemy::getDir() const
{
    return (m_dir);
}
}