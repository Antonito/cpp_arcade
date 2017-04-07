#include <iostream>
#include <sstream>
#include "Snake.hpp"
#include "Sprite.hpp"

namespace arcade
{
  namespace game
  {
    namespace snake
    {
      Snake::Snake()
      {

      }

      Snake::Snake(Snake const &other)
      {
      }

      Snake::~Snake()
      {
      }

      Snake &Snake::operator=(Snake const &other)
      {
        if (this != &other)
        {
        }
        return (*this);
      }

      void Snake::notifyEvent(std::vector<Event> &&events)
      {
        std::vector<Event> ev = events;

      }

      std::vector<std::pair<std::string, SoundType>> Snake::getSoundsToLoad() const
      {
        std::vector<std::pair<std::string, SoundType>> s;
        // TODO: implement
        return (s);
      }

      std::vector<std::unique_ptr<ISprite>> Snake::getSpritesToLoad() const
      {
        std::vector<std::unique_ptr<ISprite>> s;

        return (s);
      }

      void Snake::process()
      {
      }

#if defined(__linux__)
      WhereAmI *Snake::getWhereAmI() const
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
  arcade::game::snake::Snake game;

  game.Play();
}