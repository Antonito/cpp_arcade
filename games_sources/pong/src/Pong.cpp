#include <iostream>
#include <sstream>
#include "Pong.hpp"
#include "Sprite.hpp"

namespace arcade
{
  namespace game
  {
    namespace Pong
    {
      Pong::Pong()
      {

      }

      Pong::Pong(Pong const &other)
      {
      }

      Pong::~Pong()
      {
      }

      Pong &Pong::operator=(Pong const &other)
      {
        if (this != &other)
        {
        }
        return (*this);
      }

      void Pong::notifyEvent(std::vector<Event> &&events)
      {
        std::vector<Event> ev = events;

      }

      std::vector<std::pair<std::string, SoundType>> Pong::getSoundsToLoad() const
      {
        std::vector<std::pair<std::string, SoundType>> s;
        // TODO: implement
        return (s);
      }

      std::vector<std::unique_ptr<ISprite>> Pong::getSpritesToLoad() const
      {
        std::vector<std::unique_ptr<ISprite>> s;

        return (s);
      }

      void Pong::process()
      {
      }

#if defined(__linux__)
      WhereAmI *Pong::getWhereAmI() const
      {
        // TODO: implement
        return (nullptr);
      }
#endif
    }
  }
}


extern "C" void Play(void)
{
  arcade::game::Pong::Pong game;

  game.Play();
}