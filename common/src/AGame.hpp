#ifndef AGAME_HPP_
#define AGAME_HPP_

#include <vector>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <functional>
#include <chrono>
#include "IGame.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "EventHash.hpp"
#include "Protocol.hpp"

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
		virtual void notifyEvent(std::vector<Event> &&events) = 0;

		// Network
		virtual void notifyNetwork(std::vector<NetworkPacket> &&events);
		virtual std::vector<NetworkPacket> &&getNetworkToSend();

		// Sound
		virtual std::vector<std::pair<std::string, SoundType>> getSoundsToLoad() const = 0;
		virtual std::vector<Sound>         getSoundsToPlay();

		// Map
		virtual IMap const &getCurrentMap() const;

		// GUI
		virtual IGUI &getGUI();

		// Play
		void Play();

	protected:
#if defined(__linux__)
		virtual WhereAmI *getWhereAmI() const = 0;
		GetMap *getMap() const;
#endif

		GameState m_state;

		// Network buffers
		std::vector<NetworkPacket> m_received;
		std::vector<NetworkPacket> m_toSend;

		// Sounds to play buffer
		std::vector<Sound> m_soundsToPlay;

		// Game map
		std::unique_ptr<Map> m_map;
		std::unique_ptr<GUI> m_gui;

		size_t getCurrentTick() const;

	private:
		typedef std::chrono::high_resolution_clock m_clock_t;

		std::chrono::time_point<m_clock_t> m_startTick;
	};
}

#endif // !AGAME_HPP_
