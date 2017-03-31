#include "Map.hpp"

namespace arcade
{
	Map::Map(size_t width, size_t height) : m_width(width), m_height(height)
	{
		// Push a first layer
		this->addLayer();
	}

	Map::~Map()
	{
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
}