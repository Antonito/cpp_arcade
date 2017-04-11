#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "AEntity.hpp"
#include "AMovable.hpp"

namespace arcade
{
  namespace game
  {
    namespace pacman
    {
      class Enemy : public AMovable
      {

      public:
	Enemy();
	Enemy(Enemy const &other) = default;
	virtual ~Enemy();
	virtual void display(Map &map, double ratio = 0.0) const;
	virtual void move(Map &map);

	void kill();
	void setEatable(bool eat);
	void setDead(bool dead);
	void setDeathTime(size_t time);

	size_t getDeathTime() const;
	bool   getEatable() const;
	bool   getDead() const;

      private:
	bool   m_eatable;
	bool   m_dead;
	size_t m_deathTime;
      };
    }
  }
}
#endif // !ENEMY_HPP_
