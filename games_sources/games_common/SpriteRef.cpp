#include "SpriteRef.hpp"

namespace arcade
{
  std::vector<size_t> SpriteRef::m_spriteNbs;

  SpriteRef::SpriteRef(int id)
  {
    this->setId(id);
  }

  SpriteRef::SpriteRef(SpriteRef const &other)
  {
  }

  SpriteRef::~SpriteRef()
  {
  }

  SpriteRef &SpriteRef::operator=(SpriteRef const &other)
  {
    if (this != &other)
      {
      }
    return (*this);
  }

  int SpriteRef::getId() const
  {
    return (m_id);
  }

  size_t SpriteRef::getPos() const
  {
    return (m_pos);
  }

  void SpriteRef::next()
  {
    // If we have a sprite
    if (m_id != -1)
      {
	m_pos++;
	if (m_pos == SpriteRef::m_spriteNbs[m_id])
	  {
	    m_pos = 0;
	  }
      }
  }

  void SpriteRef::prev()
  {
    // If we have a sprite
    if (m_id != -1)
      {
	if (m_pos == 0)
	  {
	    m_pos = SpriteRef::m_spriteNbs[m_id];
	  }
	m_pos--;
      }
  }

  void SpriteRef::setId(int id)
  {
    if (m_id < 0)
      {
	m_id = -1;
      }
    else
      {
	m_id = id % SpriteRef::m_spriteNbs.size();
      }
  }

  void SpriteRef::setPos(size_t pos)
  {
    m_pos = pos % SpriteRef::m_spriteNbs[m_id];
  }
}