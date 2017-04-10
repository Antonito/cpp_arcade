#include <iostream>
#include <sstream>
#include <algorithm>
#include "Pong.hpp"
#include "Sprite.hpp"

namespace arcade
{
  namespace game
  {
    namespace pong
    {
      Pong::Pong() :
	m_lastTick(0),
        m_curTick(0),
	m_state(PongState::AUTHENTICATING), m_fact()
      {
        m_map = std::make_unique<Map>(80, 50);

        m_map->addLayer();
        m_map->addLayer();

        m_map->clearLayer(0, Color(30, 30, 30));
        m_map->clearLayer(1);

        size_t size = std::max(m_map->getHeight() / 10, static_cast<size_t>(10));
        size_t y = (m_map->getHeight() - size) / 2;

        for (size_t player = 0; player < 2; ++player)
        {
          for (size_t i = 0; i < size; ++i)
          {
            m_player[player].push(Position(player * (m_map->getWidth() - 3) + 1, y + i));
          }
        }
        m_id = 0;
        m_ball.setBallPos(Position(m_map->getWidth() / 2, m_map->getHeight() / 2));
      }

      Pong::Pong(Pong const &other) :
        m_lastTick(other.m_lastTick),
        m_curTick(other.m_curTick),
        m_id(other.m_id)
      {
        m_player[0] = other.m_player[0];
        m_player[1] = other.m_player[1];
      }

      Pong::~Pong()
      {
      }

      Pong &Pong::operator=(Pong const &other)
      {
        if (this != &other)
        {
          m_lastTick = other.m_lastTick;
          m_curTick = other.m_curTick;
          m_player[0] = other.m_player[0];
          m_player[1] = other.m_player[1];
          m_id = other.m_id;
        }
        return (*this);
      }

      bool Pong::hasNetwork() const
      {
	return (true);
      }

      void Pong::notifyEvent(std::vector<Event> &&events)
      {
        std::vector<Event> ev = events;

        for (Event const &e : ev)
        {
          if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
          {
            switch (e.kb_key)
            {
            case KB_ARROW_UP:
              if (m_player[m_id][0].y > 0)
              {
                m_player[m_id].setDir(Direction::UP);
                m_player[m_id].move();
              }
              break;
            case KB_ARROW_DOWN:
              if (m_player[m_id].last().y < m_map->getHeight() - 1)
              {
                m_player[m_id].setDir(Direction::DOWN);
                m_player[m_id].move();
              }
              break;
            default:
              break;
            }
          }
        }
      }

      std::vector<std::pair<std::string, SoundType>> Pong::getSoundsToLoad() const
      {
        std::vector<std::pair<std::string, SoundType>> s;
        // TODO: implement
        return (s);
      }

      std::vector<std::unique_ptr<ISprite>> Pong::getSpritesToLoad() const
      {
        std::vector<std::unique_ptr<ISprite>> s;

        return (s);
      }

