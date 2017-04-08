#ifndef PONG_HPP_
#define PONG_HPP_

#include <cstdlib>
#include "AGame.hpp"

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
        ~Pong();

        Pong &operator=(Pong const &other);

        virtual void notifyEvent(std::vector<Event> &&events);

        virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const;

        virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;

        virtual void process();

#if defined(__linux__)
        virtual WhereAmI *getWhereAmI() const;
#endif
      private:

        size_t m_lastTick;
        size_t m_curTick;
      };
    }
  }
}

extern "C" void Play(void);

#endif // !PONG_HPP_
