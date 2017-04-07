#include <iostream>
#include "Shoot.hpp"

namespace arcade
{

Shoot::Shoot(Pos const &pos, Dir dir, Map &map)
{
    m_dir = dir;
    m_pos = pos;
    map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::MY_SHOOT);
    m_shot = true;
}

Shoot::~Shoot()
{
}

bool Shoot::move(Map &map, Dir dir)
{
    if (m_shot && m_pos.inMap(map))
    {
        map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::EMPTY);
        m_pos.move(dir);
        if (m_pos.inMap(map))
            map.at(1, m_pos.getX(), m_pos.getY()).setType(TileType::MY_SHOOT);
    }
    return (false);
}

bool Shoot::hit(Shoot const &shoot)
{
    return (false);
}

bool Shoot::touchCenti(std::vector<Enemy> &centipedes, std::vector<Obstacle> &obstacles, Map &map)
{
    Enemy new_centi;
    bool ret;

    ret = false;
    for (Enemy &e : centipedes)
    {
        if (e.touchTail(m_pos))
        {
            new_centi = e.splitCentipede(m_pos, obstacles, map);
            ret = true;
        }
    }
    if (ret == true && new_centi.getDir() != Dir::UP)
        centipedes.push_back(new_centi);
    return (ret);
}

bool Shoot::touchObstacles(std::vector<Obstacle> &obstacles)
{
    for (Obstacle &o : obstacles)
    {
        if (o.hit(*this))
            return (true);
    }
    return (false);
}

void Shoot::display(Map &map) const
{
    if (m_shot)
        map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Yellow);
}

Dir Shoot::getDir() const
{
    return (m_dir);
}

bool Shoot::isShot() const
{
    return (m_shot);
}
}