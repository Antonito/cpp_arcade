#include <iostream>
#include <sstream>
#include "Snake.hpp"
#include "Sprite.hpp"

namespace arcade
{
namespace game
{
namespace snake
{
Snake::Snake()
{
  std::vector<std::string> m =
      {
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
          "0000000000000000000000000",
          "0000000000000000000000000"};

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
      }
      m_map->at(0, x, y).setType(type);
    }
  }

  m_map->clearLayer(0, Color(50, 50, 50));
  m_map->clearLayer(1);
  m_player.push(Position(m_map->getWidth() / 2, m_map->getHeight() / 2), 4);
  m_player.setDir(Direction::LEFT);
  m_fruit.push(placeFood(*m_map));
  m_lastTick = 0;
  m_curTick = 0;
  m_tmpDir = Direction::LEFT;
}

Snake::Snake(Snake const &other) : AGame()
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_fruit = other.m_fruit;
  m_lastTick = other.m_lastTick;
  m_curTick = other.m_curTick;
  m_tmpDir = other.m_tmpDir;
}

Snake::~Snake()
{
}

Snake &Snake::operator=(Snake const &other)
{
  if (this != &other)
  {
    *m_map = *other.m_map;
    m_player = other.m_player;
    m_fruit = other.m_fruit;
    m_lastTick = other.m_lastTick;
    m_curTick = other.m_curTick;
    m_tmpDir = other.m_tmpDir;
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
        if (m_player.getDir() != Direction::DOWN)
          m_tmpDir = Direction::UP;
        break;
      case KB_ARROW_DOWN:
        if (m_player.getDir() != Direction::UP)
          m_tmpDir = Direction::DOWN;
        break;
      case KB_ARROW_LEFT:
        if (m_player.getDir() != Direction::RIGHT)
          m_tmpDir = Direction::LEFT;
        break;
      case KB_ARROW_RIGHT:
        if (m_player.getDir() != Direction::LEFT)
          m_tmpDir = Direction::RIGHT;
        break;
      case KB_ESCAPE:
        m_state = MENU;
      default:
        break;
      }
    }
  }
}

std::vector<std::pair<std::string, SoundType>> Snake::getSoundsToLoad() const
{
  std::vector<std::pair<std::string, SoundType>> s;

  s.emplace_back("assets/sounds/Collect_Point_00.wav", SoundType::MUSIC);

  m_soundsToPlay.emplace_back(0, VOLUME, 25.0);

  return (s);
}

std::vector<std::unique_ptr<ISprite>> Snake::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  s.push_back(std::make_unique<Sprite>("assets/snake/", "apple", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("assets/snake/", "peach", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("assets/snake/", "strawberry", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("assets/snake/", "cherry", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("assets/snake/", "head", 4, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("assets/snake/", "body", 1, ".png", "$"));

  return (s);
}

void Snake::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);
  m_player.display(*m_map, (m_curTick - m_lastTick) / 100.0);
  m_fruit.display(*m_map);

  if (m_curTick - m_lastTick > 100)
  {
    m_player.setDir(m_tmpDir);
    if (m_fruit[0] == m_player.next())
    {
      m_soundsToPlay.emplace_back(0, PLAY);
      m_fruit[0] = placeFood(*m_map);
      m_fruit.updateSprite();
      m_player.push(m_player.last());
      m_player[m_player.size() - 2] = m_player[m_player.size() - 3];
    }
    if (m_player.next().inMap(*m_map) && (!m_player.isTouch(m_player.next()) || m_player.next() == m_player.last()))
    {
      m_player.move(*m_map);
    }
    else
      m_state = MENU;
    m_lastTick = m_curTick;
  }
}

#if defined(__linux__)
void Snake::WhereAmI(std::ostream &os) const
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

Position Snake::placeFood(Map const &map) const
{
  size_t width = map.getWidth();
  size_t height = map.getHeight();

  // Try to place random
  for (size_t i = 0; i < 10000; ++i)
  {
    Position p(rand() % width, rand() % height);

    if (map.at(0, p.x, p.y).getType() != TileType::BLOCK &&
        m_player.isTouch(p) == false)
    {
      return (p);
    }
  }

  // Search the first spot
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      Position p(x, y);

      if (map.at(0, x, y).getType() != TileType::BLOCK &&
          m_player.isTouch(p) == false)
      {
        return (p);
      }
    }
  }
  return (Position(0, 0));
}
}
}
}

#if defined(__linux__)
extern "C" void Play(void)
{
  arcade::game::snake::Snake game;

  game.Play();
}
#endif
