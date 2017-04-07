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
	Tile(TileType type = TileType::EMPTY, Color color = {0xFFFFFFFF});
	Tile(Tile const &other);
	~Tile();

	Tile &operator=(Tile const &other);

	virtual TileType getType() const;
	virtual void setType(TileType type);

	virtual TileTypeEvolution getTypeEv() const;
	virtual void setTypeEv(TileTypeEvolution type);

	virtual Color getColor() const;
	virtual void setColor(Color color);

	virtual size_t getSpriteId() const;
	virtual size_t getSpritePos() const;
	virtual void nextSprite();
	virtual void prevSprite();
	virtual void setSpritePos(size_t pos);
	virtual void setSprite(size_t id);
        void removeSprite();

	virtual double getShiftX() const;
	virtual double getShiftY() const;
	virtual bool hasSprite() const;

	void setShiftX(double shift);
	void setShiftY(double shift);
	void setShift(double x, double y);

      private:
	TileType m_type;
	TileTypeEvolution m_typeEv;
	Color m_color;
	SpriteRef m_sprite;
	double m_shiftX;
	double m_shiftY;
        bool m_hasSprite;
};
}

#endif // !TILE_HPP_
