#include "SpriteRef.hpp"

namespace arcade
{
  namespace game
  {
    std::vector<size_t> SpriteRef::m_spriteNbs;

    SpriteRef::SpriteRef(size_t id) : m_id(id), m_pos(0)
    {
    }

    SpriteRef::SpriteRef(SpriteRef const &other)
        : m_id(other.m_id), m_pos(other.m_pos)
    {
    }

    SpriteRef::~SpriteRef()
    {
    }

    SpriteRef &SpriteRef::operator=(SpriteRef const &other)
    {
      if (this != &other)
	{
	  m_id = other.m_id;
	  m_pos = other.m_pos;
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
      if (m_id != 0)
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
      if (m_id != 0)
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
      // m_id = id % SpriteRef::m_spriteNbs.size();
      m_id = id;
    }

    void SpriteRef::setPos(size_t pos)
    {
      // m_pos = pos % SpriteRef::m_spriteNbs[m_id];
      m_pos = pos;
    }
  }
}