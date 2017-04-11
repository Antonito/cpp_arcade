#include <iostream>
#include <sstream>
#include "Qix.hpp"
#include "Sprite.hpp"

namespace arcade
{
namespace game
{
namespace qix
{
Qix::Qix()
{
  Enemy new_enemy;
  Position tmp;

  std::vector<std::string> m =
      {"0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000",
       "0000000000000000000000000"};

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
      }
      m_map->at(0, x, y).setType(type);
    }
  }

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
    m_obstacles.push_back(Obstacle());
    m_obstacles[i].push(tmp);
    m_obstacles[i].setPv(5);
    m_map->at(0, tmp.x, tmp.y).setType(TileType::OBSTACLE);
  }

  m_lastTick = 0;
  m_lastShootTick = 0;
  m_curTick = 0;
  m_hasShot = false;
}

Qix::Qix(Qix const &other) : AGame()
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

Qix::~Qix()
{
}

Qix &Qix::operator=(Qix const &other)
{
  if (this != &other)
  {
  }
  return (*this);
}

void Qix::notifyEvent(std::vector<Event> &&events)
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

std::vector<std::pair<std::string, SoundType>> Qix::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>> s;
  // TODO: implement
  return (s);
}

std::vector<std::unique_ptr<ISprite>> Qix::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

void Qix::checkShoot()
{
  m_shoot.move(*m_map);
  for (Enemy &e : m_enemy)
  {
    if (e.isTouch(m_shoot[0]))
    {
      // split Qix
      m_hasShot = false;
    }
  }

  for (std::vector<Obstacle>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
  {
    if (it->isTouch(m_shoot[0]))
    {
      it->hit();
      if (it->getPv() == 0)
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

void Qix::process()
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

  for (Enemy const &e : m_enemy)
  {
    e.display(*m_map);
  }

  //Movement of the shoot ,enemy and check of collision
  if (m_hasShot && m_curTick - m_lastShootTick > 40)
  {
    checkShoot();
    m_lastShootTick = m_curTick;
  }

  if (m_curTick - m_lastTick > 5)
  {
    for (Enemy &e : m_enemy)
    {
      e.move(*m_map);
      if (e.isTouch(m_player[0]))
        m_state = MENU;
    }
    m_lastTick = m_curTick;
  }
}

Position Qix::placeObstacle(Map const &map) const
{
  size_t width = map.getWidth();
  size_t height = map.getHeight();

  // Try to place random
  for (size_t i = 0; i < 10000; ++i)
  {
    Position p(rand() % width, rand() % (height - (height / 5)));

    for (Obstacle const &o : m_obstacles)
    {
      if (o.isTouch(p))
        continue;
    }

    if (map.at(0, p.x, p.y).getType() != TileType::EMPTY)
    {
      return (p);
    }
  }
  return (Position(0, 0));
}

#if defined(__linux__)
void Qix::WhereAmI(std::ostream &os) const
{
  uint16_t size = static_cast<uint16_t>(m_player.size());
  arcade::WhereAmI header = {CommandType::WHERE_AM_I, size};
  std::unique_ptr<::arcade::Position[]> pos(new ::arcade::Position[size]);

  for (size_t i = 0; i < size; ++i)
  {
    pos[i].x = m_player[i].x;
    pos[i].y = m_player[i].y;
  }

  os.write(reinterpret_cast<char *>(&header), sizeof(arcade::WhereAmI));
  os.write(reinterpret_cast<char *>(pos.get()), size * sizeof(::arcade::Position));
}

#endif
}
}
}

#if defined(__linux__)
extern "C" void Play(void)
{
  arcade::game::Qix::Qix game;

  game.Play();
}
#endif
