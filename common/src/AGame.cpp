#include "AGame.hpp"

namespace arcade
{
	AGame::AGame() : m_state(INGAME)
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
	
	std::vector<int>&& AGame::getSoundsToPlay()
	{
		return (std::move(m_soundsToPlay));
	}
	
	IMap const & AGame::getCurrentMap() const
	{
		return (*m_map);
	}

	IGUI const & AGame::getGUI() const
	{
		return (*m_gui);
	}
}