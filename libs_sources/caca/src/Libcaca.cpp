#include <exception>
#include <iostream>
#include "Libcaca.hpp"

namespace arcade
{
  LibSFML::LibSFML(size_t width, size_t height)
  {
    // TODO : implement
  }

  LibSFML::~LibSFML()
  {
    // TODO : implement
  }

  bool LibSFML::pollEvent(Event & e)
  {
    // TODO : implement
    return (false);
  }

  bool LibSFML::doesSupportSound() const
  {
    return (true);
  }

  void LibSFML::loadSounds(std::vector<std::string> const & sounds)
  {
    // TODO : implement
  }

  void LibSFML::playSound(int soundId)
  {
    // TODO : implement
  }

  void LibSFML::updateMap(IMap const & map)
  {
    // TODO : implement
  }

  void LibSFML::updateGUI(IGUI const & gui)
  {
    // TODO : implement
  }

  void LibSFML::display()
  {
    // TODO : implement
  }

  void LibSFML::clear()
  {
    // TODO : implement
  }

  KeyboardKey LibSFML::getKeyboardKey(sf::Keyboard::Key code)
  {
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibSFML::getMouseKey(sf::Mouse::Button code)
  {
    return (MouseKey::M_NONE);
  }

  MouseKey LibSFML::getMouseWheel(sf::Mouse::Wheel code)
  {
    // TODO : implement
  }

  MousePos LibSFML::getMousePos()
  {
    // TODO : implement
  }
}
