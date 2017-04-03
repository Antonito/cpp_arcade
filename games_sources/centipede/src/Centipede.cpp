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
  for (int i = 0; i < 15; i++)
    centi.part.push_back(start_centi);
  centi.dir = RIGHT;
  isShot = false;
  m_centipedes.push_back(centi);
  placeObstacles();
  m_lastTickPlayer = 0;
  m_lastTickCenti = 0;
  m_lastTickShoot = 0;
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
  m_lastTickPlayer = 0;
  m_lastTickCenti = 0;
  m_lastTickShoot = 0;

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
        if (static_cast<size_t>(m_pos.y) > m_map->getHeight() - (m_map->getHeight() / 5) - 1)
        {
          m_pos.y -= 1;
        }
        break;
      case KB_ARROW_DOWN:
        if (static_cast<size_t>(m_pos.y) < m_map->getHeight() - 1)
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
        if (static_cast<size_t>(m_pos.x) < m_map->getWidth() - 1)
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

std::vector<std::pair<std::string, SoundType>> Centipede::getSoundsToLoad() const
{
  // TODO: implement
  return (std::vector<std::pair<std::string, SoundType>>());
}

std::vector<std::unique_ptr<ISprite>> &&Centipede::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (std::move(s));
}

bool Centipede::touchObstacle(t_centipede const &centi, t_pos &next)
{
  if (next.x < 0 || static_cast<size_t>(next.x) > m_map->getWidth() - 1)
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

  std::cout << "j = " << j << std::endl;
  std::cout << "i = " << i << std::endl;
  std::cout << "size = " << m_centipedes[i].part.size() << std::endl;
  new_obs.pos.x = m_centipedes[i].part[j].x;
  new_obs.pos.y = m_centipedes[i].part[j].y;
  new_obs.life = 5;
  m_obstacles.push_back(new_obs);

  // Check Start of the tail
  if (j == 0)
  {
    std::cout << "START TAIL" << std::endl;
    m_centipedes[i].part.erase(m_centipedes[i].part.begin());
    if (m_centipedes[i].part.size() == 0)
      m_centipedes.erase(m_centipedes.begin() + i);
  }
  else if (j == m_centipedes[i].part.size() - 1)
  {
    std::cout << "END TAIL" << std::endl;
    m_centipedes[i].part.pop_back();
    if (m_centipedes[i].part.size() == 0)
      m_centipedes.erase(m_centipedes.begin() + i);
  }
  else
  {
    std::vector<t_pos> new_part(m_centipedes[i].part.begin() + j, m_centipedes[i].part.end());

    new_centi.dir = m_centipedes[i].dir;
    new_centi.part = new_part;
    m_centipedes[i].part.resize(j - 1);
    m_centipedes.push_back(new_centi);
  }
}

void Centipede::moveCentipedes()
{
  t_pos next;

  for (t_centipede &centi : m_centipedes)
  {
    centi.part.pop_back();
    if ((centi.part.front().x == m_pos.x && centi.part.front().y == m_pos.y) ||
        static_cast<size_t>(centi.part.front().y) == m_map->getHeight() - 1)
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

  for (int i = 0; i < 5; i++)
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

  //Check if the shot touch an Obstacles
  for (t_obstacle &obs : m_obstacles)
  {
    if (obs.pos.x == m_shoot.x && obs.pos.y == m_shoot.y)
    {
      obs.life -= 1;
      return true;
    }
  }

  // check if the shot touch a Centipede
  for (t_centipede const &centi : m_centipedes)
  {
    j = 0;
    for (t_pos const &pos : centi.part)
    {
      if (pos.x == m_shoot.x && pos.y == m_shoot.y)
      {
        splitCentipede(i, j);
        return true;
      }
      j++;
    }
    i++;
  }

  //Check if the shot go out of map
  if (m_shoot.y == 0)
  {
    return true;
  }

  return false;
}

void Centipede::process()
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
  // Obstacles display and check destructed obstacles
  for (std::vector<Centipede::t_obstacle>::iterator it = m_obstacles.begin();
       it != m_obstacles.end();)
  {
    if (it->life <= 0)
    {
      it = m_obstacles.erase(it);
    }
    else
    {
      m_map->at(1, it->pos.x, it->pos.y).setColor(Color::Red);
      ++it;
    }
  }
  // Centipedes display
  for (t_centipede const &centi : m_centipedes)
  {
    for (t_pos const &pos : centi.part)
      m_map->at(1, pos.x, pos.y).setColor(Color::Blue);
  }

  //Player display
  m_map->at(1, m_pos.x, m_pos.y).setColor(Color::Green);

  //Missile display
  if (isShot)
  {
    m_map->at(1, m_shoot.x, m_shoot.y).setColor(Color::Yellow);
  }

  // Make  the centipedes move at each tik

  if ((m_curTick - m_lastTickCenti) > 300)
  {
    moveCentipedes();
    m_lastTickCenti = m_curTick;
  }
  // Missile display
  if (isShot && (m_curTick - m_lastTickShoot) > 30)
  {
    if (touchTarget())
    {
      isShot = false;
    }
    else
    {
      m_shoot.y -= 1;
    }
    m_lastTickShoot = m_curTick;
  }

  // Player display
  if ((m_curTick - m_lastTickPlayer) > 60)
  {

    m_lastTickPlayer = m_curTick;
  }
}

WhereAmI *Centipede::getWhereAmI() const
{
  WhereAmI *w = new WhereAmI;

  w->type = CommandType::WHERE_AM_I;
  w->lenght = 0;
  return (w);
}
}