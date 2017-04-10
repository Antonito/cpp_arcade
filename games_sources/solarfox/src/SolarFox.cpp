#include <iostream>
#include <sstream>
#include "SolarFox.hpp"
#include "Sprite.hpp"

namespace arcade
{
namespace game
{
namespace solarfox
{
SolarFox::SolarFox()
{
  Position tmp;

  std::vector<std::string> m =
      {
          "111111111111D111111111111",
          "1111111111111111111111111",
          "1111111111111111111111111",
          "1110000000000000000000111",
          "1110000000000000000000111",
          "1110000000000000000000111",
          "1110000xxxxxxxxxxx0000111",
          "1110000x000000000x0000111",
          "1110000x0xxxxxxx0x0000111",
          "1110000x0x00000x0x0000111",
          "1110000x0x0xxx0x0x0000111",
          "1110000x0x0x0x0x0x0000111",
          "R110000x0x0xSx0x0x000011L",
          "1110000x0x0x0x0x0x0000111",
          "1110000x0x0xxx0x0x0000111",
          "1110000x0x00000x0x0000111",
          "1110000x0xxxxxxx0x0000111",
          "1110000x000000000x0000111",
          "1110000xxxxxxxxxxx0000111",
          "1110000000000000000000111",
          "1110000000000000000000111",
          "1110000000000000000000111",
          "1111111111111111111111111",
          "1111111111111111111111111",
          "111111111111U111111111111"};

  m_map = std::make_unique<Map>(m[0].size(), m.size());
  m_map->addLayer();
  m_map->addLayer();
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
      case 'S':
        type = TileType::EMPTY;
        m_player.push(Position(x, y));
        m_player.setDir(Direction::UP);
        break;
      case 'x':
        type = TileType::POWERUP;
        m_powerups.push(Position(x, y));
        break;
      case 'U':
      {
        Enemy enemy_up;

        type = TileType::BLOCK;
        enemy_up.push(Position(x, y));
        enemy_up.setShootDir(Direction::UP);
        enemy_up.setDir(Direction::LEFT);
        m_enemies.push_back(enemy_up);

        break;
      }
      case 'D':
      {
        Enemy enemy_down;

        type = TileType::BLOCK;
        enemy_down.push(Position(x, y));
        enemy_down.setShootDir(Direction::DOWN);
        enemy_down.setDir(Direction::RIGHT);
        m_enemies.push_back(enemy_down);
        break;
      }
      case 'L':
      {
        Enemy enemy_left;

        type = TileType::BLOCK;
        enemy_left.push(Position(x, y));
        enemy_left.setShootDir(Direction::LEFT);
        enemy_left.setDir(Direction::UP);
        m_enemies.push_back(enemy_left);
        break;
      }
      case 'R':
      {
        Enemy enemy_right;

        type = TileType::BLOCK;
        enemy_right.push(Position(x, y));
        enemy_right.setShootDir(Direction::RIGHT);
        enemy_right.setDir(Direction::DOWN);
        m_enemies.push_back(enemy_right);
        break;
      }
      }
      m_map->at(0, x, y).setType(type);
    }
  }
  m_map->clearLayer(0, Color(50, 50, 50));
  m_map->clearLayer(1);

  m_hasShot = false;
  m_lastTick = 0;
  m_lastShootTick = 0;
  m_lastEvilShootTick = 0;
  m_lastEvilSalveTick = 0;
  m_lastEvilTick = 0;
  m_curTick = 0;
}

SolarFox::SolarFox(SolarFox const &other)
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_enemies = other.m_enemies;
  m_powerups = other.m_powerups;
  m_lastTick = other.m_lastTick;
  m_lastShootTick = other.m_lastShootTick;
  m_curTick = other.m_curTick;
  m_hasShot = other.m_hasShot;
  m_lastEvilShootTick = other.m_lastEvilShootTick;
  m_lastEvilSalveTick = other.m_lastEvilSalveTick;
  m_lastEvilTick = other.m_lastEvilTick;
}

SolarFox::~SolarFox()
{
}

SolarFox &SolarFox::operator=(SolarFox const &other)
{
  if (this != &other)
  {
  }
  return (*this);
}

