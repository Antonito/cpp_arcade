#include <iostream>
#include "Tile.hpp"

namespace arcade
{
Tile::Tile(TileType type, Color color) : m_type(type), m_color(color)
{
}

Tile::Tile(Tile const &other) : m_type(other.m_type),
				m_color(other.m_color), m_sprite(other.m_sprite)
{
}

Tile::~Tile()
{
}

Tile &Tile::operator=(Tile const &other)
{
	if (this != &other)
	{
		m_type = other.m_type;
		m_color = other.m_color;
		m_sprite = other.m_sprite;
	}
	return (*this);
}

TileType Tile::getType() const
{
	return (m_type);
}

void Tile::setType(TileType type)
{
	m_type = type;
}

TileTypeEvolution Tile::getTypeEv() const
{
	return (m_typeEv);
}

void Tile::setTypeEv(TileTypeEvolution type)
{
	m_typeEv = type;
}

Color Tile::getColor() const
{
	return (m_color);
}

void Tile::setColor(Color color)
{
	m_color = color;
}

size_t Tile::getSpriteId() const
{
	return (0);
}

size_t Tile::getSpritePos() const
{
	return (m_sprite.getPos());
}

void Tile::nextSprite()
{
	m_sprite.next();
}

void Tile::prevSprite()
{
	m_sprite.prev();
}

void Tile::setSpritePos(size_t pos)
{
	m_sprite.setPos(pos);
}

void Tile::setSprite(size_t id)
{
	m_sprite.setId(id);
}

double Tile::getShiftX() const
{
	return (m_shiftX);
}

double Tile::getShiftY() const
{
	return (m_shiftY);
}

void Tile::setShiftX(double shift)
{
	m_shiftX = shift;
}

void Tile::setShiftY(double shift)
{
	m_shiftY = shift;
}

void Tile::setShift(double x, double y)
{
	setShiftX(x);
	setShiftY(y);
}

bool Tile::hasSprite() const
{
	return (false);
}
}
