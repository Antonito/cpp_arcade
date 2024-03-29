#include "Map.hpp"
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include "RessourceError.hpp"

namespace arcade
{
  namespace game
  {
    Map::Map(size_t width, size_t height) : m_width(width), m_height(height)
    {
    }

    Map::Map(Map const &other)
        : m_layers(other.m_layers), m_width(other.m_width),
          m_height(other.m_height)
    {
    }

    Map::Map(Map &&other)
        : m_layers(std::move(other.m_layers)), m_width(other.m_width),
          m_height(other.m_height)
    {
      other.m_width = 0;
      other.m_height = 0;
    }

    Map::~Map()
    {
    }

    Map &Map::operator=(Map const &other)
    {
      if (this != &other)
	{
	  m_layers = other.m_layers;
	  m_width = other.m_width;
	  m_height = other.m_height;
	}
      return (*this);
    }

    Map &Map::operator=(Map &&other)
    {
      if (this != &other)
	{
	  m_layers = std::move(other.m_layers);
	  m_width = other.m_width;
	  m_height = other.m_height;
	  other.m_width = 0;
	  other.m_height = 0;
	}
      return (*this);
    }

    Tile &Map::at(size_t layer, size_t x, size_t y)
    {
      return (m_layers[layer].at(x, y));
    }

    Tile const &Map::at(size_t layer, size_t x, size_t y) const
    {
      return (m_layers[layer].at(x, y));
    }

    size_t Map::getLayerNb() const
    {
      return (m_layers.size());
    }

    size_t Map::getWidth() const
    {
      return (m_width);
    }

    size_t Map::getHeight() const
    {
      return (m_height);
    }

    void Map::addLayer()
    {
      m_layers.emplace_back(m_width, m_height);
    }

    void Map::loadMap(std::string const &path)
    {
      std::stringstream map;
      std::ifstream     file;
      std::string       tmp;
      file.open(path.c_str());
      if (file.is_open())
	{
	  map << file.rdbuf();
	  file.close();
	}
      else
	throw RessourceError("Cannot open map: " + path);
      map >> m_width;
      map >> m_height;
      std::getline(map, tmp);
      addLayer();

      if (m_width * m_height > map.str().size())
	{
	  throw RessourceError("Invalid map size");
	}
      for (size_t y = 0; std::getline(map, tmp) && y < m_height; y++)
	{
	  for (size_t x = 0; x < tmp.size() && x < m_width; x++)
	    {
	      if (tmp[x] >= '0' && tmp[x] <= '9')
		m_layers[0].at(x, y).setType(
		    static_cast<TileType>(tmp[x] - '0'));
	    }
	}
    }

    void Map::clear(Color color)
    {
      for (Layer &layer : m_layers)
	{
	  layer.clear(color);
	}
    }

    void Map::clear(Color color, size_t sprite)
    {
      for (Layer &layer : m_layers)
	{
	  layer.clear(color, sprite);
	}
    }

    void Map::clearLayer(size_t layer, Color color)
    {
      m_layers[layer].clear(color);
    }

    void Map::clearLayer(size_t layer, Color color, size_t sprite)
    {
      m_layers[layer].clear(color, sprite);
    }
  }
}
