#include <iostream>
#include <sstream>
#include "BlockadeLocal.hpp"
#include "Sprite.hpp"

namespace arcade
{
  namespace game
  {
    namespace blockade_local
    {
      BlockadeLocal::BlockadeLocal() : AGame("blockade_local")
      {
	// clang-format off
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
          "000000F00000000000S000000",
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
	// clang-format on

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
		  case 'F':
		    type = TileType::EMPTY;
		    m_player1.push(Position(x, y), 5);
		    m_player1.setDir(Direction::UP);
		    break;
		  case 'S':
		    type = TileType::EMPTY;
		    m_player2.push(Position(x, y), 5);
		    m_player2.setDir(Direction::DOWN);
		    break;
		  }
		m_map->at(0, x, y).setType(type);
	      }
	  }

	m_map->clearLayer(0, Color(50, 50, 50));
	m_map->clearLayer(1);

	m_lastTick = 0;
	m_curTick = 0;
	m_tmpDir1 = Direction::UP;
	m_tmpDir2 = Direction::DOWN;
      }

      BlockadeLocal::BlockadeLocal(BlockadeLocal const &other)
          : AGame("blockade_local")
      {
	*m_map = *other.m_map;
	m_player1 = other.m_player1;
	m_player2 = other.m_player2;
	m_lastTick = other.m_lastTick;
	m_curTick = other.m_curTick;
	m_tmpDir1 = other.m_tmpDir1;
	m_tmpDir2 = other.m_tmpDir2;
      }

      BlockadeLocal::~BlockadeLocal()
      {
      }

      BlockadeLocal &BlockadeLocal::operator=(BlockadeLocal const &other)
      {
	if (this != &other)
	  {
	    *m_map = *other.m_map;
	    m_player1 = other.m_player1;
	    m_player2 = other.m_player2;
	    m_lastTick = other.m_lastTick;
	    m_curTick = other.m_curTick;
	    m_tmpDir1 = other.m_tmpDir1;
	    m_tmpDir2 = other.m_tmpDir2;
	  }
	return (*this);
      }

      void BlockadeLocal::notifyEvent(std::vector<Event> &&events)
      {
	std::vector<Event> ev = events;

	for (Event const &e : ev)
	  {
	    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
	      {
		switch (e.kb_key)
		  {
		  case KB_ARROW_UP:
		    if (m_player1.getDir() != Direction::DOWN)
		      m_tmpDir1 = Direction::UP;
		    break;
		  case KB_ARROW_DOWN:
		    if (m_player1.getDir() != Direction::UP)
		      m_tmpDir1 = Direction::DOWN;
		    break;
		  case KB_ARROW_LEFT:
		    if (m_player1.getDir() != Direction::RIGHT)
		      m_tmpDir1 = Direction::LEFT;
		    break;
		  case KB_ARROW_RIGHT:
		    if (m_player1.getDir() != Direction::LEFT)
		      m_tmpDir1 = Direction::RIGHT;
		    break;
		  case KB_W:
		    if (m_player2.getDir() != Direction::DOWN)
		      m_tmpDir2 = Direction::UP;
		    break;
		  case KB_S:
		    if (m_player2.getDir() != Direction::UP)
		      m_tmpDir2 = Direction::DOWN;
		    break;
		  case KB_A:
		    if (m_player2.getDir() != Direction::RIGHT)
		      m_tmpDir2 = Direction::LEFT;
		    break;
		  case KB_D:
		    if (m_player2.getDir() != Direction::LEFT)
		      m_tmpDir2 = Direction::RIGHT;
		    break;
		  case KB_ENTER:
		    if (m_finished)
		      m_state = MENU;
		    break;
		  case KB_ESCAPE:
		    m_state = MENU;
		    break;
		  default:
		    break;
		  }
	      }
	  }
      }

      std::vector<std::pair<std::string, SoundType>>
          BlockadeLocal::getSoundsToLoad() const
      {
	std::vector<std::pair<std::string, SoundType>> s;

	s.emplace_back("assets/sounds/Collect_Point_00.wav", SoundType::MUSIC);

	m_soundsToPlay.emplace_back(0, VOLUME, 25.0);

	return (s);
      }

      std::vector<std::unique_ptr<ISprite>>
          BlockadeLocal::getSpritesToLoad() const
      {
	std::vector<std::unique_ptr<ISprite>> s;

	s.push_back(std::make_unique<Sprite>("assets/snake/", "apple", 1,
	                                     ".png", "$"));
	s.push_back(std::make_unique<Sprite>("assets/snake/", "peach", 1,
	                                     ".png", "$"));
	s.push_back(std::make_unique<Sprite>("assets/snake/", "strawberry", 1,
	                                     ".png", "$"));
	s.push_back(std::make_unique<Sprite>("assets/snake/", "cherry", 1,
	                                     ".png", "$"));
	s.push_back(
	    std::make_unique<Sprite>("assets/snake/", "head", 4, ".png", "$"));
	s.push_back(
	    std::make_unique<Sprite>("assets/snake/", "body", 1, ".png", "$"));

	return (s);
      }

      void BlockadeLocal::process()
      {
	if (m_finished)
	  return;
	m_curTick = this->getCurrentTick();
	m_map->clearLayer(1);
	m_player1.display(*m_map, (m_curTick - m_lastTick) / 100.0);
	m_player2.display(*m_map, (m_curTick - m_lastTick) / 100.0);

	if (m_curTick - m_lastTick > 100)
	  {
	    m_player1.setDir(m_tmpDir1);
	    m_player2.setDir(m_tmpDir2);

	    if (m_player1.next().inMap(*m_map) &&
	        !m_player2.isTouch(m_player1.next()) &&
	        (!m_player1.isTouch(m_player1.next()) ||
	         m_player1.next() == m_player1.last()))
	      {
		m_player1.move(*m_map);
	      }
	    else
	      m_state = MENU;

	    if (m_player2.next().inMap(*m_map) &&
	        !m_player1.isTouch(m_player2.next()) &&
	        (!m_player2.isTouch(m_player2.next()) ||
	         m_player2.next() == m_player2.last()))
	      {
		m_player2.move(*m_map);
	      }
	    else
	      m_finished = true;
	    m_lastTick = m_curTick;
	  }
      }

#if defined(__linux__)
      void BlockadeLocal::WhereAmI(std::ostream &os) const
      {
	uint16_t         size = static_cast<uint16_t>(m_player1.size() - 1);
	arcade::WhereAmI header = {};
	std::unique_ptr<::arcade::Position[]> pos(
	    new ::arcade::Position[size]);
	header.type = CommandType::WHERE_AM_I;
	header.lenght = size;

	for (size_t i = 0; i < size; ++i)
	  {
	    pos[i].x = m_player1[i].x;
	    pos[i].y = m_player1[i].y;
	  }

	os.write(reinterpret_cast<char *>(&header), sizeof(arcade::WhereAmI));
	os.write(reinterpret_cast<char *>(pos.get()),
	         size * sizeof(::arcade::Position));
      }
#endif
    }
  }
}

#if defined(__linux__)
extern "C" void Play(void)
{
  arcade::game::blockade_local::BlockadeLocal game;

  game.Play();
}
#endif
