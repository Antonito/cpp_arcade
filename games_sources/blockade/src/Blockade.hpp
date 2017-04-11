#ifndef BLOCKADE_HPP_
#define BLOCKADE_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    namespace blockade
    {
      class Blockade : public AGame
      {

      public:
	Blockade();
	Blockade(Blockade const &other);
	~Blockade();

	Blockade &operator=(Blockade const &other);

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
	size_t    m_lastTick;
	size_t    m_curTick;
      };
    }
  }
}

#if defined(__linux__)
extern "C" void Play(void);
#endif

#endif // !BLOCKADE_HPP_
