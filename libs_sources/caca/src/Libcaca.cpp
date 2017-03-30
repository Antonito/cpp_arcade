#include <exception>
#include <iostream>
#include "Libcaca.hpp"

namespace arcade
{
  Libcaca::Libcaca(size_t width, size_t height) : m_win(nullptr), m_canvas(nullptr),
						  m_mapWidth(0), m_mapHeight(0)
  {
    static_cast<void>(width);
    static_cast<void>(height);
    m_win = caca_create_display(NULL);
    if (!m_win)
      {
	std::cerr << "Cannot create libcaca window" << std::endl;
	throw std::exception(); // TODO: Exception
      }
    caca_set_display_title(m_win, "Arcade");
    m_canvas = caca_get_canvas(m_win);
    if (!m_canvas)
      {
	std::cerr << "Cannot get libcaca canvas" << std::endl;
	throw std::exception(); // TODO: Exception
      }
    m_width = caca_get_canvas_width(m_canvas);
    m_height = caca_get_canvas_height(m_canvas);
  }

  Libcaca::~Libcaca()
  {
    // TODO : implement
    caca_free_canvas(m_canvas);
    caca_free_display(m_win);
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
    caca_refresh_display(m_win);
  }

  void Libcaca::clear()
  {
    caca_clear_canvas(m_canvas);
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
