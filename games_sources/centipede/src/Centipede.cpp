#include <iostream>
#include <sstream>
#include "Centipede.hpp"
#include "Sprite.hpp"

namespace arcade
{
namespace game
{
namespace centipede
{
Centipede::Centipede()
{
  Enemy new_enemy;
  Position tmp;

  m_map = std::make_unique<Map>(0, 0);
  m_map->loadMap("./map/centipede/map0.txt");
  m_map->addLayer();
  m_map->clearLayer(0, Color(50, 50, 50));
  m_map->clearLayer(1);
  m_player.push(Position(m_map->getWidth() / 2, m_map->getHeight() - (m_map->getHeight() / 5)));
  m_player.setDir(Direction::UP);
  new_enemy.push(Position(m_map->getWidth() / 2, 0), 10);
  new_enemy.setDir(Direction::RIGHT);
  m_enemy.push_back(new_enemy);
  for (size_t i = 0; i < 30; i++)
  {
    tmp = placeObstacle(*m_map);
    m_obstacles.push(tmp);
    m_map->at(0, tmp.x, tmp.y).setType(TileType::OBSTACLE);
  }
  m_lastTick = 0;
  m_curTick = 0;
}

Centipede::Centipede(Centipede const &other)
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_obstacles = other.m_obstacles;
  m_enemy = other.m_enemy;
  m_lastTick = other.m_lastTick;
  m_curTick = other.m_curTick;
}

Centipede::~Centipede()
{
}

Centipede &Centipede::operator=(Centipede const &other)
{
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
    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      switch (e.kb_key)
      {
      case KB_ARROW_UP:
        m_player.setDir(Direction::UP);
        m_player.move(*m_map);
        break;
      case KB_ARROW_DOWN:
        m_player.setDir(Direction::DOWN);
        m_player.move(*m_map);
        break;
      case KB_ARROW_LEFT:
        m_player.setDir(Direction::LEFT);
        m_player.move(*m_map);
        break;
      case KB_ARROW_RIGHT:
        m_player.setDir(Direction::RIGHT);
        m_player.move(*m_map);
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
  std::vector<std::pair<std::string, SoundType>> s;
  // TODO: implement
  return (s);
}

std::vector<std::unique_ptr<ISprite>> Centipede::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

void Centipede::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);
  m_player.display(*m_map);
  m_obstacles.display(*m_map);
  for (Enemy const &e : m_enemy)
  {
    e.display(*m_map);
  }

  if (m_curTick - m_lastTick > 100)
  {
    for (Enemy &e : m_enemy)
    {
      e.move(*m_map);
    }
    m_lastTick = m_curTick;
  }
}

#if defined(__linux__)
WhereAmI *Centipede::getWhereAmI() const
{
  // TODO: implement
  return (nullptr);
}

Position Centipede::placeObstacle(Map const &map) const
{
  size_t width = map.getWidth();
  size_t height = map.getHeight();

  // Try to place random
  for (size_t i = 0; i < 10000; ++i)
  {
    Position p(rand() % width, rand() % (height - (height / 5)));

    if (map.at(0, p.x, p.y).getType() != TileType::EMPTY && m_obstacles.isTouch(p) == false)
    {
      return (p);
    }
  }
  return (Position(0, 0));
}
#endif
}
}
}

extern "C" void Play(void)
{
  arcade::game::centipede::Centipede game;

  game.Play();
}