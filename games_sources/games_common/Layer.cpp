#include "Layer.hpp"

namespace arcade
{
	Layer::Layer(size_t width, size_t height) : m_width(width), m_height(height)
	{
		m_tiles.reserve(height);
		for (size_t y = 0; y < height; ++y)
		{
			m_tiles.emplace_back();
			m_tiles[y].reserve(width);
			for (size_t x = 0; x < width; ++x)
			{
				m_tiles[y].push_back(std::make_unique<Tile>());
			}
		}
	}

	Layer::~Layer()
	{
	}

	std::vector<std::unique_ptr<ITile>>& Layer::operator[](int n)
	{
		return (m_tiles[n]);
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