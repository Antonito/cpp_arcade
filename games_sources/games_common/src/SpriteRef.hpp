#ifndef SPRITEREF_HPP_
#define SPRITEREF_HPP_

#include <vector>
#include <cstdlib>

namespace arcade
{
  namespace game
  {
    class SpriteRef
    {
    public:
      SpriteRef(size_t id = 0);
      SpriteRef(SpriteRef const &other);
      ~SpriteRef();

      SpriteRef &operator=(SpriteRef const &other);

      int getId() const;
      size_t getPos() const;

      void next();
      void prev();

      void setId(int id);
      void setPos(size_t pos);

    private:
      static std::vector<size_t> m_spriteNbs;

      size_t m_id;
      size_t m_pos;
    };
  }
}

#endif // !SPRITEREF_HPP_