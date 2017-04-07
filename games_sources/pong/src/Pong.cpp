#include <iostream>
#include <unistd.h>
#include "Pong.hpp"

namespace arcade
{
Pong::Pong()
{
  constexpr size_t width = 24;
  constexpr size_t height = 24;

  m_map = std::make_unique<Map>(width, height);
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      m_map->at(0, x, y).setColor(Color::White);
    }
  };
  m_map->addLayer();
  m_gui = std::make_unique<GUI>();

  m_player1 = Player(Pos(2, height / 2), Dir::UP);
  m_player2 = Player(Pos(width - 2, height / 2), Dir::UP);
  m_lastTickPlayer = 0;
  Component comp;

  comp.setX(0.05);
  comp.setY(0.05);
  comp.setWidth(0.15);
  comp.setHeight(0.05);
  comp.setBackgroundColor(Color(0, 0, 0, 170));
  m_gui->push(std::move(comp));
}

Pong::Pong(Pong const &other)
{
  size_t width = other.m_map->getWidth();
  size_t height = other.m_map->getHeight();

  // TODO : also copy layers

  m_map = std::make_unique<Map>(width, height);
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      m_map->at(0, x, y).setColor(Color::White);
    }
  };

  m_player1 = Player(Pos(2, height / 2), Dir::UP);
  m_player2 = Player(Pos(width - 2, height / 2), Dir::UP);
  m_lastTickPlayer = 0;
}

Pong::~Pong()
{
}

Pong &Pong::operator=(Pong const &other)
{
  std::cout << "eq" << std::endl;
  if (this != &other)
  {
  }
  return (*this);
}

void Pong::notifyEvent(std::vector<Event> &&events)
{
  std::vector<Event> ev = events;
  for (Event const &e : ev)
  {
    if (e.type == ET_QUIT)
    {
      m_state = QUIT;
    }
    else if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      switch (e.kb_key)
      {
      case KB_ARROW_UP:
        if (m_player1.getPos().getY() > 0)
        {
          m_player1.move(*m_map, Dir::UP);
        }
        break;
      case KB_ARROW_DOWN:
        if (static_cast<size_t>(m_player1.getPos().getY()) < m_map->getHeight() - 1)
        {
          m_player1.move(*m_map, Dir::DOWN);
        }
        break;
      case KB_ESCAPE:
        m_state = MENU;
      default:
        break;
      }
    }
  }
}

std::vector<std::pair<std::string, SoundType>> Pong::getSoundsToLoad() const
{
  // TODO: implement
  return (std::vector<std::pair<std::string, SoundType>>());
}

std::vector<std::unique_ptr<ISprite>> Pong::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

void Pong::process()
{

  //TODO: Use std::chrono
  m_curTick = this->getCurrentTick();

  for (size_t y = 0; y < m_map->getHeight(); ++y)
  {
    for (size_t x = 0; x < m_map->getWidth(); ++x)
    {
      m_map->at(1, x, y).setColor(Color::Transparent);
    }
  };

  //Players display
  m_player1.display(*m_map);
  m_player2.display(*m_map);

  // Make  the Pongs move at each tik

  if ((m_curTick - m_lastTickPlayer) > 60)
  {

    m_lastTickPlayer = m_curTick;
  }
}

WhereAmI *Pong::getWhereAmI() const
{
  WhereAmI *w = new WhereAmI;

  w->type = CommandType::WHERE_AM_I;
  w->lenght = 0;
  return (w);
}
}