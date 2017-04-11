#include <iostream>
#include <sstream>
#include "SpaceInvader.hpp"
#include "Sprite.hpp"

namespace arcade
{
namespace game
{
namespace spaceinvader
{
SpaceInvader::SpaceInvader()
{
  Enemy new_enemy;
  Position tmp;

  std::vector<std::string> m =
      {
          "1111111111111111111111111",
          "1111111111111111111111111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111E11E11E11E11E11E11111",
          "1111111111111111111111111",
          "1111111111111111111111111",
          "1111111111111111111111111",
          "1111111111111111111111111",
          "111xxx11xxx111xxx11xxx111",
          "111x1x11x1x111x1x11x1x111",
          "1111111111111111111111111",
          "000000000000S000000000000"};

  m_map = std::make_unique<Map>(m[0].size(), m.size());
  m_map->addLayer();
  m_map->addLayer();

  //Parse map and set player and enemies position and direction
  for (size_t y = 0; y < m_map->getHeight(); ++y)
  {
    for (size_t x = 0; x < m_map->getWidth(); ++x)
    {
      TileType type;

      switch (m[y][x])
      {
      case '0':
        type = TileType::EMPTY;
        break;
      case '1':
        type = TileType::BLOCK;
        break;
      case 'x':
      {
        Obstacle new_obstacle;

        type = TileType::BLOCK;
        new_obstacle.push(Position(x, y));
        new_obstacle.setPv(3);
        m_obstacles.push_back(new_obstacle);
        break;
      }
      case 'E':
        m_enemy.push(Position(x, y));
        break;
      case 'S':
        m_player.push(Position(x, y));
        m_player.setDir(Direction::LEFT);
        break;
      }
      m_map->at(0, x, y).setType(type);
    }
  }

  m_map->clearLayer(0, Color(50, 50, 50));
  m_map->clearLayer(1);

  m_enemy.setDir(Direction::RIGHT);
  m_lastTick = 0;
  m_lastShootTick = 0;
  m_curTick = 0;
  m_hasShot = false;
}

SpaceInvader::SpaceInvader(SpaceInvader const &other)
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_obstacles = other.m_obstacles;
  m_enemy = other.m_enemy;
  m_lastTick = other.m_lastTick;
  m_lastShootTick = other.m_lastShootTick;
  m_curTick = other.m_curTick;
  m_hasShot = other.m_hasShot;
}

SpaceInvader::~SpaceInvader()
{
}

SpaceInvader &SpaceInvader::operator=(SpaceInvader const &other)
{
  if (this != &other)
  {
  }
  return (*this);
}

void SpaceInvader::notifyEvent(std::vector<Event> &&events)
{
  std::vector<Event> ev = events;

  for (Event const &e : ev)
  {
    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      switch (e.kb_key)
      {
      case KB_ARROW_LEFT:
        m_player.setDir(Direction::LEFT);
        m_player.move(*m_map);
        break;
      case KB_ARROW_RIGHT:
        m_player.setDir(Direction::RIGHT);
        m_player.move(*m_map);
        break;
      case KB_SPACE:
        if (!m_hasShot)
        {
          m_hasShot = true;
          m_shoot = *static_cast<Shoot *>(m_player.shoot().get());
          m_shoot.setDir(Direction::UP);
          m_shoot.setCurTile(m_map->at(0, m_shoot[0].x, m_shoot[0].y).getType());
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

std::vector<std::pair<std::string, SoundType>> SpaceInvader::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>> s;
  // TODO: implement
  return (s);
}

std::vector<std::unique_ptr<ISprite>> SpaceInvader::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

void SpaceInvader::checkShoot()
{
  m_shoot.move(*m_map);
  if (m_enemy.isTouch(m_shoot[0]))
  {
    m_hasShot = false;
    m_enemy.erase(m_shoot[0]);
  }

  for (std::vector<Obstacle>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
  {
    if (it->isTouch(m_shoot[0]) || m_enemy.isTouch((*it)[0]))
    {
      it->hit();
      if (it->getPv() == 0 || m_enemy.isTouch((*it)[0]))
      {
        m_map->at(0, (*it)[0].x, (*it)[0].y).setType(TileType::EMPTY);
        it = m_obstacles.erase(it);
      }
      else
        it++;
      m_hasShot = false;
    }
    else
      it++;
  }

  if (m_shoot[0].y == 0)
    m_hasShot = false;
}

void SpaceInvader::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);

  //Display player, obstacles and enemies
  m_player.display(*m_map);
  if (m_hasShot)
    m_shoot.display(*m_map);

  for (Obstacle const &o : m_obstacles)
  {
    o.display(*m_map);
  }
  m_enemy.display(*m_map);

  //Movement of the shoot ,enemy and check of collision
  if (m_hasShot && m_curTick - m_lastShootTick > 40)
  {
    checkShoot();
    m_lastShootTick = m_curTick;
  }

  if (m_curTick - m_lastTick > 300 + (100 * (m_enemy.size() / 5)))
  {
    m_enemy.move(*m_map);
    if (m_enemy.isTouch(m_player[0]))
      m_state = MENU;
    m_lastTick = m_curTick;
  }
}

#if defined(__linux__)
void SpaceInvader::WhereAmI(std::ostream &) const
{
  // TODO: implement
}

#endif
}
}
}

#if defined(__linux__)
extern "C" void Play(void)
{
  arcade::game::spaceinvader::SpaceInvader game;

  game.Play();
}
#endif
