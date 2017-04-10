#ifndef LIBSFMLSOUND_HPP_
#define LIBSFMLSOUND_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "IGfxLib.hpp"

namespace arcade
{
  class LibSFMLSound : public IGfxLib
  {
  public:
    LibSFMLSound();
    LibSFMLSound(LibSFMLSound const &other) = delete;
    ~LibSFMLSound();

    LibSFMLSound &operator=(LibSFMLSound const &other) = delete;

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
    std::vector<std::unique_ptr<sf::Music>> m_music;
    std::vector<sf::SoundBuffer> m_soundBuffer;
    std::vector<std::unique_ptr<sf::Sound>> m_sound;
    std::vector<std::pair<SoundType, size_t>> m_soundIndex;
  };
}

#endif // !LIBSFMLSOUND_HPP_
