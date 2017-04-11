#include <cmath>
#include <iostream>
#include "Ball.hpp"

namespace arcade
{
namespace game
{
namespace pong
{
Ball::Ball()
{
  m_pos.push_back(Position(0, 0));
  this->reset(Position(0, 0));
}

Ball::~Ball()
{
}

void Ball::display(Map &map, double ratio) const
{
  Tile &tile = map.at(1, m_pos[0].x, m_pos[0].y);

  tile.setColor(Color::White);

  double tmp;

  if (m_x + 0.5 > 0.0)
    tile.setShiftX(std::modf(m_x + 0.5, &tmp));
  else
    tile.setShiftX(-std::modf(-m_x - 0.5, &tmp));
  if (m_y + 0.5 > 0.0)
    tile.setShiftY(std::modf(m_y + 0.5, &tmp));
  else
    tile.setShiftY(-std::modf(-m_y - 0.5, &tmp));
}
void arcade::game::pong::Ball::updatePosition(Player const &p, size_t mapHeight, double time)
{
  m_x = m_x + m_dirX * m_speed * time;
  m_y = m_y + m_dirY * m_speed * time;

  if (m_y < 0.0)
  {
    m_y = -m_y;
    m_dirY *= -1;
  }
  else if (m_y > mapHeight - 1)
  {
    m_y = 2 * (mapHeight - 1) - m_y;
    m_dirY *= -1;
  }

  // Player 1
  if (m_dirX < 0.0)
  {
    if (m_x < p[0].x + 1 && m_y > p[0].y - 1 && m_y < p.last().y + 1)
    {
      m_dirX *= -1;
      m_x = 2 * p[0].x + 1 - m_x;
    }
  }
  // Player 2
  else
  {
    if (m_x > p[0].x - 1 && m_y > p[0].y - 1 && m_y < p.last().y + 1)
    {
      m_dirX *= -1;
      m_x = 2 * (p[1].x + 1) - m_x;
    }
  }
  m_pos[0].x = static_cast<ssize_t>(m_x + 0.5);
  m_pos[0].y = static_cast<ssize_t>(m_y + 0.5);
}

int arcade::game::pong::Ball::getBallDir() const
{
  return (m_dirX < 0.0 ? 0 : 1);
}

void Ball::setBallPos(Position const & p)
{
  if (m_pos.size() == 0)
    m_pos.push_back(p);
  else
    m_pos[0] = p;
  m_x = p.x;
  m_y = p.y;
}
void Ball::reset(Position const &p)
{
  m_dirX = (1 % 2 ? 1.0 : -1.0);
  m_dirY = static_cast<double>(1 % 600 + 400) / 1000.0 * (1 % 2 ? 1 : -1);

  double norm = std::sqrt(1.0 + m_dirY * m_dirY);

  m_dirX /= norm;
  m_dirY /= norm;
  m_speed = 18.0;
  m_pos[0] = p;
  m_x = p.x;
  m_y = p.y;
}
  double Ball::getX() const
  {
    return (m_x);
  }

  double Ball::getY() const
  {
    return (m_y);
  }

  void Ball::setX(double x)
  {
    m_x = x;
  }

  void Ball::setY(double y)
  {
    m_y = y;
  }
}
}
}
