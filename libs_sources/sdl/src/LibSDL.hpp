#ifndef LIBSDL_HPP_
#define LIBSDL_HPP_

#if defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
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
    virtual void loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds);
    virtual void soundControl(Sound const &sound);

    // Map
    virtual void updateMap(IMap const &map);

    // GUI
    virtual void updateGUI(IGUI &gui);

    // Display
    virtual void display();

    // Sprites
    virtual void loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);

    // Clear
    virtual void clear();
  private:
    static KeyboardKey getKeyboardKey(SDL_Keycode code);
    static MouseKey getMouseKey(Uint8 code);
    static MouseKey getMouseWheel(SDL_MouseWheelEvent const &code);

    static std::map<SDL_Keycode, KeyboardKey> m_kb_keys;
    static std::map<Uint8, MouseKey> m_mouse_keys;

    static void fillRect(SDL_Surface *surface, SDL_Rect *rect, Color color);

    static constexpr size_t m_maxTileSize = 30;

    SDL_Window *m_win;
    SDL_Surface *m_winSurface;

    std::vector<std::vector<SDL_Surface *>> m_sprites;

    TTF_Font *m_font;
  };
}

#endif // !LIBSDL_HPP_
