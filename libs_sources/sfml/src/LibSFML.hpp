#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    virtual void loadSounds(
        std::vector<std::pair<std::string, SoundType>> const &sounds);
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
    static KeyboardKey getKeyboardKey(sf::Keyboard::Key code);
    static MouseKey getMouseKey(sf::Mouse::Button code);
    static MouseKey getMouseWheel(sf::Mouse::Wheel code);
    MousePos getMousePos();

    static std::map<sf::Keyboard::Key, KeyboardKey> m_kb_keys;
    static std::map<sf::Mouse::Button, MouseKey>    m_mouse_keys;

    static constexpr size_t m_maxTileSize = 24;

    std::unique_ptr<sf::RenderWindow>       m_win;
    std::vector<std::unique_ptr<sf::Music>> m_music;
    std::vector<sf::SoundBuffer>            m_soundBuffer;
    std::vector<std::unique_ptr<sf::Sound>> m_sound;
    std::vector<std::pair<SoundType, size_t>> m_soundIndex;
    sf::Vector2i m_mousePos;

    std::vector<std::vector<sf::Texture>> m_sprites;

    sf::Font m_font;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBSFML_HPP_
