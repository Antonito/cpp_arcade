#include <iostream>
#include <sstream>
#include <algorithm>
#include "Pong.hpp"
#include "Sprite.hpp"
#include "PongPacket.hpp"

namespace arcade
{
  namespace game
  {
    namespace pong
    {
      Pong::Pong() :
	m_lastTick(0),
        m_curTick(0),
	m_lastUpTick(0), m_lastDownTick(0), m_lastSendTick(0), m_lastSendBallTick(0),
	m_state(PongState::AUTHENTICATING), m_fact(), m_updatePos(0)
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
          m_smoothTick[player] = 0;
          for (size_t i = 0; i < size; ++i)
          {
            m_player[player].push(Position(player * (m_map->getWidth() - 3) + 1, y + i));
          }
        }
        m_id = 0;
        m_ball.setBallPos(Position(m_map->getWidth() / 2, m_map->getHeight() / 2));
      }

      Pong::Pong(Pong const &other) : AGame(),
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
              if (m_curTick - m_lastUpTick > 60
		  && m_player[m_id][0].y > 0)
              {
                m_player[m_id].setDir(Direction::UP);
                m_player[m_id].move();
		++m_updatePos;
                m_smoothTick[m_id] = this->getCurrentTick();
                m_lastUpTick = m_curTick;
              }
              break;
            case KB_ARROW_DOWN:
              if (m_curTick - m_lastDownTick > 60 &&
		  static_cast<unsigned>(m_player[m_id].last().y) <
		  m_map->getHeight() - 1)
              {
                m_player[m_id].setDir(Direction::DOWN);
                m_player[m_id].move();
		++m_updatePos;
                m_smoothTick[m_id] = this->getCurrentTick();
                m_lastDownTick = m_curTick;
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
	static bool	shouldSend = true;
	bool	rec = false;
	uint8_t	otherId = (m_id == 0);

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
		    m_state = PongState::SETTING;
		  }
	      }
	    break;

	  case PongState::SETTING:
	    for (NetworkPacket const &pck : m_received)
	      {
		Network::NetworkPacketData<0, PongPacket> *_pck =
		  reinterpret_cast<Network::NetworkPacketData<0, PongPacket> *>(pck.data);

		if (ntohl(pck.header.magicNumber) == NetworkPacketHeader::packetMagicNumber && _pck &&
		    static_cast<NetworkAction>(ntohl(static_cast<uint32_t>(_pck->action))) ==
		    NetworkAction::ENTITY_EVENT)
		  {
		    m_id = _pck->entity.data.id;
		    m_state = PongState::WAITING;
		  }
	      }
	    break;

	  case PongState::WAITING:
	    // Waiting for a second player
	    for (NetworkPacket const &pck : m_received)
	      {
		Network::NetworkPacketData<0, uint8_t>	*_pck = reinterpret_cast<Network::NetworkPacketData<0, uint8_t> *>(pck.data);
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
	    for (NetworkPacket const &pck : m_received)
	      {
		Network::NetworkPacketData<0, PongPacket>	*_pck = reinterpret_cast<Network::NetworkPacketData<0, PongPacket> *>(pck.data);
		if (ntohl(pck.header.magicNumber) == NetworkPacketHeader::packetMagicNumber && _pck &&
		    static_cast<NetworkAction>(ntohl(static_cast<uint32_t>(_pck->action))) ==
		    NetworkAction::ENTITY_EVENT)
		  {
		    for (uint32_t i = 0; i < ntohl(_pck->entity.data.update); ++i)
		      {
			if (ntohl(_pck->entity.data.pos.y) > m_player[otherId][0].y &&
			    static_cast<unsigned>(m_player[otherId].last().y)
			    < m_map->getHeight() - 1)
			  {
			    m_player[otherId].setDir(Direction::DOWN);
			    m_player[otherId].move();
                            m_smoothTick[otherId] = this->getCurrentTick();
			  }
			else if (ntohl(_pck->entity.data.pos.y) < m_player[otherId][0].y &&
				 m_player[otherId][0].y > 0)
			  {
			    m_player[otherId].setDir(Direction::UP);
			    m_player[otherId].move();
                            m_smoothTick[otherId] = this->getCurrentTick();
                        }
		      }
		    if (m_id != 0 && _pck->entity.data.updateBall == true)
		      {
                        m_ball.reset(Position());
			m_ball.setX(static_cast<double>(ntohl(_pck->entity.data.ball.x)));
			m_ball.setY(static_cast<double>(ntohl(_pck->entity.data.ball.y)));
		      }
		  }
	      }
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
	      rec = false;
	    }
	    break;

	  case PongState::SETTING:
	    if (!rec)
	      {
		std::unique_ptr<NetworkPacket>	createdPck = m_fact.create<1, bool>(NetworkGames::PONG, [&](Network::NetworkPacketData<1, bool> &p) {
		    p.action = static_cast<NetworkAction>(htonl(static_cast<uint32_t>(NetworkAction::ENTITY_EVENT)));
		    p.auth = false;
		  });
		NetworkPacket	*raw = createdPck.get();
		NetworkPacket	pck = *createdPck;
		createdPck.release();
		m_toSend.push_back(pck);
		delete raw;
		rec = true;
	      }
	    break;

	  case PongState::WAITING:
	    // Waiting for other players
