#ifndef PONG_HPP_
#define PONG_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "PacketFactory.hpp"

namespace arcade
{
  namespace game
  {
    namespace pong
    {
      class Pong : public AGame
      {

      public:
        Pong();
        Pong(Pong const &other);
        virtual ~Pong();

        Pong &operator=(Pong const &other);

	virtual bool hasNetwork() const;

        virtual void notifyEvent(std::vector<Event> &&events);

        virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

        virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

        virtual void process();

#if defined(__linux__)
        virtual void WhereAmI(std::ostream &) const;
#endif
      private:
	enum PongState
	  {
	    AUTHENTICATING,
	    SETTING,
	    WAITING,
	    PLAYING
	  };

        size_t m_lastTick;
        size_t m_curTick;

        Ball m_ball;
        Player m_player[2];
        size_t m_id;
	PongState m_state;
	Network::PacketFactory m_fact;
	uint8_t m_playerId;
      };
    }
  }
}

#if defined(__linux__)
extern "C" void Play(void);
#endif

#endif // !PONG_HPP_
