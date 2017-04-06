#include <iostream>
#include "AEntity.hpp"
#include "Shoot.hpp"

namespace arcade
{
AEntity::AEntity()
{
}

Pos const &AEntity::getPos() const
{
    return (m_pos);
}
}