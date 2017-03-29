#include <iostream>
#include "Snake.hpp"

namespace arcade
{
	Snake::Snake()
	{
		constexpr size_t width = 24;
		constexpr size_t height = 24;

		m_map = std::make_unique<Map>(width, height);
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				m_map->at(0, x, y).setColor(Color::White);
			}
		};

		m_pos = { width / 2, height / 2 };

		m_map->addLayer();
	}

	Snake::Snake(Snake const &other)
	{
		size_t width = other.m_map->getWidth();
		size_t height = other.m_map->getHeight();

		// TODO : also copy layers

		m_map = std::make_unique<Map>(width, height);
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				m_map->at(0, x, y).setColor(Color::White);
			}
		};

		m_pos = { width / 2, height / 2 };
	}

	Snake::~Snake()
	{}

	Snake &Snake::operator=(Snake const &other)
	{
		std::cout << "eq" << std::endl;
		if (this != &other)
		{
		}
		return (*this);
	}

	void Snake::notifyEvent(std::vector<Event>&& events)
	{
		std::vector<Event> ev = events;

		for (Event const &e : ev)
		{
			if (e.type == ET_QUIT)
			{
				m_state = QUIT;
			}
			else if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
			{
				switch (e.kb_key)
				{
				case KB_ARROW_UP:
					m_pos.y = (m_pos.y - 1 + m_map->getHeight()) % m_map->getHeight();
					break;
				case KB_ARROW_DOWN:
					m_pos.y = (m_pos.y + 1) % m_map->getHeight();
					break;
				case KB_ARROW_LEFT:
					m_pos.x = (m_pos.x - 1 + m_map->getWidth()) % m_map->getWidth();
					break;
				case KB_ARROW_RIGHT:
					m_pos.x = (m_pos.x + 1) % m_map->getWidth();
					break;
				case KB_ESCAPE:
					m_state = QUIT;
				default:
					break;
				}
			}
		}
	}

	std::vector<std::string> Snake::getSoundsToLoad() const
	{
		// TODO: implement
		return (std::vector<std::string>());
	}

	void Snake::process()
	{
		for (size_t y = 0; y < m_map->getHeight(); ++y)
		{
			for (size_t x = 0; x < m_map->getWidth(); ++x)
			{
				m_map->at(1, x, y).setColor(Color::Transparent);
			}
		};
		m_map->at(1, m_pos.x, m_pos.y).setColor(Color::Red);
	}
}