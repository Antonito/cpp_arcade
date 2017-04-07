#ifndef Pong_HPP_
#define Pong_HPP_

#include <cstdlib>
#include "AGame.hpp"
#include "Player.hpp"
#include "Pos.hpp"

namespace arcade
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

  virtual std::vector<std::unique_ptr<ISprite>> &&getSpritesToLoad() const;

  virtual void process();

  virtual WhereAmI *getWhereAmI() const;

private:
  Player m_player1;
  Player m_player2;

  size_t m_lastTickPlayer;
  size_t m_curTick;
};
}

#endif // !Pong_HPP_
