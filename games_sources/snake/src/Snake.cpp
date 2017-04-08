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
  m_map = std::make_unique<Map>(0, 0);
  m_map->loadMap("./map/snake/snake_map.txt");
  m_map->addLayer();
  //clear;
  m_player->push(Position(m_map->getWidth() / 2, m_map->getHeight() / 2), 4);
  m_fruit->push(Position(placeFood()));
  m_lastTick = 0;
  m_curTick = 0;
}

Snake::Snake(Snake const &other)
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_fruit = other.m_fruit;
  m_lastTick = other.m_lastTick;
  m_curTick = other.m__curTick;
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

  for (Event const &e : ev)
  {
    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      switch (e.kb_key)
      {
      case KB_ARROW_UP:
        if (m_player.getDir() != Direction::DOWN)
          m_tmpDir = Direction::UP;
        break;
      case KB_ARROW_DOWN:
        if (m_player.getDir() != Direction::UP)
          m_tmpDir = Direction::DOWN;
        break;
      case KB_ARROW_LEFT:
        if (m_player.getDir() != Direction::RIGHT)
          m_tmpDir = Direction::LEFT;
        break;
      case KB_ARROW_RIGHT:
        if (m_player.getDir() != Direction::LEFT)
          m_tmpDir = Direction::RIGHT;
        break;
      case KB_ESCAPE:
        m_state = MENU;
      default:
        break;
      }
    }
  }
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
  m_curTick = this->getCurrentTick();
  //clear
  m_player.display(*m_map, (m_curTick - m_lastTick) / 100.0);
  m_fruit.display(*m_map);

  if (m_curTick - m_lastTick > 100)
  {
    if (m_fruit.isTouch(m_player.next()))
      m_fruit[0] = placeFood();
    if (m_player.next().inMap(*m_map) && !m_player.isTouch(m_player.next()))
    {
      m_player.setDir(m_tmpDir);
      m_player.move();
    }
    else
      m_state = MENU;
    m_lastTick = m_curTick;
  }
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