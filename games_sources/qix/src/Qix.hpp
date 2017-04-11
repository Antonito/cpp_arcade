#ifndef QIX_HPP_
#define QIX_HPP_

#include <cstdlib>
#include <ostream>
#include "AGame.hpp"
#include "Player.hpp"
#include "AEntity.hpp"

namespace arcade
{
  namespace game
  {
    namespace qix
    {
      class Qix : public AGame
      {

      public:
	Qix();
	Qix(Qix const &other);
	~Qix();

	Qix &operator=(Qix const &other);

	virtual void notifyEvent(std::vector<Event> &&events);

	virtual std::vector<std::pair<std::string, SoundType>>
	    getSoundsToLoad() const;

	virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

	virtual void process();

#if defined(__linux__)
	virtual void WhereAmI(std::ostream &) const;
#endif
      private:
	Player    m_player;
	Direction m_dir;

	size_t m_lastTick;
	size_t m_curTick;
      };
    }
  }
}

#if defined(__linux__)
extern "C" void Play(void);
#endif

#endif // !QIX_HPP_
