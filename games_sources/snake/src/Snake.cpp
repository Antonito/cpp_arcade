#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Snake.hpp"

namespace arcade
{
Snake::Snake()
{
  constexpr size_t width = 24;
  constexpr size_t height = 24;
  t_pos start_pos;

  start_pos.x = width / 2;
  start_pos.y = height / 2;
  for (size_t i = 0; i < 4; i++)
    m_pos.push_back(start_pos);
  m_map = std::make_unique<Map>(width, height);
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      m_map->at(0, x, y).setColor(Color::White);
    }
  };
  m_lastTick = 0;
  m_curTick = 0;
  m_map->addLayer();
  m_dir = LEFT;
  placeFood();
  m_gui = std::make_unique<GUI>();

  Component comp;

  comp.setX(0.05);
  comp.setY(0.05);
  comp.setWidth(0.15);
  comp.setHeight(0.05);
  comp.setBackgroundColor(Color(0, 0, 0, 170));
  m_gui->push(std::move(comp));
}

Snake::Snake(Snake const &other)
{
  size_t width = other.m_map->getWidth();
  size_t height = other.m_map->getHeight();
  t_pos start_pos;

  start_pos.x = width / 2;
  start_pos.y = height / 2;
  for (size_t i = 0; i < 4; i++)
    m_pos.push_back(start_pos);

  m_dir = LEFT;
  placeFood();
  // TODO : also copy layers

  m_map = std::make_unique<Map>(width, height);
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      m_map->at(0, x, y).setColor(Color::White);
    }
  };
}

Snake::~Snake()
{
}

Snake &Snake::operator=(Snake const &other)
{
  std::cout << "eq" << std::endl;
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
        if (m_dir != DOWN)
          m_dir = UP;
        break;
      case KB_ARROW_DOWN:
        if (m_dir != UP)
          m_dir = DOWN;
        break;
      case KB_ARROW_LEFT:
        if (m_dir != RIGHT)
          m_dir = LEFT;
        break;
      case KB_ARROW_RIGHT:
        if (m_dir != LEFT)
          m_dir = RIGHT;
        break;
      default:
        break;
      }
    }
  }
}

std::vector<std::pair<std::string, SoundType>> Snake::getSoundsToLoad() const
{
  // TODO: implement
  return (std::vector<std::pair<std::string, SoundType>>());
}

std::vector<std::unique_ptr<ISprite>> Snake::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

bool Snake::isDead(Snake::t_pos const &next) const
{
  if (next.x < 0 || static_cast<size_t>(next.x) >= m_map->getWidth() || next.y < 0 ||
      static_cast<size_t>(next.y) >= m_map->getHeight())
    return true;
  for (t_pos const &p : m_pos)
  {
    if (next.x == p.x && next.y == p.y)
      return true;
  }
  return false;
}

void Snake::didEat()
{
  m_eat = false;
  if (m_food.x == m_pos.front().x && m_food.y == m_pos.front().y)
  {
    m_eat = true;
  }
}

bool Snake::onSnake(Snake::t_pos const &new_food) const
{
  for (t_pos const &p : m_pos)
  {
    if (p.x == new_food.x && p.y == new_food.y)
      return true;
  }
  return false;
}

void Snake::placeFood()
{
  t_pos new_food;

  new_food.x = rand() % m_map->getWidth();
  new_food.y = rand() % m_map->getHeight();
  while (onSnake(new_food))
  {
    new_food.x = rand() % m_map->getWidth();
    new_food.y = rand() % m_map->getHeight();
  }
  m_food = new_food;
}

void Snake::process()
{
  t_pos next;

  m_curTick = this->getCurrentTick();
  if ((m_curTick - m_lastTick) > 60)
  {
    didEat();
    if (m_eat)
      placeFood();
    switch (m_dir)
    {
    case UP:
      next.x = m_pos.front().x;
      next.y = m_pos.front().y - 1;
      if (!m_eat)
        m_pos.pop_back();
      if (isDead(next))
        m_state = MENU;
      else
        m_pos.insert(m_pos.begin(), next);
      break;
    case DOWN:
      next.x = m_pos.front().x;
      next.y = m_pos.front().y + 1;
      if (!m_eat)
        m_pos.pop_back();
      if (isDead(next))
        m_state = MENU;
      else
        m_pos.insert(m_pos.begin(), next);
      break;
    case LEFT:
      next.x = m_pos.front().x - 1;
      next.y = m_pos.front().y;
      if (!m_eat)
        m_pos.pop_back();
      if (isDead(next))
        m_state = MENU;
      else
        m_pos.insert(m_pos.begin(), next);
      break;
    case RIGHT:
      next.x = m_pos.front().x + 1;
      next.y = m_pos.front().y;
      if (!m_eat)
        m_pos.pop_back();
      if (isDead(next))
        m_state = MENU;
      else
        m_pos.insert(m_pos.begin(), next);
      break;
    default:
      break;
    }
    for (size_t y = 0; y < m_map->getHeight(); ++y)
    {
      for (size_t x = 0; x < m_map->getWidth(); ++x)
      {
        m_map->at(1, x, y).setColor(Color::Transparent);
      }
    };

    m_map->at(1, m_food.x, m_food.y).setColor(Color::Green);
    for (t_pos const &p : m_pos)
    {
      if (p.x == m_pos.front().x && p.y == m_pos.front().y)
        m_map->at(1, p.x, p.y).setColor(Color::Red);
      else
        m_map->at(1, p.x, p.y).setColor(Color::Blue);
    }
    m_lastTick = m_curTick;
  }
}

#if defined(__linux__)
WhereAmI *Snake::getWhereAmI() const
{
  WhereAmI *w = new WhereAmI;

  w->type = CommandType::WHERE_AM_I;
  w->lenght = 0;
  return (w);
}
#endif
}
