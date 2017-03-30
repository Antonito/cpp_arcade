#ifndef LIBCACA_HPP_
#define LIBCACA_HPP_

#include <map>
#include <caca.h>
#include "IGfxLib.hpp"

namespace arcade
{
  class Libcaca : public IGfxLib
  {
  public:
    Libcaca(size_t width = 1280, size_t height = 720);
    Libcaca(Libcaca const &other) = delete;
    ~Libcaca();

    Libcaca &operator=(Libcaca const &other) = delete;

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

    static KeyboardKey getKeyboardKey(int code);
    static MouseKey getMouseKey(int code);
    MousePos getMousePos();

    static std::map<int, KeyboardKey> m_kb_keys;
    static std::map<int, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    caca_display_t *m_win;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBCACA_HPP_
