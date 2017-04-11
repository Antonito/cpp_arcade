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
  std::vector<std::string> m =
      {
          "1##################",
          "#........#........#",
          "#U##.###.#.###.##U#",
          "#.................#",
          "#.##.#.#####.#.##.#",
          "#....#...#...#....#",
          "####.###.#.###.####",
          "####.#.......#.####",
          "####.#.## ##.#.####",
          "    ...#xEx#...    ",
          "####.#.#xxx#.#.####",
          "####.#.#####.#.####",
          "####.#...S...#.####",
          "####.#.#####.#.####",
          "#........#........#",
          "#.##.###.#.###.##.#",
          "#..#...........#..#",
          "##.#.#.#####.#.#.##",
          "#....#...#...#....#",
          "#U######.#.######U#",
          "#.................#",
          "###################",
      };

  m_map = std::make_unique<Map>(m[0].size(), m.size());
  m_map->addLayer();
  m_map->addLayer();
  m_map->clearLayer(0, Color(50, 50, 50));

  //Parse map and set powerups, player and enemies position and direction
  for (size_t y = 0; y < m_map->getHeight(); ++y)
  {
    for (size_t x = 0; x < m_map->getWidth(); ++x)
    {
      TileType type;

      switch (m[y][x])
      {
      case ' ':
        type = TileType::EMPTY;
        break;
      case '#':
        type = TileType::BLOCK;
        m_map->at(0, x, y).setColor(Color::Black);
        break;
      case 'x':
        type = TileType::BLOCK;
        break;
      case '.':
        type = TileType::POWERUP;
        m_powerups.push(Position(x, y));
        break;
      case 'U':
        type = TileType::POWERUP;
        m_superPowers.push(Position(x, y));
        break;
      case 'S':
        type = TileType::EMPTY;
        m_player.push(Position(x, y));
        m_player.setDir(Direction::RIGHT);
        break;
      case 'E':
        type = TileType::EMPTY;
        new_enemy.push(Position(x, y));
        new_enemy.setDir(Direction::UP);
        for (size_t i = 0; i < 4; i++)
        {
          m_enemy.push_back(new_enemy);
        }
        break;
      }
      m_map->at(0, x, y).setType(type);
    }
  }
  //Clear layer 1 and 2
  m_map->clearLayer(1);

  m_lastTick = 0;
  m_lastGhostTick = 0;
  m_startTick = 0;
  m_nextDir = Direction::RIGHT;
  m_curTick = 0;
  m_eatTime = 0;
  m_hasEat = false;
}

Pacman::Pacman(Pacman const &other) : AGame()
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_powerups = other.m_powerups;
  m_enemy = other.m_enemy;
  m_lastGhostTick = other.m_lastGhostTick;
  m_lastTick = other.m_lastTick;
  m_startTick = other.m_startTick;
  m_curTick = other.m_curTick;
  m_nextDir = other.m_nextDir;
  m_hasEat = other.m_hasEat;
  m_eatTime = other.m_eatTime;
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
      case KB_ENTER:
        if (m_finished)
          m_state = MENU;
        break;
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

void Pacman::checkEnemy()
{
  for (Enemy &e : m_enemy)
  {
    if (e[0] == m_player[0])
    {
      if (e.getEatable())
      {
        e.setDead(true);
        m_score += 100;
        e.setDeathTime(this->getCurrentTick());
      }
      else
      {
        m_finished = true;
        return;
      }
    }
  }
}

void Pacman::checkPowerUps()
{
  if (m_powerups.size() == 0)
  {
    m_finished = true;
    return;
  }
  if (m_powerups.isTouch(m_player[0]))
  {
    m_score += 5;
    m_powerups.erase(m_player[0]);
  }
}

void Pacman::checkSuperPowers()
{
  if (m_superPowers.isTouch(m_player[0]))
  {
    m_hasEat = true;
    for (Enemy &e : m_enemy)
    {
      if (!e.getDead())
      {
        e.setEatable(true);
      }
    }
    m_hasEat = true;
    m_eatTime = this->getCurrentTick();
    m_superPowers.erase(m_player[0]);
  }
}

void Pacman::unsetSuperPowers()
{
  for (Enemy &e : m_enemy)
  {
    e.setEatable(false);
  }
  m_hasEat = false;
}

void Pacman::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);

  // Display player, and powerups
  m_powerups.display(*m_map);
  m_superPowers.display(*m_map);
  m_player.display(*m_map);

  for (Enemy const &e : m_enemy)
  {
    e.display(*m_map);
  }

  if (!m_start && m_curTick - m_startTick > 10000)
  {
    m_start = true;
    m_startTick = m_curTick;
  }

  if (m_start && m_curTick - m_lastGhostTick > 300)
  {
    for (Enemy &e : m_enemy)
    {
      e.move(*m_map);
    }
    m_lastGhostTick = m_curTick;
  }

  if (m_curTick - m_lastTick > 200)
  {
    // Check colision
    checkEnemy();
    checkPowerUps();
    checkSuperPowers();
    if (m_hasEat && m_curTick - m_eatTime > 10000)
      unsetSuperPowers();
    m_player.setNextDir(m_nextDir);
    m_player.move(*m_map);
    m_lastTick = m_curTick;
  }
}

#if defined(__linux__)
void Pacman::WhereAmI(std::ostream &os) const
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
  arcade::game::pacman::Pacman game;

  game.Play();
}
#endif
