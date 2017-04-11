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

  std::vector<std::string> m =
      {".........................",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       ".00000000000000000000000.",
       "............S............"};

  m_map = std::make_unique<Map>(m[0].size(), m.size());
  m_map->addLayer();
  m_map->addLayer();

  m_map->clearLayer(0, Color(50, 50, 50));
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
      case '.':
        type = TileType::OTHER;
        m_map->at(0, x, y).setColor(Color::White);
        break;
      case 'S':
        type = TileType::OTHER;
        m_player.push(Position(x, y));
        m_player.setDir(Direction::UP);
        break;
      }
      m_map->at(0, x, y).setType(type);
    }
  }
  m_map->clearLayer(1);
  m_lastTick = 0;
  m_curTick = 0;
  m_dir = Direction::UP;
}

Qix::Qix(Qix const &other) : AGame()
{
  *m_map = *other.m_map;
  m_player = other.m_player;
  m_lastTick = other.m_lastTick;
  m_curTick = other.m_curTick;
  m_dir = other.m_dir;
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
        if (m_player.getDir() != Direction::DOWN)
          m_dir = Direction::UP;
        break;
      case KB_ARROW_DOWN:
        if (m_player.getDir() != Direction::UP)
          m_dir = Direction::DOWN;
        break;
      case KB_ARROW_LEFT:
        if (m_player.getDir() != Direction::RIGHT)
          m_dir = Direction::LEFT;
        break;
      case KB_ARROW_RIGHT:
        if (m_player.getDir() != Direction::LEFT)
          m_dir = Direction::RIGHT;
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

void Qix::process()
{
  m_curTick = this->getCurrentTick();
  m_map->clearLayer(1);

  //Display player, obstacles and enemies
  m_player.display(*m_map);

  //Movement of the shoot ,enemy and check of collision
  if (m_curTick - m_lastTick > 100)
  {
    m_player.setDir(m_dir);
    m_player.move(*m_map);
    m_lastTick = m_curTick;
  }
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
  arcade::game::qix::Qix game;

  game.Play();
}
#endif
