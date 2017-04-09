#include <exception>
#include <iostream>
#include <cstring>
#include "LibSFMLSound.hpp"
#include "RessourceError.hpp"

namespace arcade
{
  LibSFMLSound::LibSFMLSound()
  {
  }

  LibSFMLSound::~LibSFMLSound()
  {
  }

  bool LibSFMLSound::pollEvent(Event &)
  {
    return (false);
  }

  bool LibSFMLSound::doesSupportSound() const
  {
    return (true);
  }

  void LibSFMLSound::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds)
  {
    size_t index;

    m_sound.clear();
    m_soundBuffer.clear();
    m_music.clear();
    for (std::pair<std::string, SoundType> const &p : sounds)
      {
	if (p.second == SoundType::MUSIC)
	  {
	    m_music.push_back(std::make_unique<sf::Music>());
	    sf::Music &cur = *m_music.back();
	    if (!cur.openFromFile(p.first))
	      {
		std::cerr << "Cannot open music: " << p.first << std::endl;
		throw RessourceError("Error loading music");
	      }
            index = m_music.size() - 1;
	  }
	else
	  {
	  m_soundBuffer.emplace_back();
          sf::SoundBuffer &buf = m_soundBuffer.back();
	    if (!buf.loadFromFile(p.first))
	      {
		std::cerr << "Cannot open sound: " << p.first << std::endl;
		throw RessourceError("Error loading sound");
	      }
	    m_sound.emplace_back();
            sf::Sound &sound = m_sound.back();
            sound.setBuffer(buf);
            index = m_sound.size() - 1;
	  }
        m_soundIndex.emplace_back(p.second, index);
      }
  }

  void LibSFMLSound::soundControl(Sound const &sound)
  {
    SoundType type = m_soundIndex[sound.id].first;
    size_t index = m_soundIndex[sound.id].second;

    if (type == SoundType::MUSIC)
    {
      m_music[index]->play();
    }
    else
    {
      m_sound[index].play();
    }
  }

  void LibSFMLSound::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
    // Move the given vector
    std::vector<std::unique_ptr<ISprite>> sp(std::move(sprites));

    // Remove all the current sprites
    sp.clear();
  }

  void LibSFMLSound::updateMap(IMap const &)
  {
  }

  void LibSFMLSound::updateGUI(IGUI &)
  {
  }

  void LibSFMLSound::display()
  {
  }

  void LibSFMLSound::clear()
  {
  }
}