#include "Snake.hpp"

namespace arcade
{
	Snake::Snake()
	{}

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