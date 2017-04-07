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

    m_dir = dir;
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

void Player::display(Map &map, double ratio) const
{
  Pos next = m_pos;
  size_t i = 0;

  next.move(m_dir);
  map.at(1, m_pos.getX(), m_pos.getY()).setColor(Color::Blue);
  map.at(1, m_pos.getX(), m_pos.getY()).setSprite(4);
  map.at(1, m_pos.getX(), m_pos.getY()).setShiftX((next.getX() - m_pos.getX()) * ratio);
  map.at(1, m_pos.getX(), m_pos.getY()).setShiftY((next.getY() - m_pos.getY()) * ratio);

  if (m_tail.size() > 0)
  {
    map.at(1, m_tail[0].getX(), m_tail[0].getY()).setShiftX((m_pos.getX() - m_tail[0].getX()) * ratio);
    map.at(1, m_tail[0].getX(), m_tail[0].getY()).setShiftY((m_pos.getY() - m_tail[0].getY()) * ratio);
  }

    for (Pos const &p : m_tail)
    {
      map.at(1, p.getX(), p.getY()).setColor(Color::Red);
      map.at(1, p.getX(), p.getY()).setSprite(5);
      if (i > 0)
      {
        map.at(1, p.getX(), p.getY()).setShiftX((m_tail[i - 1].getX() - p.getX()) * ratio);
        map.at(1, p.getX(), p.getY()).setShiftY((m_tail[i - 1].getY() - p.getY()) * ratio);
      }
      ++i;
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

WhereAmI * Player::getWhereAmI() const
{
  union {
    WhereAmI *w;
    uint8_t *c;
  };

  size_t size = sizeof(WhereAmI) + m_tail.size() * sizeof(Position);

  c = new uint8_t[size];

  w->type = CommandType::WHERE_AM_I;
  w->lenght = m_tail.size();

  for (size_t i = 0; i < m_tail.size(); ++i)
  {
    w->position[i].x = m_tail[i].getX();
    w->position[i].y = m_tail[i].getY();
  }
  return (w);
}

Dir Player::getDir() const
{
    return (m_dir);
}
}