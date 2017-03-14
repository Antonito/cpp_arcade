#include <dirent.h>
#include "Core.hpp"
#include "GameState.hpp"

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
	}

	Core::~Core()
	{
	}

	void Core::launch()
	{
		GameState state = MENU;

		// Load all the game and graphic libraries
		this->initLists();

		// Set the current library to the first one
		m_lib = m_libList[0].getFunction<std::unique_ptr<IGfxLib> &&()>("getLib")();

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
	}

	GameState Core::gameLoop()
	{
		// We have no game currently so we exit immediately
		return QUIT;
	}

	GameState Core::menuLoop()
	{
		// Here we use directly use the first lib and game, but normally
		// there is a menu to let the user choose

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
			// Check all the entities in the directory
			while ((ent = readdir(dir)) != NULL)
			{
				// If it's a REGULAR file and it's name
				// is formated like "lib_arcade_XXX.so"
				if (ent->d_type == DT_REG &&
					Core::isNameValid(ent->d_name, "lib_arcade_", ".so"))
				{
					m_libList.emplace_back(std::string("lib/") + ent->d_name);
				}
			}
			// Close the dir after using it because we are well educated people :)
			closedir(dir);
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
			// Check all the entities in the directory
			while ((ent = readdir(dir)) != NULL)
			{
				// If it's a REGULAR file and it's a .so
				if (ent->d_type == DT_REG &&
					Core::isNameValid(ent->d_name, "", ".so"))
				{
					m_gameList.emplace_back(std::string("games/") + ent->d_name);
				}
			}
			// Close the dir after using it because we are well educated people
			// and yes all of this was copy/pasted :)
			closedir(dir);
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
			name.compare(name.length() - suffix.length() - 1,
				suffix.length(), suffix) == 0);
	}
}