#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_

#include <SFML/Window.hpp>
#include <map>
#include "IGfxLib.hpp"

namespace arcade
{
  class LibSFML : public IGfxLib
  {
  public:
    LibSFML(size_t width = 1280, size_t height = 720);
    LibSFML(LibSFML const &other) = delete;
    ~LibSFML();

    LibSFML &operator=(LibSFML const &other) = delete;

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
#if 0
    static KeyboardKey getKeyboardKey(SFML_Keycode code);
    static MouseKey getMouseKey(Uint8 code);
    static MouseKey getMouseWheel(SFML_MouseWheelEvent const &code);

    static std::map<SFML_Keycode, KeyboardKey> m_kb_keys;
    static std::map<Uint8, MouseKey> m_mouse_keys;
#endif

    static constexpr size_t m_tileSize = 24;

    std::unique_ptr<sf::Window> m_win;
#if 0
    SFML_Surface *m_winSurface;

    SFML_Surface *m_map;
    size_t m_mapWidth;
    size_t m_mapHeight;

    SFML_Surface *m_gui;
#endif
  };
}

#endif // !LIBSFML_HPP_
