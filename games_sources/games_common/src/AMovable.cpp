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

void AMovable::move()
{
  if (m_pos.size() == 0)
  {
    return;
  }

  std::cout << m_pos[0].x << std::endl;
  std::cout << m_pos[0].x << std::endl;
  std::cout << static_cast<int>(m_dir) << std::endl;

  m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
  m_pos.erase(m_pos.end() - 1);
}

Position AMovable::next() const
{
  return (m_pos[0] + m_dir);
}
}
}