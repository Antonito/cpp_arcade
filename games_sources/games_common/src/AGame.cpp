#include <iostream>
#include <fstream>
#include <sstream>
#include "AGame.hpp"

namespace arcade
{
  namespace game
  {
    AGame::AGame(std::string const &name)
        : m_state(INGAME), m_gui(std::make_unique<GUI>()), m_score(0),
          m_finished(false), m_startTick(m_clock_t::now()), m_mouliMode(false),
          m_fakeTick(0), m_overUpdated(false), m_name(name)
    {
      m_over = std::make_unique<GUI>();
      m_over->push(Component(0, 0, 1, 1, Color(0, 0, 0, 150)));
      m_over->push(
          Component(0.45, 0.2, 0.4, 0.2, Color::Transparent, "Game Over !"));
      m_over->push(Component(0.45, 0.5, 0.4, 0.2));
    }

    GameState AGame::getGameState() const
    {
      return (m_state);
    }

    void AGame::notifyNetwork(std::vector<NetworkPacket> &&events)
    {
      m_received = events;
    }

    std::vector<NetworkPacket> AGame::getNetworkToSend()
    {
      return (std::move(m_toSend));
    }

    bool AGame::hasNetwork() const
    {
      return (false);
    }

    std::vector<Sound> AGame::getSoundsToPlay()
    {
      return (std::move(m_soundsToPlay));
    }

    IMap const &AGame::getCurrentMap() const
    {
      return (*m_map);
    }

    IGUI &AGame::getGUI()
    {
      if (m_finished)
	{
	  if (!m_overUpdated)
	    {
	      std::stringstream ss;
	      std::fstream      os("scores/" + m_name + ".txt",
	                      std::ios::out | std::ios::trunc);

	      size_t last;

	      ss << m_score;
	      m_over->at(2).setText("Score : " + ss.str());
	      if (os.is_open())
		{
		  os >> last;
		  if (last < m_score)
		    {
		      os << m_score << std::endl;
		    }
		}
	    }
	  return (*m_over);
	}
      return (*m_gui);
    }

#if defined(__linux__)
    void AGame::getMap(std::ostream &os) const
    {
      // Allocate the struct
      GetMap header = {CommandType::GET_MAP,
                       static_cast<uint16_t>(m_map->getWidth()),
                       static_cast<uint16_t>(m_map->getHeight())};
      std::unique_ptr<TileType[]> map(
          new TileType[header.width * header.height]);

      // Prepare the struct
      for (size_t i = 0;
           i < static_cast<unsigned>(header.width * header.height); ++i)
	{
	  map[i] = TileType::EMPTY;
	}

      // Fill the data
      for (size_t l = 0; l < m_map->getLayerNb(); ++l)
	{
	  for (size_t y = 0; y < m_map->getHeight(); ++y)
	    {
	      for (size_t x = 0; x < m_map->getWidth(); ++x)
		{
		  TileType type = m_map->at(l, x, y).getType();

		  if (type != TileType::EMPTY)
		    {
		      map[y * header.width + x] = type;
		    }
		}
	    }
	}

      os.write(reinterpret_cast<char *>(&header), sizeof(GetMap));
      os.write(reinterpret_cast<char *>(map.get()),
               header.width * header.height * sizeof(TileType));
    }

    void AGame::Play(void)
    {
      CommandType        type;
      std::vector<Event> events;
      Event              ev;
      bool               play = true;

      ev.type = ET_KEYBOARD;
      ev.action = AT_PRESSED;
      m_mouliMode = true;
      m_state = INGAME;
      this->process();
      this->process();
      this->process();

      while (m_state == INGAME)
	{
	  if (play)
	    {
	      this->notifyEvent(std::move(events));
	      this->process();
	      play = false;
	    }

	  if (!std::cin.read(reinterpret_cast<char *>(&type),
	                     sizeof(CommandType)))
	    {
	      return;
	    }

	  switch (type)
	    {
	    case CommandType::WHERE_AM_I:
	      this->WhereAmI(std::cout);
	      break;
	    case CommandType::GET_MAP:
	      this->getMap(std::cout);
	      break;
	    case CommandType::GO_UP:
	      ev.kb_key = KB_ARROW_UP;
	      events.push_back(ev);
	      break;
	    case CommandType::GO_DOWN:
	      ev.kb_key = KB_ARROW_DOWN;
	      events.push_back(ev);
	      break;
	    case CommandType::GO_LEFT:
	      ev.kb_key = KB_ARROW_LEFT;
	      events.push_back(ev);
	      break;
	    case CommandType::GO_RIGHT:
	      ev.kb_key = KB_ARROW_RIGHT;
	      events.push_back(ev);
	      break;
	    case CommandType::GO_FORWARD:
	      break;
	    case CommandType::SHOOT:
	      ev.kb_key = KB_SPACE;
	      events.push_back(ev);
	      break;
	    case CommandType::PLAY:
	      play = true;
	      break;
	    default:
	      break;
	    }
	}
    }
#endif

    size_t AGame::getCurrentTick() const
    {
      if (m_mouliMode)
	{
	  m_fakeTick += 1000;
	  return (m_fakeTick);
	}
      return (std::chrono::duration_cast<std::chrono::milliseconds>(
                  m_clock_t::now() - m_startTick)
                  .count());
    }
  }
}
