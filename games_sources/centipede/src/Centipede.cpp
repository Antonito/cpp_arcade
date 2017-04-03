#include <iostream>
#include <unistd.h>
#include "Centipede.hpp"

namespace arcade
{
Centipede::Centipede()
{
  constexpr size_t width = 24;
  constexpr size_t height = 24;
  t_centipede centi;
  t_pos start_centi;

  m_pos.x = width / 2;
  m_pos.y = height - ((height / 5) / 2);
  m_map = std::make_unique<Map>(width, height);
  start_centi.x = width / 2;
  start_centi.y = 0;
  for (int i = 0; i < 8; i++)
    centi.part.push_back(start_centi);
  centi.dir = RIGHT;
  isShot = false;
  m_centipedes.push_back(centi);
  placeObstacles();
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      m_map->at(0, x, y).setColor(Color::White);
    }
  };

  m_map->addLayer();
  m_gui = std::make_unique<GUI>();

  Component comp;

  comp.setX(0.05);
  comp.setY(0.05);
  comp.setWidth(0.15);
  comp.setHeight(0.05);
  comp.setBackgroundColor(Color(0, 0, 0, 170));
  m_gui->push(std::move(comp));
}

Centipede::Centipede(Centipede const &other)
{
  size_t width = other.m_map->getWidth();
  size_t height = other.m_map->getHeight();
  t_centipede centi;
  t_pos start_centi;

  m_pos.x = width / 2;
  m_pos.y = height - ((height / 5) / 2);
  start_centi.x = width / 2;
  start_centi.y = 0;
  for (int i = 0; i < 8; i++)
    centi.part.push_back(start_centi);
  centi.dir = RIGHT;
  isShot = false;
  m_centipedes.push_back(centi);
  placeObstacles();

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

Centipede::~Centipede()
{
}

Centipede &Centipede::operator=(Centipede const &other)
{
  std::cout << "eq" << std::endl;
  if (this != &other)
  {
  }
  return (*this);
}

void Centipede::notifyEvent(std::vector<Event> &&events)
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
        if (m_pos.y > m_map->getHeight() - (m_map->getHeight() / 5) - 1)
        {
          m_pos.y -= 1;
        }
        break;
      case KB_ARROW_DOWN:
        if (m_pos.y < m_map->getHeight() - 1)
        {
          m_pos.y += 1;
        }
        break;
      case KB_ARROW_LEFT:
        if (m_pos.x > 0)
        {
          m_pos.x -= 1;
        }
        break;
      case KB_ARROW_RIGHT:
        if (m_pos.x < m_map->getWidth() - 1)
        {
          m_pos.x += 1;
        }
        break;
      case KB_SPACE:
        if (!isShot)
        {
          isShot = true;
          m_shoot.x = m_pos.x;
          m_shoot.y = m_pos.y;
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

std::vector<std::string> Centipede::getSoundsToLoad() const
{
  // TODO: implement
  return (std::vector<std::string>());
}

std::vector<std::unique_ptr<ISprite>> &&Centipede::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (std::move(s));
}

bool Centipede::touchObstacle(t_centipede const &centi, t_pos &next)
{
  if (next.x < 0 || next.x > m_map->getWidth() - 1)
  {
    next.x = centi.part.front().x;
    next.y = centi.part.front().y + 1;
    return true;
  }
  for (t_obstacle const &obs : m_obstacles)
  {
    if (obs.pos.x == next.x && obs.pos.y == next.y)
    {
      next.x = centi.part.front().x;
      next.y = centi.part.front().y + 1;
      return true;
    }
  }
  return false;
}

void Centipede::splitCentipede(size_t i, size_t j)
{
  t_obstacle new_obs;
  t_centipede new_centi;
  std::vector<t_pos> new_part(m_centipedes[i].part.begin() + j, m_centipedes[i].part.end());

  new_obs.pos.x = m_centipedes[i].part[j].x;
  new_obs.pos.y = m_centipedes[i].part[j].y;
  new_obs.life = 5;
  m_obstacles.push_back(new_obs);
  if (m_centipedes[i].dir == RIGHT)
    new_centi.dir = LEFT;
  else
    new_centi.dir = RIGHT;
  new_centi.part = new_part;
  m_centipedes[i].part.resize(j - 1);
  m_centipedes.push_back(new_centi);
}

void Centipede::moveCentipedes()
{
  t_pos next;

  for (t_centipede &centi : m_centipedes)
  {
    centi.part.pop_back();
    if ((centi.part.front().x == m_pos.x && centi.part.front().y == m_pos.y) ||
        centi.part.front().y == m_map->getHeight() - 1)
    {
      m_state = MENU;
      return;
    }
    if (centi.dir == LEFT)
    {
      next.x = centi.part.front().x - 1;
      next.y = centi.part.front().y;
      if (touchObstacle(centi, next))
      {
        centi.dir = RIGHT;
      }
    }
    else if (centi.dir == RIGHT)
    {
      next.x = centi.part.front().x + 1;
      next.y = centi.part.front().y;
      if (touchObstacle(centi, next))
      {
        centi.dir = LEFT;
      }
    }
    centi.part.insert(centi.part.begin(), next);
  }
}

void Centipede::placeObstacles()
{
  t_pos new_obs_pos;
  t_obstacle new_obs;

  for (int i = 0; i < 10; i++)
  {
    new_obs_pos.x = rand() % m_map->getWidth();
    new_obs_pos.y = rand() % (m_map->getHeight() - (m_map->getHeight() / 5) - 1);
    new_obs.pos = new_obs_pos;
    new_obs.life = 5;
    m_obstacles.push_back(new_obs);
  }
}

bool Centipede::touchTarget()
{
  size_t i = 0;
  size_t j = 0;

  //Check if the shot go out of map
  if (m_shoot.y == 0)
  {
    return true;
  }

  //Check if the shot touch an Obstacles
  for (t_obstacle const &obs : m_obstacles)
  {
    if (obs.pos.x == m_shoot.x && obs.pos.y == m_shoot.y)
    {
      obs.life -= 1;
      return true;
    }

    // check if the shot touch a Centipede
    // for (t_centipede const &centi : m_centipedes)
    // {
    //   i++;
    //   j = 0;
    //   for (t_pos const &pos : centi.part)
    //   {
    //     j++;
    //     if (pos.x == m_shoot.x && pos.y == m_shoot.y)
    //     {
    //       //splitCentipede(i, j);
    //       return true;
    //     }
    //   }
    // }
  }

  return false;
}

void Centipede::process()
{

  //TODO: Use std::chrono
  usleep(100000);

  for (size_t y = 0; y < m_map->getHeight(); ++y)
  {
    for (size_t x = 0; x < m_map->getWidth(); ++x)
    {
      m_map->at(1, x, y).setColor(Color::Transparent);
    }
  };

  // Make  the centipedes move at each tik
  moveCentipedes();

  // Missile display
  if (isShot)
  {
    if (touchTarget())
    {
      isShot = false;
    }
    else
    {
      m_map->at(1, m_shoot.x, m_shoot.y).setColor(Color::Yellow);
      m_shoot.y -= 1;
    }
  }

  // Obstacles display
  for (t_obstacle const &obs : m_obstacles)
  {
    m_map->at(1, obs.pos.x, obs.pos.y).setColor(Color::Red);
  }

  // Centipedes display
  for (t_centipede const &centi : m_centipedes)
  {
    for (t_pos const &pos : centi.part)
      m_map->at(1, pos.x, pos.y).setColor(Color::Blue);
  }
  m_map->at(1, m_pos.x, m_pos.y).setColor(Color::Green);
}

WhereAmI *Centipede::getWhereAmI() const
{
  WhereAmI *w = new WhereAmI;

  w->type = CommandType::WHERE_AM_I;
  w->lenght = 0;
  return (w);
}
}