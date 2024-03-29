#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>
#include <memory>
#include <cstdlib>
#include "Tile.hpp"

namespace arcade
{
  namespace game
  {
    class Layer
    {
    public:
      explicit Layer(size_t width, size_t height);
      Layer(Layer const &other);
      Layer(Layer &&other);
      virtual ~Layer();

      Layer &operator=(Layer const &other);
      Layer &operator=(Layer &&other);

      virtual size_t getWidth() const;
      virtual size_t getHeight() const;

      Tile &at(size_t x, size_t y);
      Tile const &at(size_t x, size_t y) const;

      void clear(Color color);
      void clear(Color color, size_t sprite);

    private:
      std::vector<Tile> m_tiles;
      size_t            m_width;
      size_t            m_height;
    };
  }
}

#endif // !LAYER_HPP_