#include <dirent.h>
#include "Core.hpp"
#include "GameState.hpp"
#include "Logger.hpp"

//
// PLEASE READ CAREFULLY
// 
// To compile you need "dirent.h".
// This file is not directly available in Visual Studio.
// You can download it here:
// https://raw.githubusercontent.com/tronkko/dirent/master/include/dirent.h
//
// Then move it in your Visual Studio include directory:
// VS 17 (on two lines): C:\Program Files (x86)\Microsoft Visual Studio\
// 2017\Enterprise\VC\Tools\MSVC\14.10.25017\include
// VS 14: C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include
//
// To finish relaunch your Visual Studio and it should be ok :)
//

namespace arcade
{
	Core::Core() : m_currentGameId(0), m_currentLibId(0)
	{
		m_state = INGAME;

		m_map = std::make_unique<Map>(0, 0);
		m_gui = std::make_unique<GUI>();

		// Create the main menu GUI
		Component comp;

		comp.setBackgroundColor(Color::White);
		comp.setX(0.0);
		comp.setY(0.0);
		comp.setWidth(1.0);
		comp.setHeight(1.0);
		m_gui->push(comp);

		comp.setBackgroundColor(Color(0, 0, 0, 170));

		comp.setX(0.3);
		comp.setY(0.1);
		comp.setWidth(0.4);
		comp.setHeight(0.1);
		m_gui->push(comp);

		comp.setWidth(0.35);
		comp.setHeight(0.6);

		comp.setX(0.1);
		comp.setY(0.3);
		m_gui->push(comp);

		comp.setX(0.55);
		m_gui->push(comp);

		m_inMenu = true;
		m_game = std::unique_ptr<IGame>(this);

#ifdef DEBUG
		Nope::Log::Debug << "Core constructed";
#endif
	}

	Core::~Core()
	{
#ifdef DEBUG
		Nope::Log::Debug << "Core destructed";
#endif
	}

	void Core::launch()
	{
		GameState state = MENU;

		// Log
		Nope::Log::Info << "Launching the core";

		// Load all the game and graphic libraries
		this->initLists();

		// Set the current library to the first one
		m_lib = std::unique_ptr<IGfxLib>(m_libList[0].getFunction<IGfxLib* ()>("getLib")());

		while (state != QUIT)
		{
			switch (state)
			{
			case INGAME:
			case PAUSED:
			case GAME_MENU:
				state = this->gameLoop();
				break;
			case MENU:
				state = this->menuLoop();
				break;
			default:
				state = QUIT;
				break;
			}
		}
		// Log
		Nope::Log::Info << "Exiting the core";
	}

	GameState Core::gameLoop()
	{
		GameState state = INGAME;
		std::vector<Event> events;
		std::vector<int> sounds;
		Event ev;

		Nope::Log::Info << "Launching a game";
		while (true)
		{
			events.clear();
			sounds.clear();
			m_lib->clear();
			if (state != INGAME && state != PAUSED && state != GAME_MENU)
			{
				break ;
			}
			// Events
			while (m_lib->pollEvent(ev))
				events.push_back(ev);

#ifdef DEBUG
			Nope::Log::Debug << "Polled events";
#endif
			m_game->notifyEvent(std::move(events));
#ifdef DEBUG
			Nope::Log::Debug << "Notified events";
#endif
			if (m_game.get() == nullptr)
			{
				return (QUIT);
			}
			// Network
			// TODO: implement

			// Game loop
			m_game->process();
#ifdef DEBUG
			Nope::Log::Debug << "Processed game loop";
#endif
			// Sound
			sounds = m_game->getSoundsToPlay();
#ifdef DEBUG
			Nope::Log::Debug << "Get sounds to play";
#endif
			// play sounds

			// Map
			m_lib->updateMap(m_game->getCurrentMap());
#ifdef DEBUG
			Nope::Log::Debug << "Send map to lib";
#endif

			// GUI
			m_lib->updateGUI(m_game->getGUI());
#ifdef DEBUG
			Nope::Log::Debug << "Send GUI to lib";
#endif
			// Display
			m_lib->display();
#ifdef DEBUG
			Nope::Log::Debug << "Displayed";
#endif
			// GameState
			state = m_game->getGameState();
#ifdef DEBUG
			Nope::Log::Debug << "Game state updated";
#endif
		}
		Nope::Log::Info << "Exiting a game";
		return QUIT;
	}

