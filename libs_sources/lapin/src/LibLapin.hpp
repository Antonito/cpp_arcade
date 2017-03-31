#ifndef LIBLAPIN_HPP_
#define LIBLAPIN_HPP_

#include <cstdint>
#include <map>
#include "lapin.h"
#include "IGfxLib.hpp"

namespace arcade
{
  class LibLapin : public IGfxLib
  {
  public:
    LibLapin(size_t width = 1280, size_t height = 720);
    LibLapin(LibLapin const &other) = delete;
    ~LibLapin();

    LibLapin &operator=(LibLapin const &other) = delete;

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
    // LibLapin handlers
    static t_bunny_response _mainLoop(void *data);
    static t_bunny_response _eventLoop(void *data);
    static t_bunny_response _keyHandler(t_bunny_event_state state,
					t_bunny_keysym key,
					void *dat);
    static t_bunny_response _clickHandler(t_bunny_event_state state,
					  t_bunny_mouse_button but,
					  void *dat);
    static t_bunny_response _moveHandler(t_bunny_position const *relative,
					 void *dat);
    static t_bunny_response _wheelHandler(int wheelId, int delta, void *dat);
    static t_bunny_response _lostFocusHandler(t_bunny_window const *win, void *data);
    static t_bunny_response _gotFocusHandler(t_bunny_window const *win, void *data);
    static t_bunny_response _resizeHandler(t_bunny_window const *win,
					   t_bunny_position const *size, void *data);
    static t_bunny_response _closeHandler(t_bunny_window const *win, void *data);

    static KeyboardKey getKeyboardKey(t_bunny_keysym code);
    static MouseKey getMouseKey(t_bunny_mouse_button code);
    MousePos getMousePos();

    static std::map<t_bunny_keysym, KeyboardKey> m_kb_keys;
    static std::map<t_bunny_mouse_button, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    size_t m_width;
    size_t m_height;

    t_bunny_window	*m_win;
    t_bunny_pixelarray	*m_gui;
    t_bunny_pixelarray	*m_map;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBLAPIN_HPP_
