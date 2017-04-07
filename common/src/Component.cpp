#include "Component.hpp"

namespace arcade
{
	Component::Component()
	{}

        Component::Component(double x, double y, double width, double height,
          Color color, std::string const & text) :
          m_pos({ x, y }),
          m_size({ width, height }),
          m_color(color),
          m_text(text)
        {
        }

	Component::~Component()
	{}

	double Component::getX() const
	{
		return (m_pos.x);
	}

	double Component::getY() const
	{
		return (m_pos.y);
	}

	void Component::setX(double x)
	{
		m_pos.x = x;
	}

	void Component::setY(double y)
	{
		m_pos.y = y;
	}

	double Component::getWidth() const
	{
		return (m_size.x);
	}

	double Component::getHeight() const
	{
		return (m_size.y);
	}

	void Component::setWidth(double width)
	{
		m_size.x = width;
	}

	void Component::setHeight(double height)
	{
		m_size.y = height;
	}

	std::size_t Component::getBackgroundId() const
	{
		return (m_sprite);
	}

	Color Component::getBackgroundColor() const
	{
		return (m_color);
	}

	std::string const & Component::getText() const
	{
		return (m_text);
	}

	void Component::setBackgroundId(std::size_t id)
	{
		m_sprite = id;
	}

	void Component::setBackgroundColor(Color color)
	{
		m_color = color;
	}

	void Component::setText(std::string const & text)
	{
		m_text = text;
	}

	Color Component::getTextColor() const
	{
	  return (Color());
	}

	void Component::setClicked()
	{
		this->setClicked(true);
	}

	void Component::setClicked(bool click)
	{
		m_clicked = click;
	}

	bool Component::isClicked() const
	{
		return (m_clicked);
	}

	bool Component::hasSprite() const
	{
	  return (false);
	}
}