      void Pong::process()
      {
	static bool	auth = false;
	bool	rec = false;

	// Treat input data
	switch (m_state)
	  {
	  case PongState::AUTHENTICATING:
	    for (NetworkPacket const &pck : m_received)
	      {
		Network::NetworkPacketData<0, uint8_t>	*_pck = reinterpret_cast<Network::NetworkPacketData<0, uint8_t> *>(pck.data);
		rec = true;
		if (ntohl(pck.header.magicNumber) == NetworkPacketHeader::packetMagicNumber && _pck &&
		    static_cast<NetworkAction>(ntohl(static_cast<uint32_t>(_pck->action))) ==
		    NetworkAction::HELLO_EVENT && _pck->auth == true)
		  {
#if defined(DEBUG)
		    std::cout << "Client Authenticated" << std::endl;
#endif
		    m_state = PongState::WAITING;
		  }
	      }
	    break;

	  case PongState::WAITING:
	    // Waiting for a second player
	    for (NetworkPacket const &pck : m_received)
	      {
		Network::NetworkPacketData<0, uint8_t>	*_pck = reinterpret_cast<Network::NetworkPacketData<0, uint8_t> *>(pck.data);
		std::cout << "Got a packet." << std::endl;
		std::cout << "Magic correct ? " << (ntohl(pck.header.magicNumber) == NetworkPacketHeader::packetMagicNumber) <<  std::endl;
		std::cout << "Data? " << (_pck != nullptr) << std::endl;
		std::cout << "Event: " << ntohl(static_cast<uint32_t>(_pck->action)) << "[Expected: " << NetworkAction::GAME_EVENT << "]" << std::endl;
		std::cout << "Auth? " << (_pck->auth == true) << std::endl;
		if (ntohl(pck.header.magicNumber) == NetworkPacketHeader::packetMagicNumber && _pck &&
		    static_cast<NetworkAction>(ntohl(static_cast<uint32_t>(_pck->action))) ==
		    NetworkAction::GAME_EVENT && _pck->auth == true)
		  {
#if defined(DEBUG)
		    std::cout << "Other player connected" << std::endl;
#endif
		    m_state = PongState::PLAYING;
		  }
	      }
	    break;

	  case PongState::PLAYING:
	    // Get other player's events
	    std::cout << "Playing." << std::endl;
	    break;

	  default:
	    break;
	  }

	// Output data
	switch (m_state)
	  {
	  case PongState::AUTHENTICATING:
	    // We should authenticate
	    if (!auth || rec)
	    {
#if defined(DEBUG)
	      std::cout << "Authenticating Pong" << std::endl;
#endif
	      std::unique_ptr<NetworkPacket>	createdPck = m_fact.create<1, bool>(NetworkGames::PONG, [&](Network::NetworkPacketData<1, bool> &p) {
		  p.action = static_cast<NetworkAction>(htonl(static_cast<uint32_t>(NetworkAction::HELLO_EVENT)));
		  p.auth = false;
		});
	      NetworkPacket	*raw = createdPck.get();
	      NetworkPacket	pck = *createdPck;
	      createdPck.release();
	      m_toSend.push_back(pck);
	      delete raw;
	      auth = true;
	    }
	    break;

	  case PongState::WAITING:
	    // Waiting for other players
	    std::cout << "Waiting for other players" << std::endl;
	    {
	      std::unique_ptr<NetworkPacket>	createdPck = m_fact.create<1, bool>(NetworkGames::PONG, [&](Network::NetworkPacketData<1, bool> &p) {
		  p.action = static_cast<NetworkAction>(htonl(static_cast<uint32_t>(NetworkAction::GAME_EVENT)));
		  p.auth = true;
		});
	      NetworkPacket	*raw = createdPck.get();
	      NetworkPacket	pck = *createdPck;
	      createdPck.release();
	      m_toSend.push_back(pck);
	      delete raw;
	    }
	    break;

	  case PongState::PLAYING:
	    // The game is running
	    m_map->clearLayer(1);

	    m_curTick = this->getCurrentTick();
	    m_ball.updatePosition(m_player[m_ball.getBallDir()], m_map->getHeight(),
				  (m_curTick - m_lastTick) / 1000.0);
	    if (m_ball[0].x < 0)
	      {
		m_ball.reset(Position(m_map->getWidth() / 2, m_map->getHeight() / 2));
	      }
	    else if (m_ball[0].x > m_map->getWidth() - 1)
	      {
		m_ball.reset(Position(m_map->getWidth() / 2, m_map->getHeight() / 2));
	      }
	    m_player[0].display(*m_map);
	    m_player[1].display(*m_map);
	    m_ball.display(*m_map);
	    m_lastTick = m_curTick;
	    break;

	  default:
	    break;
	  }
      }

#if defined(__linux__)
      void Pong::WhereAmI(std::ostream &) const
      {
      }
#endif
    }
  }
}

#if defined (__linux__)
extern "C" void Play(void)
{
  arcade::game::pong::Pong game;

  game.Play();
}
#endif
