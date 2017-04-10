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

    t_bunny_window	*getWin() const;
    t_bunny_pixelarray	*getMap() const;
    t_bunny_pixelarray	*getGui() const;
    t_bunny_pixelarray	*getRender() const;

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
    static void _blit(t_bunny_pixelarray *dest, t_bunny_pixelarray const *src);

    static KeyboardKey getKeyboardKey(t_bunny_keysym code);
    static MouseKey getMouseKey(t_bunny_mouse_button code);
    MousePos getMousePos();

    static std::map<t_bunny_keysym, KeyboardKey> m_kb_keys;
    static std::map<t_bunny_mouse_button, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    size_t m_width;
    size_t m_height;

    t_bunny_window	*m_win;
    t_bunny_pixelarray  *m_render;
    t_bunny_pixelarray	*m_gui;
    t_bunny_pixelarray	*m_map;

    std::vector<t_bunny_music *>	m_music;
    std::vector<t_bunny_effect *>	m_effect;
    std::vector<t_bunny_sound *>	m_sound;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBLAPIN_HPP_
