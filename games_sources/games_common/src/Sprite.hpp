#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>
#include "ISprite.hpp"

namespace arcade
{
  namespace game
  {
    class Sprite : public ISprite
    {
    public:
      explicit Sprite(std::string const &path, std::string const &name,
                      size_t count, std::string const &extentsion,
                      std::string const &ascii);
      Sprite(Sprite const &other) = default;
      virtual ~Sprite();

      Sprite &operator=(Sprite const &other) = delete;

      virtual size_t      spritesCount() const;
      virtual std::string getGraphicPath(size_t pos) const;
      virtual char getAscii(size_t pos) const;

    private:
      std::string m_path;
      std::string m_name;
      std::string m_extension;
      size_t      m_count;
      std::string m_ascii;
    };
  }
}

#endif // !SPRITE_HPP_