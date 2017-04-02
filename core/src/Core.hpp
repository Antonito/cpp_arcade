#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <map>
#include <string>
#include <functional>
#include "IGame.hpp"
#include "IGfxLib.hpp"
#include "GenLibrary.hpp"
#include "AGame.hpp"

namespace arcade
{
	class Core : public AGame
	{
	public:
		Core();
		Core(Core const &other) = delete;
		~Core();

		Core &operator=(Core const &other) = delete;

		void launch();

	private:
		GameState gameLoop();
		GameState menuLoop();

		void initLists();

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

		std::unique_ptr<IGame> m_game;
		std::unique_ptr<IGfxLib> m_lib;
		GameState m_gameState;
		// std::unique_ptr<ISoundLib> m_sound;
		// std::unique_ptr<Network> m_network;

		// Game implementation part (for main menu)
		virtual void notifyEvent(std::vector<Event> &&events);
		virtual std::vector<std::string> getSoundsToLoad() const;
		virtual void process();
		virtual std::vector<std::unique_ptr<ISprite>> &&getSpritesToLoad() const;
		virtual WhereAmI *getWhereAmI() const;
	};
}

#endif // !CORE_HPP_