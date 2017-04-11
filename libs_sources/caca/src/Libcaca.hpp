#ifndef LIBCACA_HPP_
#define LIBCACA_HPP_

#include <cstdint>
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
    virtual void loadSounds(
        std::vector<std::pair<std::string, SoundType>> const &sounds);
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
    uint16_t convert32bitsColorTo16Bits(Color color) const;

    static KeyboardKey getKeyboardKey(int code);
    static MouseKey getMouseKey(int code);
    MousePos getMousePos();

    static std::map<int, KeyboardKey> m_kb_keys;
    static std::map<int, MouseKey>    m_mouse_keys;

    static constexpr size_t m_tileSize = 1;
    size_t                  m_width;
    size_t                  m_height;
    caca_display_t *        m_win;
    caca_canvas_t *         m_canvas;
    caca_canvas_t *         m_map;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBCACA_HPP_
