#ifndef LIBALLEGRO5_HPP_
#define LIBALLEGRO5_HPP_

#define ALLEGRO_STATICLINK
#include <allegro5/allegro.h>
#include <map>
#include "IGfxLib.hpp"

namespace arcade
{
  class LibAllegro5 : public IGfxLib
  {
  public:
    LibAllegro5(size_t width = 1280, size_t height = 720);
    LibAllegro5(LibAllegro5 const &other) = delete;
    ~LibAllegro5();

    LibAllegro5 &operator=(LibAllegro5 const &other) = delete;

    // Events
    virtual bool pollEvent(Event &e);

    // Sound
    virtual bool doesSupportSound() const;
    virtual void loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds);
    virtual void soundControl(Sound const &sound);

    // Sprites
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
    static MouseKey getMouseWheel(int code);
    MousePos getMousePos();

    static std::map<int, KeyboardKey> m_kb_keys;
    static std::map<int, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    size_t m_width;
    size_t m_height;

    ALLEGRO_DISPLAY	*m_win;
    ALLEGRO_EVENT_QUEUE	*m_event;
    ALLEGRO_TIMER	*m_timer;
    ALLEGRO_BITMAP	*m_gui;
    ALLEGRO_BITMAP	*m_map;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBALLEGRO5_HPP_
