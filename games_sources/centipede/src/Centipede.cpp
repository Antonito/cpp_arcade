#include <iostream>
#include <unistd.h>
#include "Sprite.hpp"
#include "Centipede.hpp"

namespace arcade
{
Centipede::Centipede()
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

  m_player = Player(Pos(width / 2, height - ((height / 5) / 2)), Dir::UP);
  m_centipedes.push_back(Enemy(Pos(width / 2, 0), Dir::RIGHT, 8));
  placeObstacles();
  isShot = false;
  m_lastTickPlayer = 0;
  m_lastTickCenti = 0;
  m_lastTickShoot = 0;
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

  // TODO : also copy layers

  m_map = std::make_unique<Map>(width, height);
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      m_map->at(0, x, y).setColor(Color::White);
    }
  };

  m_player = Player(Pos(width / 2, height - ((height / 5) / 2)), Dir::UP);
  m_centipedes.push_back(Enemy(Pos(width / 2, 0), Dir::RIGHT, 8));
  placeObstacles();
  isShot = false;
  m_lastTickPlayer = 0;
  m_lastTickCenti = 0;
  m_lastTickShoot = 0;
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
        if (static_cast<size_t>(m_player.getPos().getY()) > m_map->getHeight() - (m_map->getHeight() / 5) - 1)
        {
          m_player.move(*m_map, Dir::UP);
        }
        break;
      case KB_ARROW_DOWN:
        if (static_cast<size_t>(m_player.getPos().getY()) < m_map->getHeight() - 1)
        {
          m_player.move(*m_map, Dir::DOWN);
        }
        break;
      case KB_ARROW_LEFT:
        if (m_player.getPos().getX() > 0)
        {
          m_player.move(*m_map, Dir::LEFT);
        }
        break;
      case KB_ARROW_RIGHT:
        if (static_cast<size_t>(m_player.getPos().getX()) < m_map->getWidth() - 1)
        {
          m_player.move(*m_map, Dir::RIGHT);
        }
        break;
      case KB_SPACE:
        if (!isShot)
        {
          m_shoot = m_player.shoot(*m_map);
          isShot = true;
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

std::vector<std::unique_ptr<ISprite>> Centipede::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  //s.push_back(std::unique_ptr<ISprite>(new Sprite("assets/centipede/", "player", 1, ".png", "O")));
  s.push_back(std::make_unique<Sprite>("./assets/centipede/", "player", 1, ".png", "A"));
  s.push_back(std::make_unique<Sprite>("./assets/centipede/", "shoot", 2, ".png", "oo"));
  s.push_back(std::make_unique<Sprite>("./assets/centipede/", "block", 1, ".png", "#"));
  return (s);
}

void Centipede::placeObstacles()
{
  for (int i = 0; i < 5; i++)
  {
    m_obstacles.push_back(Obstacle(*m_map, true,
                                   Pos(rand() % m_map->getWidth(),
                                       rand() % (m_map->getHeight() - (m_map->getHeight() / 5) - 1)),
                                   5));
  }
}

void Centipede::process()
{

  //TODO: Use std::chrono
  m_curTick = this->getCurrentTick();

  for (size_t y = 0; y < m_map->getHeight(); ++y)
  {
    for (size_t x = 0; x < m_map->getWidth(); ++x)
    {
      m_map->at(0, x, y).setColor(Color(20, 20, 20));
      m_map->at(1, x, y).setColor(Color::Transparent);
      m_map->at(1, x, y).removeSprite();
    }
  };
  // Obstacles display and check destructed obstacles
  for (std::vector<Obstacle>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
  {
    if (it->getPv() == 0)
      it = m_obstacles.erase(it);
    else
    {
      it->display(*m_map);
      it++;
    }
  }
  // Centipedes display

  for (Enemy const &c : m_centipedes)
  {
    c.display(*m_map);
  }

  //Player display
  m_player.display(*m_map);

  //Missile display
  if (isShot)
  {
    m_shoot.display(*m_map);
  }

  // Make  the centipedes move at each tik

  if ((m_curTick - m_lastTickCenti) > 300)
  {
    for (Enemy &c : m_centipedes)
    {
      if (c.touchObstacle(*m_map, m_obstacles))
        c.rotate(*m_map);
      else
        c.move(*m_map, c.getDir());
    }
    m_lastTickCenti = m_curTick;
  }
  // Missile move and check hit
  if (isShot && (m_curTick - m_lastTickShoot) > 30)
  {
    m_shoot.move(*m_map, Dir::UP);
    if (m_shoot.touchCenti(m_centipedes, m_obstacles, *m_map) ||
        m_shoot.touchObstacles(m_obstacles) ||
        !m_shoot.getPos().inMap(*m_map))
    {
      isShot = false;
    }
    m_lastTickShoot = m_curTick;
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