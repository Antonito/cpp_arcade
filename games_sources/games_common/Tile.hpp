#ifndef TILE_HPP_
#define TILE_HPP_

#include <cstdlib>
#include "ITile.hpp"
#include "Protocol.hpp"
#include "Color.hpp"
#include "SpriteRef.hpp"

namespace arcade
{
	class Tile : public ITile
	{
	public:
		Tile(TileType type = TileType::EMPTY, Color color = { 0xFFFFFFFF });
		Tile(Tile const &other);
		~Tile();

		Tile &operator=(Tile const &other);

		virtual TileType getType() const;
		virtual void setType(TileType type);

		virtual Color getColor() const;
		virtual void setColor(Color color);

		virtual int getSpriteId() const;
		virtual size_t getSpritePos() const;
		virtual void   nextSprite();
		virtual void   prevSprite();
		virtual void setSpritePos(size_t pos);
		virtual void setSprite(int id);

	private:
		TileType m_type;
		Color m_color;
		SpriteRef m_sprite;
	};
}

#endif // !TILE_HPP_