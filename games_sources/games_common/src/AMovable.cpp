#include <iostream>
#include "AMovable.hpp"

namespace arcade
{
namespace game
{
AMovable::AMovable()
{
}

AMovable::~AMovable()
{
}

void AMovable::move(Map &map)
{
  if (m_pos.size() == 0 || !m_pos[0].inMap(map))
  {
    return;
  }

  m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
  m_pos.erase(m_pos.end() - 1);
}

Position AMovable::next() const
{
  return (m_pos[0] + m_dir);
}
}
}