#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <map>
#include <string>
#include <functional>
#include <cstring>
#include "IGame.hpp"
#include "IGfxLib.hpp"
#include "GenLibrary.hpp"
#include "AGame.hpp"
#include "TCPSocket.hpp"

namespace arcade
{
	class Core : public game::AGame
	{
	public:
		Core();
		Core(Core const &other) = delete;
		~Core();

		Core &operator=(Core const &other) = delete;

		void launch(std::string const &lib);

	private:
	  static size_t constexpr pckBuffSize = 4096;
		GameState gameLoop();
		GameState menuLoop();

		void initLists(std::string const &lib);

		static bool isNameValid(std::string const &name,
			std::string const &prefix, std::string const &sufix);

		void loadGame();
		void mainEvent(Event const &e);

		std::vector<GenLibrary> m_gameList;
		std::vector<GenLibrary> m_libList;

		size_t m_currentGameId;
		size_t m_currentLibId;

		std::vector<Event> m_eventBuffer;

		bool m_inMenu;

                GenLibrary m_soundLib;

		std::unique_ptr<IGame> m_game;
		std::unique_ptr<IGfxLib> m_lib;
		GameState m_gameState;
		std::unique_ptr<IGfxLib> m_sound;
		// std::unique_ptr<Network> m_network;

		// Game implementation part (for main menu)
		virtual void notifyEvent(std::vector<Event> &&events);
		virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
		virtual void process();
		virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;
#if defined(__linux__)
		virtual void WhereAmI(std::ostream &os) const;
#endif
	  virtual void notifyNetwork(std::vector<NetworkPacket> &&events);
	  virtual std::vector<NetworkPacket> getNetworkToSend();
                // Main menu
                size_t m_firstLibIndex;
                size_t m_firstGameIndex;

                size_t m_selectedLibId;
                size_t m_selectedGameId;

                bool m_menuLib;
	  std::unique_ptr<Network::TCPSocket>	m_sock;
	};
}

#endif // !CORE_HPP_
