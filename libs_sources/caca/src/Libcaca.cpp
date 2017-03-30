#include <exception>
#include <iostream>
#include "Libcaca.hpp"

namespace arcade
{
  Libcaca::Libcaca(size_t width, size_t height) : m_win(nullptr)
  {
    // TODO : implement
  }

  Libcaca::~Libcaca()
  {
    // TODO : implement
  }

  bool Libcaca::pollEvent(Event &e)
  {
    caca_event_t	event;

    if (caca_get_event(m_win, CACA_EVENT_ANY, &event, 0))
      {
	switch (caca_get_event_type(&event))
	  {
	  case CACA_EVENT_QUIT:
	    // The window requested to be closed
	    e.type = EventType::ET_QUIT;
	    break;
	  case CACA_EVENT_RESIZE:
	    // The window was resized
	    break;

	  case CACA_EVENT_MOUSE_MOTION:
	    // The mouse moved
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_MOVED;
	    e.m_key = MouseKey::M_NONE;
	    //e.pos_abs = ;
	    // TODO: Get mouse position
	    break;
	  case CACA_EVENT_MOUSE_PRESS:
	    // A mouse button was pressed
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_PRESSED;
	    e.m_key = Libcaca::getMouseKey(caca_get_event_mouse_button(&event));
	    break;
	  case CACA_EVENT_MOUSE_RELEASE:
	    // A mouse button was released
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_RELEASED;
	    e.m_key = Libcaca::getMouseKey(caca_get_event_mouse_button(&event));
	    break;

	  case CACA_EVENT_KEY_PRESS:
	    // A key was pressed
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_PRESSED;
	    e.kb_key = getKeyboardKey(caca_get_event_key_ch(&event));
	    break;
	  case CACA_EVENT_KEY_RELEASE:
	    // A key was released
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_RELEASED;
	    e.kb_key = getKeyboardKey(caca_get_event_key_ch(&event));
	    break;
	  default:
	    e.type = EventType::ET_NONE;
	    e.action = ActionType::AT_NONE;
	    e.kb_key = KeyboardKey::KB_NONE;
	    break;
	  }
	return (true);
      }
    return (false);
  }

  bool Libcaca::doesSupportSound() const
  {
    return (false);
  }

  void Libcaca::loadSounds(std::vector<std::string> const & sounds)
  {
    static_cast<void>(sounds);
  }

  void Libcaca::playSound(int soundId)
  {
    static_cast<void>(soundId);
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

  KeyboardKey Libcaca::getKeyboardKey(int code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey Libcaca::getMouseKey(int code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      return (m_mouse_keys[code]);
    return (MouseKey::M_NONE);
  }

  MousePos Libcaca::getMousePos()
  {
    MousePos pos;

    // TODO : Check correctness
    pos.x = caca_get_mouse_x(m_win);
    pos.y = caca_get_mouse_y(m_win);
    return (pos);
  }
}