#if defined(DEBUG)
	    std::cout << "Waiting for other players" << std::endl;
#endif
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
	    {
	      bool updateBall = false;
	      static int ballCount = 0;
	      // The game is running
	      m_map->clearLayer(1);

	      m_curTick = this->getCurrentTick();
	      m_ball.updatePosition(m_player[m_ball.getBallDir()], m_map->getHeight(),
				    (m_curTick - m_lastTick) / 1000.0);
	      if (m_ball[0].x < 0)
		{
		  m_ball.reset(Position(m_map->getWidth() / 2, m_map->getHeight() / 2));
		  ballCount = 0;
		  updateBall = true;
		}
	      else if (m_ball[0].x > static_cast<signed>(m_map->getWidth() - 1))
		{
		  m_ball.reset(Position(m_map->getWidth() / 2, m_map->getHeight() / 2));
		  ballCount = 0;
		  updateBall = true;
		}
	      if (ballCount < 40)
		{
		  updateBall = true;
		  ++ballCount;
		}
	      m_ball.display(*m_map);

              for (size_t i = 0; i < 2; ++i)
              {
                m_player[i].display(*m_map, (m_curTick - m_smoothTick[i]) / 60.0);
              }

	      m_lastTick = m_curTick;
	      if (shouldSend &&
		  (updateBall || m_curTick - m_lastSendTick > 60))
		{
		  std::unique_ptr<NetworkPacket>	createdPck = m_fact.create<1, PongPacket>(NetworkGames::PONG, [&](Network::NetworkPacketData<1, PongPacket> &p) {
		      p.action = static_cast<NetworkAction>(htonl(static_cast<uint32_t>(NetworkAction::ENTITY_EVENT)));
		      p.entity.data.pos.x = htonl(m_player[m_id][0].x);
		      p.entity.data.pos.y = htonl(m_player[m_id][0].y);
		      if (m_id == 0)
			{
			  p.entity.data.ball.x = htonl(static_cast<float>(m_ball.getX()));
			  p.entity.data.ball.y = htonl(static_cast<float>(m_ball.getY()));
			}
		      else
			{
			  p.entity.data.ball.x = 0;
			  p.entity.data.ball.y = 0;
			}
		      p.entity.data.updateBall = updateBall;
		      p.entity.data.update = htonl(m_updatePos);
		      p.entity.data.id = m_id;
		    });
		  NetworkPacket	*raw = createdPck.get();
		  NetworkPacket	pck = *createdPck;
		  createdPck.release();
		  m_toSend.push_back(pck);
		  m_updatePos = 0;
		  m_lastSendTick = m_curTick;
		  delete raw;
		}
	    }
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
