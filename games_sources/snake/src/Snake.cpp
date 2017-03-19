#include "Snake.hpp"

namespace arcade
{
	Snake::Snake()
	{
		constexpr size_t width = 25;
		constexpr size_t height = 25;

		m_map = std::make_unique<Map>(width, height);
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				uint8_t r = rand() % 256;
				uint8_t g = rand() % 256;
				uint8_t b = rand() % 256;

				(*m_map)[0][y][x]->setColor(Color(r, g, b));
			}
		}
	}

	Snake::Snake(Snake const &other)
	{}

	Snake::~Snake()
	{}

	Snake &Snake::operator=(Snake const &other)
	{
		if (this != &other)
		{
		}
		return (*this);
	}

	std::vector<std::string> Snake::getSoundsToLoad() const
	{
		// TODO: implement
		return (std::vector<std::string>());
	}

	void Snake::process()
	{
		for (Event const &e : m_events)
		{
			if (e.type == ET_QUIT)
			{
				m_state = QUIT;
			}
		}
	}

}