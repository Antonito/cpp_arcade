#include <iostream>
#include "Layer.hpp"

namespace arcade
{
  namespace game
  {
    Layer::Layer(size_t width, size_t height) : m_width(width), m_height(height)
    {
      Tile tile;

      tile.setColor(Color::Transparent);
      tile.removeSprite();

      m_tiles.insert(m_tiles.begin(), width * height, tile);
    }

    Layer::Layer(Layer const & other) :
      m_tiles(other.m_tiles),
      m_width(other.m_width),
      m_height(other.m_height)
    {
    }

    Layer::Layer(Layer && other) :
      m_tiles(std::move(other.m_tiles)),
      m_width(other.m_width),
      m_height(other.m_height)
    {
      other.m_width = 0;
      other.m_height = 0;
    }

    Layer::~Layer()
    {
    }

    Layer & Layer::operator=(Layer const & other)
    {
      if (this != &other)
      {
        m_tiles = other.m_tiles;
        m_width = other.m_width;
        m_height = other.m_height;
      }
      return (*this);
    }

    Layer & Layer::operator=(Layer && other)
    {
      if (this != &other)
      {
        m_tiles = std::move(other.m_tiles);
        m_width = other.m_width;
        m_height = other.m_height;
        other.m_width = 0;
        other.m_height = 0;
      }
      return (*this);
    }

    Tile &Layer::at(size_t x, size_t y)
    {
      return (m_tiles[y * m_width + x]);
    }

    Tile const &Layer::at(size_t x, size_t y) const
    {
      return (m_tiles[y * m_width + x]);
    }

    void Layer::clear(Color color)
    {
      for (Tile &tile : m_tiles)
      {
        tile.setColor(color);
        tile.removeSprite();
        tile.setShiftX(0);
        tile.setShiftY(0);
      }
    }

    void Layer::clear(Color color, size_t sprite)
    {
      for (Tile &tile : m_tiles)
      {
        tile.setColor(color);
        tile.setSprite(sprite);
        tile.setShiftX(0);
        tile.setShiftY(0);
      }
    }

    size_t Layer::getWidth() const
    {
      return (m_width);
    }

    size_t Layer::getHeight() const
    {
      return (m_height);
    }
  }
}