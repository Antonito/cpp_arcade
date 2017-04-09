#include <iostream>
#include <sstream>
#include "Pacman.hpp"
#include "Sprite.hpp"

namespace arcade
{
namespace game
{
namespace pacman
{
Pacman::Pacman()
{
  Enemy new_enemy;

  m_map = std::make_unique<Map>(0, 0);
  m_map->loadMap("./map/pacman/map0.txt");
  m_map->addLayer();
  m_map->clearLayer(0, Color(50, 50, 50));
  m_map->clearLayer(1);
  for (size_t y = 0; y < m_map->getHeight(); y++)
  {
    for (size_t x = 0; x < m_map->getWidth(); x++)
    {
      if (m_map->at(0, x, y).getType() == TileType::BLOCK)
        m_map->at(0, x, y).setColor(Color::Black);
      else if (m_map->at(0, x, y).getType() == TileType::POWERUP)
        m_powerups.push(Position(x, y));
    }
  }
  m_player.push(Position(9, 12));
  m_player.setDir(Direction::RIGHT);
  new_enemy.push(Position(10, 9));
  new_enemy.setDir(Direction::UP);
  for (size_t i = 0; i < 4; i++)
  {
    m_enemy.push_back(new_enemy);
  }
  m_lastTick = 0;
  m_nextDir = Direction::RIGHT;
  m_curTick = 0;
}

Pacman::Pacman(Pacman const &other)
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_powerups = other.m_powerups;
  m_enemy = other.m_enemy;
  m_lastTick = other.m_lastTick;
  m_curTick = other.m_curTick;
  m_nextDir = other.m_nextDir;
}

Pacman::~Pacman()
{
}

Pacman &Pacman::operator=(Pacman const &other)
{
  if (this != &other)
  {
  }
  return (*this);
}

void Pacman::notifyEvent(std::vector<Event> &&events)
{
  std::vector<Event> ev = events;
  Direction tmpDir;

  for (Event const &e : ev)
  {
    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      tmpDir = m_player.getDir();
      switch (e.kb_key)
      {
      case KB_ARROW_UP:
        m_player.setDir(Direction::UP);
        m_nextDir = Direction::UP;
        if (m_map->at(0, m_player.next().x, m_player.next().y).getType() == TileType::BLOCK)
          m_player.setDir(tmpDir);
        break;
      case KB_ARROW_DOWN:
        m_player.setDir(Direction::DOWN);
        m_nextDir = Direction::DOWN;
        if (m_map->at(0, m_player.next().x, m_player.next().y).getType() == TileType::BLOCK)
          m_player.setDir(tmpDir);
        break;
      case KB_ARROW_LEFT:
        m_player.setDir(Direction::LEFT);
        m_nextDir = Direction::LEFT;
        if (m_map->at(0, m_player.next().x, m_player.next().y).getType() == TileType::BLOCK)
          m_player.setDir(tmpDir);
        break;
      case KB_ARROW_RIGHT:
        m_player.setDir(Direction::RIGHT);
        m_nextDir = Direction::RIGHT;
        if (m_map->at(0, m_player.next().x, m_player.next().y).getType() == TileType::BLOCK)
          m_player.setDir(tmpDir);
        break;
      case KB_ESCAPE:
        m_state = MENU;
      default:
        break;
      }
    }
  }
}

std::vector<std::pair<std::string, SoundType>> Pacman::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>> s;
  // TODO: implement
  return (s);
}

std::vector<std::unique_ptr<ISprite>> Pacman::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

void Pacman::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);
  m_powerups.display(*m_map);
  m_player.display(*m_map);
  for (Enemy const &e : m_enemy)
  {
    e.display(*m_map);
  }

  if (m_curTick - m_lastTick > 130)
  {
    if (m_powerups.isTouch(m_player[0]))
    {
      m_powerups.erase(m_player[0]);
    }
    if (m_powerups.size() == 0)
      m_state = MENU;
    m_player.move(*m_map, m_nextDir);
    m_lastTick = m_curTick;
  }
}

#if defined(__linux__)
void Pacman::WhereAmI(std::ostream &) const
{
  // TODO: implement
}

#endif
}
}
}

extern "C" void Play(void)
{
  arcade::game::pacman::Pacman game;

  game.Play();
}