#ifndef MAP_HPP_
#define MAP_HPP_

#include <cstdlib>
#include <string>
#include "IMap.hpp"
#include "Layer.hpp"

namespace arcade
{
  namespace game
  {
    class Map : public IMap
    {
    public:
      Map(size_t width, size_t height);

      Map(Map const &other);
      Map(Map &&other);
      virtual ~Map();

      Map &operator=(Map const &other);
      Map &operator=(Map &&other);

      virtual Tile &at(size_t layer, size_t x, size_t y);
      virtual Tile const &at(size_t layer, size_t x, size_t y) const;
      virtual size_t getLayerNb() const;
      virtual size_t getWidth() const;
      virtual size_t getHeight() const;
      void           addLayer();
      void loadMap(std::string const &path);

      void clear(Color color = Color::Transparent);
      void clear(Color color, size_t sprite);
      void clearLayer(size_t layer, Color color = Color::Transparent);
      void clearLayer(size_t layer, Color color, size_t sprite);

    private:
      std::vector<Layer> m_layers;
      size_t             m_width;
      size_t             m_height;
    };
  }
}

#endif // !MAP_HPP_