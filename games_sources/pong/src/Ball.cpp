#include <cmath>
#include "Ball.hpp"

namespace arcade
{
namespace game
{
namespace snake
{
Ball::Ball()
{
  m_dirX = static_cast<double>(rand() % 2000 - 1000) / 1000.0;
  if (m_dirX < 0.0 && m_dirX > -0.4)
  {
    m_dirX = -0.4;
  }
  else if (m_dirX > 0.0 && m_dirX < 0.4)
  {
    m_dirX = 0.4;
  }
  m_dirY = 1.0;

  double norm = std::sqrt(m_dirX * m_dirX + 1.0);

  m_dirX /= norm;
  m_dirY /= norm;
  m_speed = 10.0;
}

void Ball::display(Map &map, double ratio) const
{
    for (Position const &p : m_pos)
    {
      Tile &tile = map.at(1, p.x, p.y);

      tile.setColor(Color::Green);
      tile.setSprite(m_sprite);
    }
}

void arcade::game::pong::Ball::updatePosition(Player const &p, double time)
{
  double x = m_dirX * m_speed * time;
  double y = m_dirY * m_speed * time;

  // Player 1
  if (m_dirX < 0.0)
  {
    if (x < p[0].x + 1 && y > p[0].y - 1 && y < p.last().y + 1)
    {
      m_dirX *= -1;
      m_x = 2 * p[0].x + 1 - x;
    }
  }
  // Player 2
  else
  {
    if (x > p[0].x && y > p[0].y - 1 && y < p.last().y + 1)
    {
      m_dirX *= -1;
      m_x = 2 * p[1].x - x;
    }
  }
  m_pos[0].x = static_cast<ssize_t>(m_x + 0.5);
  m_pos[0].y = static_cast<ssize_t>(m_y + 0.5);
}

Ball::~Ball()
{
}
}
}
}