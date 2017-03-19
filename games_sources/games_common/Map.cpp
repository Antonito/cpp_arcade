#include "Map.hpp"

namespace arcade
{
	Map::Map(size_t width, size_t height) : m_width(width), m_height(height)
	{
		// Push a first layer
		m_layers.emplace_back(width, height);
	}

	Map::~Map()
	{
	}

	Layer & Map::operator[](size_t n)
	{
		return (m_layers[n]);
	}

	Layer const & Map::operator[](size_t n) const
	{
		return (m_layers[n]);
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