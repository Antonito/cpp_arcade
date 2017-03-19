#ifndef LIBSDL_HPP_
#define LIBSDL_HPP_

#if defined(__linux__) || (__APPLE__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <map>
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
		virtual void updateMap(IMap const &map);

		// GUI
		virtual void updateGUI(IGUI const &gui);

		// Display
		virtual void display();

		// Clear
		virtual void clear();
	private:
		static KeyboardKey getKeyboardKey(SDL_Keycode code);
		static MouseKey getMouseKey(Uint8 code);
		static MouseKey getMouseWheel(SDL_MouseWheelEvent const &code);

		static std::map<SDL_Keycode, KeyboardKey> m_kb_keys;
		static std::map<Uint8, MouseKey> m_mouse_keys;

		static constexpr size_t m_tileSize = 30;

		SDL_Window *m_win;
		SDL_Surface *m_winSurface;

		SDL_Surface *m_map;
		size_t m_mapWidth;
		size_t m_mapHeight;

		SDL_Surface *m_gui;
	};
}

#endif // !LIBSDL_HPP_