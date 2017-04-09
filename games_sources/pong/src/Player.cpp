#include <cmath>
#include "Player.hpp"

namespace arcade
{
  namespace game
  {
    namespace pong
    {
      Player::Player()
      {
      }

      Player::~Player()
      {
      }

      void Player::display(Map &map, double ratio) const
      {
        for (size_t i = 0; i < m_pos.size(); ++i)
        {
          Tile &tile = map.at(1, m_pos[i].x, m_pos[i].y);

          tile.setColor(Color::White);
        }
      }

      void Player::move()
      {
        int modif = 0;

        if (m_dir == Direction::UP)
        {
          modif = -1;
        }
        else if (m_dir == Direction::DOWN)
        {
          modif = 1;
        }

        for (Position &p : m_pos)
        {
          p.y += modif;
        }
      }
    }
  }
}