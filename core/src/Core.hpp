#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <map>
#include <string>
#include <functional>
#include "IGame.hpp"
#include "IGfxLib.hpp"
#include "GenLibrary.hpp"

namespace arcade
{
	class Core
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

		std::vector<GenLibrary> m_gameList;
		std::vector<GenLibrary> m_libList;

		size_t m_currentGameId;
		size_t m_currentLibId;

		std::unique_ptr<IGame> m_game;
		std::unique_ptr<IGfxLib> m_lib;
		// std::unique_ptr<ISoundLib> m_sound;
		// std::unique_ptr<Network> m_network;
	};
}

#endif // !CORE_HPP_