#include <iostream>
#include "Pos.hpp"

namespace arcade
{

Pos::Pos(ssize_t x, ssize_t y) : m_x(x), m_y(y)
{
}

Pos::~Pos()
{
}

bool Pos::operator==(Pos const &other) const
{
	if (m_x == other.getX() && m_y == other.getY())
		return true;
	return false;
}

bool Pos::inMap(Map &map) const
{
	if (m_x < 0 || m_x >= map.getWidth() || m_y < 0 || m_y >= map.getWidth())
		return false;
	return true;
}

void Pos::move(Dir dir)
{
	switch (dir)
	{
	case Dir::UP:
		m_y -= 1;
		break;
	case Dir::DOWN:
		m_y += 1;
		break;
	case Dir::LEFT:
		m_x -= 1;
		break;
	case Dir::RIGHT:
		m_x += 1;
		break;
	}
}

void Pos::setX(ssize_t x)
{
	m_x = x;
}

void Pos::setY(ssize_t y)
{
	m_y = y;
}

ssize_t Pos::getX() const
{
	return (m_x);
}

ssize_t Pos::getY() const
{
	return (m_y);
}
}