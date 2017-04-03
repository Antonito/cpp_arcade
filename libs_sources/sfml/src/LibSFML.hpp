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
    static KeyboardKey getKeyboardKey(sf::Keyboard::Key code);
    static MouseKey getMouseKey(sf::Mouse::Button code);
    static MouseKey getMouseWheel(sf::Mouse::Wheel code);
    MousePos getMousePos();

    static std::map<sf::Keyboard::Key, KeyboardKey> m_kb_keys;
    static std::map<sf::Mouse::Button, MouseKey> m_mouse_keys;

    static constexpr size_t m_tileSize = 24;

    std::unique_ptr<sf::RenderWindow> m_win;
    std::vector<std::unique_ptr<sf::Music>> m_music;
    std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffer;
    std::vector<std::unique_ptr<sf::Sound>> m_sound;
    sf::Vector2i m_mousePos;

    std::unique_ptr<uint32_t[]> m_guiPix;
    std::unique_ptr<sf::Texture> m_gui;
    std::unique_ptr<sf::Sprite> m_guiSprite;

    std::unique_ptr<uint32_t[]> m_mapPix;
    std::unique_ptr<sf::Texture> m_map;
    std::unique_ptr<sf::Sprite> m_mapSprite;

    size_t m_mapWidth;
    size_t m_mapHeight;
  };
}

#endif // !LIBSFML_HPP_
