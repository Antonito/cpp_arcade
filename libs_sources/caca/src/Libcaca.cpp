#include <exception>
#include <iostream>
#include "Libcaca.hpp"

namespace arcade
{
  Libcaca::Libcaca(size_t width, size_t height)
  {
    // TODO : implement
  }

  Libcaca::~Libcaca()
  {
    // TODO : implement
  }

  bool Libcaca::pollEvent(Event &e)
  {
    // TODO : implement
    return (false);
  }

  bool Libcaca::doesSupportSound() const
  {
    return (true);
  }

  void Libcaca::loadSounds(std::vector<std::string> const & sounds)
  {
    // TODO : implement
  }

  void Libcaca::playSound(int soundId)
  {
    // TODO : implement
  }

  void Libcaca::updateMap(IMap const & map)
  {
    // TODO : implement
  }

  void Libcaca::updateGUI(IGUI const & gui)
  {
    // TODO : implement
  }

  void Libcaca::display()
  {
    // TODO : implement
  }

  void Libcaca::clear()
  {
    // TODO : implement
  }

  KeyboardKey Libcaca::getKeyboardKey(caca_event_t const *code)
  {
    // TODO : implement
    return (KeyboardKey::KB_NONE);
  }

  MouseKey Libcaca::getMouseKey(caca_event_t const *code)
  {
    // TODO : implement
    return (MouseKey::M_NONE);
  }

  MouseKey Libcaca::getMouseWheel(caca_event_t const *code)
  {
    // TODO : implement
    return (MouseKey::M_NONE);
  }

  MousePos Libcaca::getMousePos()
  {
    // TODO : implement
  }
}