	GameState Core::menuLoop()
	{
		Nope::Log::Info << "Entering the main menu";

		// Here we use directly use the first lib and game, but normally
		// there is a menu to let the user choose
		//m_game = std::unique_ptr<IGame>(m_gameList[0].getFunction<IGame* ()>("getGame")());



		Nope::Log::Info << "Leaving the main menu";

		return INGAME;
	}

	// We use dirent.h for cross-platform and lightweight solution
	void Core::initLists()
	{
		DIR *dir;
		struct dirent *ent;

		// Open "dir/" directory
		if ((dir = opendir("lib")) != NULL)
		{
			Nope::Log::Info << "Opened directory 'lib'";
			// Check all the entities in the directory
			while ((ent = readdir(dir)) != NULL)
			{
				Nope::Log::Info << "Reading '" << ent->d_name << "'";
				// If it's a REGULAR file and it's name
				// is formated like "lib_arcade_XXX.so"
				if (ent->d_type == DT_REG &&
#if defined(__linux__) || (__APPLE__)
					Core::isNameValid(ent->d_name, "lib_arcade_", ".so"))
#else
					Core::isNameValid(ent->d_name, "lib_arcade_", ".dll"))
#endif
				{
					Nope::Log::Info << "Adding library '" << ent->d_name << "'";
					m_libList.emplace_back(std::string("lib/") + ent->d_name);
				}
			}
			// Close the dir after using it because we are well educated people :)
			closedir(dir);
			Nope::Log::Info << "Closing dir 'lib'";
		}
		else
		{
			throw std::exception(); // TODO: create a good exception
		}

		// Check if there was at least one graphic lib
		if (m_libList.size() == 0)
		{
			throw std::exception(); // TODO: there is no graphic library
		}

		// Open "games/" directory
		if ((dir = opendir("games")) != NULL)
		{
			Nope::Log::Info << "Opened directory 'games'";
			// Check all the entities in the directory
			while ((ent = readdir(dir)) != NULL)
			{
				Nope::Log::Info << "Reading '" << ent->d_name << "'";				// If it's a REGULAR file and it's a .so
				if (ent->d_type == DT_REG &&
#if defined(__linux__) || (__APPLE__)
					Core::isNameValid(ent->d_name, "", ".so"))
#else
					Core::isNameValid(ent->d_name, "", ".dll"))
#endif
				{
					Nope::Log::Info << "Adding library '" << ent->d_name << "'";
					m_gameList.emplace_back(std::string("games/") + ent->d_name);
				}
			}
			// Close the dir after using it because we are well educated people
			// and yes all of this was copy/pasted :)
			closedir(dir);
			Nope::Log::Info << "Closing dir 'lib'";
		}
		else
		{
			throw std::exception(); // TODO: create a good exception
		}
	}

	// Check if the name string begins with prefix and end with suffix
	// ex: isNameValid("liboui.a", "lib", ".a") => true
	//	   isNameValid("liboui.a", "lib_arcade", ".a") => false
	//	   isNameValid("liboui.a", "lib", ".so") => false
	bool Core::isNameValid(std::string const & name,
		std::string const &prefix, std::string const &suffix)
	{
		return (name.compare(0, prefix.length(), prefix) == 0 &&
			name.compare(name.length() - suffix.length(),
				suffix.length(), suffix) == 0);
	}

	void Core::notifyEvent(std::vector<Event>&& events)
	{
		std::vector<Event> ev = events;

		for (Event const &e : ev)
		{
			if (e.type == EventType::ET_QUIT)
			{
				m_state = QUIT;
				m_game.release();
			}
			else if (e.type == EventType::ET_KEYBOARD &&
				e.action == ActionType::AT_PRESSED)
			{
				if (e.kb_key == KeyboardKey::KB_ESCAPE)
				{
					m_state = QUIT;
					m_game.release();
				}
				else if (e.kb_key == KeyboardKey::KB_ENTER)
				{
					m_game.release();
					m_game = std::unique_ptr<IGame>(m_gameList[m_currentGameId].getFunction<IGame *()>("getGame")());
				}
			}
		}
	}

	std::vector<std::string> Core::getSoundsToLoad() const
	{
		return (std::vector<std::string>());
	}

	void Core::process()
	{
	}
}