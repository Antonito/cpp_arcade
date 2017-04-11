#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "Obstacle.hpp"
#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    namespace nibbler
    {
      class Nibbler : public AGame
      {

      public:
	Nibbler();
	Nibbler(Nibbler const &other);
	~Nibbler();

	Nibbler &operator=(Nibbler const &other);

	virtual void notifyEvent(std::vector<Event> &&events);

	virtual std::vector<std::pair<std::string, SoundType>>
	    getSoundsToLoad() const;

	virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

	virtual void process();

#if defined(__linux__)
	virtual void WhereAmI(std::ostream &os) const;
#endif
      private:
	Position placeFood(Map const &map) const;

	Player    m_player;
	Fruit     m_fruit;
	Direction m_tmpDir;
	Obstacle  m_obstacles;

	size_t m_lastTick;
	size_t m_curTick;
      };
    }
  }
}

#if defined(__linux__)
extern "C" void Play(void);
#endif

#endif // !NIBBLER_HPP_
