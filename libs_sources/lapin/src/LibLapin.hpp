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
    static KeyboardKey getKeyboardKey(int code);
    static MouseKey getMouseKey(int code);
    MousePos getMousePos();

    static std::map<int, KeyboardKey> m_kb_keys;
    static std::map<int, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;
    size_t m_width;
    size_t m_height;

    t_bunny_window	*m_win;
    t_bunny_pixelarray	*m_map;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBLAPIN_HPP_
