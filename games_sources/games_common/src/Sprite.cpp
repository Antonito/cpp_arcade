#include <sstream>
#include "Sprite.hpp"

namespace arcade
{
  namespace game
  {
    Sprite::Sprite(std::string const & path, std::string const & name,
      size_t count, std::string const & extension,
      std::string const & ascii) :
      m_path(path),
      m_name(name),
      m_extension(extension),
      m_count(count),
      m_ascii(ascii)
    {
    }

    Sprite::~Sprite()
    {
    }
    size_t Sprite::spritesCount() const
    {
      return (m_count);
    }

    std::string Sprite::getGraphicPath(size_t pos) const
    {
      std::stringstream ss;

      ss << m_path << m_name << pos << m_extension;
      return (ss.str());
    }

    char Sprite::getAscii(size_t pos) const
    {
      return (m_ascii[pos]);
    }
  }
}