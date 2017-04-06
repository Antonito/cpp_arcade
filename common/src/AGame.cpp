#include <iostream>
#include <fstream>
#include "AGame.hpp"

namespace arcade
{
  AGame::AGame() : m_state(INGAME),
    m_startTick(m_clock_t::now()),
    m_mouliMode(false),
    m_fakeTick(0)
  {
  }

  GameState AGame::getGameState() const
  {
    return (m_state);
  }

  void AGame::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
    m_received = events;
  }

  std::vector<NetworkPacket> &&AGame::getNetworkToSend()
  {
    return (std::move(m_toSend));
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
    return (*m_gui);
  }

#if defined(__linux__)
  GetMap *AGame::getMap() const
  {
    // Allocate the struct
    size_t size = sizeof(GetMap) + (m_map->getWidth() * m_map->getHeight()) * sizeof(TileType);
    GetMap *map = reinterpret_cast<GetMap *>(new uint8_t[size]);

    // Prepare the struct
    map->type = CommandType::GET_MAP;
    map->width = m_map->getWidth();
    map->height = m_map->getHeight();
    for (size_t i = 0; i < m_map->getWidth() * m_map->getHeight(); ++i)
    {
      map->tile[i] = TileType::EMPTY;
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
            map->tile[y * map->width + x] = type;
          }
        }
      }
    }
    return (map);
  }

  void AGame::Play(void)
  {
    CommandType type;
    std::vector<Event> events;
    Event ev;
    bool play = true;

    ev.type = ET_KEYBOARD;
    ev.action = AT_PRESSED;
    m_mouliMode = true;
    m_state = INGAME;

    while (m_state == INGAME)
    {
      if (play)
      {
        this->notifyEvent(std::move(events));
        this->process();
        play = false;
      }

      if (!std::cin.read(reinterpret_cast<char *>(&type), sizeof(CommandType)))
      {
        return;
      }

      switch (type)
      {
      case CommandType::WHERE_AM_I:
      {
        WhereAmI *w = this->getWhereAmI();

        std::cout.write(reinterpret_cast<char *>(w), sizeof(WhereAmI) + w->lenght * sizeof(Position));
        delete[] w;
        break;
      }
      case CommandType::GET_MAP:
      {
        GetMap *m = this->getMap();

        std::cout.write(reinterpret_cast<char *>(m), sizeof(GetMap) + m->width * m->height * sizeof(TileType));
        delete[] m;
        break;
      }
      case CommandType::GO_UP:
        ev.kb_key = KB_ARROW_UP;
        events.push_back(ev);
        play = true;
        break;
      case CommandType::GO_DOWN:
        ev.kb_key = KB_ARROW_DOWN;
        events.push_back(ev);
        play = true;
        break;
      case CommandType::GO_LEFT:
        ev.kb_key = KB_ARROW_LEFT;
        events.push_back(ev);
        play = true;
        break;
      case CommandType::GO_RIGHT:
        ev.kb_key = KB_ARROW_RIGHT;
        events.push_back(ev);
        play = true;
        break;
      case CommandType::GO_FORWARD:
        play = true;
        break;
      case CommandType::SHOOT:
        ev.kb_key = KB_SPACE;
        events.push_back(ev);
        play = true;
        break;
      case CommandType::PLAY:
        break;
      default:
        play = true;
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
    return (std::chrono::duration_cast<std::chrono::milliseconds>(m_clock_t::now() - m_startTick).count());
  }
}