#include "AEntity.hpp"

namespace arcade
{
namespace game
{
AEntity::AEntity() : m_dir(Direction::LEFT)
{
}

AEntity::AEntity(size_t size)
{
  m_pos.insert(m_pos.begin(), size, Position());
}

AEntity::~AEntity()
{
}

size_t AEntity::size() const
{
  return (m_pos.size());
}

Position &AEntity::operator[](size_t n)
{
  return (m_pos[n]);
}

void AEntity::push(Position pos, size_t n)
{
  for (size_t i = 0; i < n; ++i)
  {
    m_pos.push_back(pos);
  }
}

bool AEntity::isTouch(Position pos) const
{
  for (Position const &p : m_pos)
  {
    if (p == pos)
    {
      return (true);
    }
  }
  return (false);
}

void AEntity::setDir(Direction dir) a
{
  m_dir = dir;
}

Direction AEntity::getDir() const;
{
  return (m_dir);
}
}
}