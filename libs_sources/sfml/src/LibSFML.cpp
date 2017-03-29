#include <exception>
#include <iostream>
#include "LibSFML.hpp"

namespace arcade
{
  LibSFML::LibSFML(size_t width, size_t height) :
    m_map(nullptr), m_mapWidth(0), m_mapHeight(0), m_gui(nullptr)
  {
    m_win = std::make_unique<sf::Window>(sf::VideoMode(width, height), "Arcade");
  }

  LibSFML::~LibSFML()
  {
  }

  bool LibSFML::pollEvent(Event & e)
  {
    (void)e;
    // TODO: Implement
  }

  bool LibSFML::doesSupportSound() const
  {
    return (true);
  }

  void LibSFML::loadSounds(std::vector<std::string> const & sounds)
  {
    (void)sounds;
    // TODO : implement
  }

  void LibSFML::playSound(int soundId)
  {
    (void)soundId;
    // TODO : implement
  }

  void LibSFML::updateMap(IMap const & map)
  {
    (void)map;
    // TODO : implement
  }

  void LibSFML::updateGUI(IGUI const & gui)
  {
    (void)gui;
    // TODO: Implement
  }

  void LibSFML::display()
  {
    // TODO : implement
  }
  void LibSFML::clear()
  {
    // TODO : implement
  }

#if 0
  KeyboardKey LibSFML::getKeyboardKey(SFML_Keycode code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibSFML::getMouseKey(Uint8 code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      {
	return (m_mouse_keys[code]);
      }
    return (MouseKey::M_NONE);
  }

  MouseKey LibSFML::getMouseWheel(SFML_MouseWheelEvent const & code)
  {
    // TODO: Implement
  }
#endif

}
