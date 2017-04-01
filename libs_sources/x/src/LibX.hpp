#ifndef LIBX_HPP_
#define LIBX_HPP_

#include <cstdint>
#include <map>
#include <X11/Xlib.h>
#include "IGfxLib.hpp"

namespace arcade
{
  class LibX : public IGfxLib
  {
  public:
    LibX(size_t width = 1280, size_t height = 720);
    LibX(LibX const &other) = delete;
    ~LibX();

    LibX &operator=(LibX const &other) = delete;

    // Events
    virtual bool pollEvent(Event &e);

    // Sound
    virtual bool doesSupportSound() const;
    virtual void loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds);
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

    static constexpr long eventMask =
      KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
      PointerMotionMask | ResizeRedirectMask;

    static KeyboardKey getKeyboardKey(int code);
    static MouseKey getMouseKey(int code);
    MousePos getMousePos();

    static std::map<int, KeyboardKey> m_kb_keys;
    void setKeyMapping() const;
    static std::map<int, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    size_t m_width;
    size_t m_height;

    Display	*m_disp;
    Window	m_win;
    Window	m_root;
    GC		m_gc;
    int		m_screen;
    uint64_t	m_whitePixel;
    uint64_t	m_blackPixel;
    Atom	m_del;
    int		m_fd;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBX_HPP_
