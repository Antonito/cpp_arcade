#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <cstdlib>
#include "AGame.hpp"

namespace arcade
{
	class Snake : public AGame
	{
	public:
		Snake();
		Snake(Snake const &other);
		~Snake();

		Snake &operator=(Snake const &other);

		virtual void notifyEvent(std::vector<Event> &&events);

		virtual std::vector<std::string> getSoundsToLoad() const;

		virtual void process();

	private:
		struct
		{
			size_t x;
			size_t y;
		}   m_pos;
	};
}

#endif // !SNAKE_HPP_