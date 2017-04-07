#include <iostream>
#include "Layer.hpp"

namespace arcade
{
	Layer::Layer(size_t width, size_t height) : m_width(width), m_height(height)
	{
		Tile tile;
		
		tile.setColor(Color::Transparent);
                tile.removeSprite();

		m_tiles.insert(m_tiles.begin(), width * height, tile);
	}

	Layer::~Layer()
	{
	}

	Tile &Layer::at(size_t x, size_t y)
	{
		return (m_tiles[y * m_width + x]);
	}

	Tile const &Layer::at(size_t x, size_t y) const
	{
		return (m_tiles[y * m_width + x]);
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