void SolarFox::notifyEvent(std::vector<Event> &&events)
{
  std::vector<Event> ev = events;

  for (Event const &e : ev)
  {
    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      switch (e.kb_key)
      {
      case KB_ARROW_UP:
        if (m_player.getDir() != Direction::DOWN)
          m_player.setDir(Direction::UP);
        break;
      case KB_ARROW_DOWN:
        if (m_player.getDir() != Direction::UP)
          m_player.setDir(Direction::DOWN);
        break;
      case KB_ARROW_LEFT:
        if (m_player.getDir() != Direction::RIGHT)
          m_player.setDir(Direction::LEFT);
        break;
      case KB_ARROW_RIGHT:
        if (m_player.getDir() != Direction::LEFT)
          m_player.setDir(Direction::RIGHT);
        break;
      case KB_SPACE:
        if (!m_hasShot)
        {
          m_hasShot = true;
          m_shoot = *static_cast<Shoot *>(m_player.shoot().get());
          m_shoot.setDir(m_player.getDir());
          m_shoot.setCurTile(m_map->at(0, m_shoot[0].x, m_shoot[0].y).getType());
          m_shoot.setRange(3);
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

std::vector<std::pair<std::string, SoundType>> SolarFox::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>> s;
  // TODO: implement
  return (s);
}

std::vector<std::unique_ptr<ISprite>> SolarFox::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  return (s);
}

void SolarFox::checkPowerUps()
{
  if (m_powerups.size() == 0)
    m_state = MENU;
  if (m_hasShot && m_powerups.isTouch(m_shoot[0]))
  {
    // up score
    m_hasShot = false;
    m_map->at(0, m_shoot[0].x, m_shoot[0].y).setType(m_shoot.getCurTile());
    m_powerups.erase(m_shoot[0]);
  }
}

bool SolarFox::checkShoot(Position pos)
{
  if (pos == m_player[0])
  {
    m_state = MENU;
    return true;
  }
  if (m_hasShot && pos == m_shoot[0])
    return true;
  return false;
}

void SolarFox::moveEvilShoot(size_t speed)
{
  if (m_curTick - m_lastEvilShootTick > speed)
  {
    for (std::vector<EvilShoot>::iterator it = m_evilShoot.begin(); it != m_evilShoot.end();)
    {
      if (checkShoot((*it)[0]) || !it->next().inMap(*m_map))
        it = m_evilShoot.erase(it);
      else
      {
        it->move(*m_map);
        it++;
      }
    }
    m_lastEvilShootTick = m_curTick;
  }
}

void SolarFox::moveEvilDude(size_t speed)
{
  if (m_curTick - m_lastEvilTick > speed)
  {
    for (Enemy &e : m_enemies)
    {
      if (e.getShootDir() == Direction::UP || e.getShootDir() == Direction::DOWN)
        e.setDir(static_cast<Direction>(2 + rand() % 2));
      else
        e.setDir(static_cast<Direction>(rand() % 2));
      e.move(*m_map);
    }
    m_lastEvilTick = m_curTick;
  }
}

void SolarFox::movePlayer(size_t speed)
{
  if (m_curTick - m_lastTick > speed)
  {
    m_player.move(*m_map);

    m_lastTick = m_curTick;
  }
}

void SolarFox::movePlayerShoot(size_t speed)
{
  if (m_curTick - m_lastShootTick > speed)
  {
    checkPowerUps();
    if (m_hasShot)
    {
      m_shoot.move(*m_map);
      if (m_shoot.getRange() <= 0)
      {
        m_hasShot = false;
        m_map->at(0, m_shoot[0].x, m_shoot[0].y).setType(m_shoot.getCurTile());
      }
    }
    m_lastShootTick = m_curTick;
  }
}

void SolarFox::enemyShoot(size_t speed)
{
  if (m_curTick - m_lastEvilSalveTick > speed)
  {
    for (Enemy &e : m_enemies)
    {
      EvilShoot new_shoot;

      new_shoot = *static_cast<EvilShoot *>(e.shoot().get());
      new_shoot.setCurTile(m_map->at(0, new_shoot[0].x, new_shoot[0].y).getType());
      m_evilShoot.push_back(new_shoot);
      m_lastEvilSalveTick = m_curTick;
    }
  }
}

void SolarFox::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);
  m_powerups.display(*m_map);
  if (m_hasShot)
    m_shoot.display(*m_map);
  m_player.display(*m_map);

  for (Enemy const &e : m_enemies)
  {
    e.display(*m_map);
  }
  for (EvilShoot const &es : m_evilShoot)
  {
    es.display(*m_map);
  }
  for (std::vector<EvilShoot>::iterator it = m_evilShoot.begin(); it != m_evilShoot.end();)
  {
    if (checkShoot((*it)[0]) || !it->next().inMap(*m_map))
      it = m_evilShoot.erase(it);
    else
    {
      it++;
    }
  }
  enemyShoot(3000);
  moveEvilShoot(150);
  moveEvilDude(400);
  movePlayer(200);
  movePlayerShoot(50);
}

#if defined(__linux__)

void SolarFox::WhereAmI(std::ostream &) const
{
  // TODO: implement
}

#endif
}
}
}

extern "C" void Play(void)
{
  arcade::game::solarfox::SolarFox game;

  game.Play();
}