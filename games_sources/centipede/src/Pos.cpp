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
void Pos::up()
{
	m_y -= 1;
}

void Pos::down()
{
	m_y += 1;
}

void Pos::left()
{
	m_x -= 1;
}

void Pos::right()
{
	m_x += 1;
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