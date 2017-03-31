#ifndef LIBNCURSES_HPP_
#define LIBNCURSES_HPP_

#include <cstdint>
#include <map>
#include <ncurses.h>
#include "IGfxLib.hpp"

namespace arcade
{
  class LibNcurses : public IGfxLib
  {
  public:
    LibNcurses(size_t width = 1280, size_t height = 720);
    LibNcurses(LibNcurses const &other) = delete;
    ~LibNcurses();

    LibNcurses &operator=(LibNcurses const &other) = delete;

    // Events
    virtual bool pollEvent(Event &e);

    // Sound
    virtual bool doesSupportSound() const;
    virtual void loadSounds(std::vector<std::string> const &sounds);
    virtual void soundControl(Sound const &sound);

	// Sprite
	virtual void loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);

    // Map
    virtual void updateMap(IMap const &map);

    // GUI
    virtual void updateGUI(IGUI &gui);

    // Display
    virtual void display();

    // Clear
    virtual void clear();
  private:
    static KeyboardKey getKeyboardKey(int code);
    static MouseKey getMouseKey(int code);
    MousePos getMousePos();

    static std::map<int, KeyboardKey> m_kb_keys;
    static std::map<int, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    size_t m_width;
    size_t m_height;

    WINDOW	*m_win;
    WINDOW	*m_map;
    WINDOW	*m_gui;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBNCURSES_HPP_
