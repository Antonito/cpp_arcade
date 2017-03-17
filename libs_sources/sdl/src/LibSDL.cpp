#include <exception>
#include <iostream>
#include "LibSDL.hpp"

namespace arcade
{
	LibSDL::LibSDL(size_t width, size_t height)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "Error while initializing SDL2 : " << SDL_GetError() << std::endl;
			throw std::exception(); // TODO: create a good exception
		}

		m_win = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (m_win == NULL)
		{
			std::cerr << "Error while creating SDL2 Window (1): " << SDL_GetError() << std::endl;
			throw std::exception(); // TODO: create a good exception
		}

		m_winSurface = SDL_GetWindowSurface(m_win);

		if (m_winSurface == NULL)
		{
			std::cerr << "Error while creating SDL2 Window (2): " << SDL_GetError() << std::endl;
			throw std::exception(); // TODO: create a good exception
		}
	}

	LibSDL::~LibSDL()
	{
		SDL_Event e;

		while (SDL_WaitEvent(&e))
			if (e.type == SDL_QUIT)
				break;
		SDL_DestroyWindow(m_win);
		SDL_Quit();
	}

	bool LibSDL::pollEvent(Event & e)
	{
		return false;
	}

	bool LibSDL::doesSupportSound() const
	{
		return (true);
	}

	void LibSDL::loadSounds(std::vector<std::string> const & sounds)
	{
		(void)sounds;
		// TODO : implement
	}

	void LibSDL::playSound(int soundId)
	{
		(void)soundId;
		// TODO : implement
	}

	void LibSDL::displayMap(IMap const & map)
	{
		(void)map;
		// TODO : implement
	}

	void LibSDL::displayMenu(IMenu const & menu)
	{
		(void)menu;
		// TODO : implement
	}

	void LibSDL::displayGUI(IGUI const & gui)
	{
		(void)gui;
		// TODO : implement
	}


}