#include "AGame.hpp"

namespace arcade
{
	AGame::AGame()
	{
	}

	GameState AGame::getGameState() const
	{
		return (m_state);
	}

	void AGame::notifyEvent(std::vector<Event> const & events)
	{
		m_events = events; // TODO: std::move plz
	}

	void AGame::notifyNetwork(std::vector<NetworkPacket> const &events)
	{
		m_received = events; // TODO: std::move plz
	}
	
	std::vector<NetworkPacket> AGame::getNetworkToSend() const
	{
		return (std::move(m_toSend));
	}
	
	std::vector<int>&& AGame::getSoundToPlay()
	{
		return (std::move(m_soundsToPlay));
	}
	
	IMap const & AGame::getCurrentMap() const
	{
		return (*m_map);
	}

//	IGUI const & AGame::getGUI() const
//	{
//		return (m_gui);
//	}
}