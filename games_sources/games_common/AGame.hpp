#ifndef AGAME_HPP_
#define AGAME_HPP_

#include <vector>
#include <string>
#include <cstdlib>
#include "IGame.hpp"
#include "Map.hpp"
//#include "GUI.hpp"

namespace arcade
{
	class AGame : public IGame
	{
	public:
		AGame();
		AGame(AGame const &other) = delete;
		virtual ~AGame() {};

		AGame &operator=(AGame const &other) = delete;

		// Game state
		virtual GameState getGameState() const;

		// Events
		virtual void notifyEvent(std::vector<Event> const &events);

		// Network
		virtual void notifyNetwork(std::vector<NetworkPacket> const &events);
		virtual std::vector<NetworkPacket> getNetworkToSend() const;

		// Sound
		virtual std::vector<std::string> getSoundsToLoad() const = 0;
		virtual std::vector<int>         &&getSoundToPlay();

		// Map
		virtual IMap const &getCurrentMap() const;

		// Menu
		virtual IMenu const &getMenu() const = 0;

		// GUI
		//virtual IGUI const &getGUI() const;

	private:
		GameState m_state;

		std::vector<Event> m_events;

		std::vector<NetworkPacket> m_received;
		std::vector<NetworkPacket> m_toSend;

		std::vector<int> m_soundsToPlay;

		std::unique_ptr<Map> m_map;
		//GUI m_gui;
	};
}

#endif // !AGAME_HPP_