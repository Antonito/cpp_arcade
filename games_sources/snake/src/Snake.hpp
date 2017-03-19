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

		virtual std::vector<std::string> getSoundsToLoad() const;

		virtual void process();

	private:
	};
}

#endif // !SNAKE_HPP_