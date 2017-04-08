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

  m_pos.insert(m_pos.begin(), m_pos[0] + m_dir);
  m_pos.erase(m_pos.end() - 1);
}
}
}