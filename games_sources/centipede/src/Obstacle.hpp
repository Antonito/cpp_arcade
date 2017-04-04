#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <cstdlib>
#include "AGame.hpp"
// include Pos

namespace arcade
{
class Obstacle
{

      public:
	Obstacle(bool destructible, Pos &pos, ssize_t pv);
	Obstacle(Obstacle const &other);
	~Obstacle();
	Obstacle &operator=(Obstacle const &other);
	void hit(size_t damage = 1);
	void place(Map &map);
	void move();
	void destroy(Map &map);
	ssize_t getPv() const;

      private:
	Pos m_pos;
	ssize_t m_pv;
	bool m_destructible;
};
}

#endif // !OBSTACLE_HPP_