#ifndef MAP_HPP_
#define MAP_HPP_

#include <cstdlib>
#include "IMap.hpp"
#include "Layer.hpp"

namespace arcade
{
	class Map : public IMap
	{
	public:
		Map(size_t width, size_t height);

		Map(Map const &other) = delete;
		virtual ~Map();
			
		Map &operator=(Map const &other) = delete;

		virtual Tile &at(size_t layer, size_t x, size_t y);
		virtual Tile const &at(size_t layer, size_t x, size_t y) const;
		virtual size_t getLayerNb() const;
		virtual size_t getWidth() const;
		virtual size_t getHeight() const;
		void addLayer();

	private:
		std::vector<Layer> m_layers;
		size_t m_width;
		size_t m_height;
	};
}

#endif // !MAP_HPP_