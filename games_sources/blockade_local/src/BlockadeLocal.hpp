#ifndef BLOCKADELOCAL_HPP_
#define BLOCKADELOCAL_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    namespace blockade_local
    {
      class BlockadeLocal : public AGame
      {

      public:
	BlockadeLocal();
	BlockadeLocal(BlockadeLocal const &other);
	~BlockadeLocal();

	BlockadeLocal &operator=(BlockadeLocal const &other);

	virtual void notifyEvent(std::vector<Event> &&events);

	virtual std::vector<std::pair<std::string, SoundType>>
	    getSoundsToLoad() const;

	virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

	virtual void process();

#if defined(__linux__)
	virtual void WhereAmI(std::ostream &os) const;
#endif
      private:
	Player    m_player1;
	Player    m_player2;
	Fruit     m_fruit;
	Direction m_tmpDir1;
	Direction m_tmpDir2;

	size_t m_lastTick;
	size_t m_curTick;
      };
    }
  }
}

#if defined(__linux__)
extern "C" void Play(void);
#endif

#endif // !BLOCKADELOCAL_HPP_
