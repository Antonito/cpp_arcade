#ifndef LIBSDL_HPP_
#define LIBSDL_HPP_

#if defined(__linux__) || (__APPLE__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include "IGfxLib.hpp"

namespace arcade
{
	class LibSDL : public IGfxLib
	{
	public:
		LibSDL(size_t width = 1280, size_t height = 720);
		LibSDL(LibSDL const &other) = delete;
		~LibSDL();

		LibSDL &operator=(LibSDL const &other) = delete;

		// Events
		virtual bool pollEvent(Event &e);

		// Sound
		virtual bool doesSupportSound() const;
		virtual void loadSounds(std::vector<std::string> const &sounds);
		virtual void playSound(int soundId);

		// Map
		virtual void displayMap(IMap const &map);

		// Menu
		virtual void displayMenu(IMenu const &menu);

		// GUI
		virtual void displayGUI(IGUI const &gui);
	private:
		SDL_Window *m_win;
		SDL_Surface *m_winSurface;
	};
}

#endif // !LIBSDL_HPP_