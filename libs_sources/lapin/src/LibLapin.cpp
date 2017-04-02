#include <cassert>
#include <exception>
#include <iostream>
#include "LibLapin.hpp"

namespace arcade
{
  LibLapin::LibLapin(size_t width, size_t height) : m_width(width), m_height(height),
						    m_gui(nullptr), m_map(nullptr),
						    m_mapWidth(0), m_mapHeight(0)
  {
    m_win = bunny_start(width, height, false, "Arcade lapin");
    if (!m_win)
      {
	std::cerr << "Cannot create libLapin Window"
#if defined(DEBUG)
		  << " [" << width << "x" << height << "]"
#endif
		  << std::endl;
	throw std::exception(); // TODO: Exception
      }
    m_gui = bunny_new_pixelarray(width, height);
    if (!m_gui)
      {
	std::cerr << "Cannot create pixelarray" << std::endl;
	throw std::exception(); // TODO: Exception
      }
    bunny_set_loop_main_function(&LibLapin::_mainLoop);
	bunny_loop(m_win, 60, nullptr);
  }

  LibLapin::~LibLapin()
  {
    //bunny_delete_clipable(&m_gui->clipable);
    bunny_stop(m_win);
    //bunny_free(m_gui);
  }

  bool LibLapin::pollEvent(Event &e)
  {
    bool	ret = false;

    bunny_set_key_response(&LibLapin::_keyHandler);
    bunny_set_click_response(&LibLapin::_clickHandler);
    bunny_set_move_response(&LibLapin::_moveHandler);
    bunny_set_wheel_response(&LibLapin::_wheelHandler);
    bunny_set_lost_focus_response(&LibLapin::_lostFocusHandler);
    bunny_set_get_focus_response(&LibLapin::_gotFocusHandler);
    bunny_set_resize_response(&LibLapin::_resizeHandler);
    bunny_set_close_response(&LibLapin::_closeHandler);
    bunny_set_loop_main_function(&LibLapin::_eventLoop);
    if (bunny_loop(m_win, 60, &e) == EXIT_ON_SUCCESS)
      {
	ret = true;
      }
    bunny_set_loop_main_function(&LibLapin::_mainLoop);
    bunny_set_key_response(nullptr);
    bunny_set_click_response(nullptr);
    bunny_set_move_response(nullptr);
    bunny_set_wheel_response(nullptr);
    bunny_set_lost_focus_response(nullptr);
    bunny_set_get_focus_response(nullptr);
    bunny_set_resize_response(nullptr);
    bunny_set_close_response(nullptr);
    return (ret);
  }

  bool LibLapin::doesSupportSound() const
  {
    return (true);
  }

  void LibLapin::loadSounds(std::vector<std::string> const & sounds)
  {
    // TODO
    static_cast<void>(sounds);
  }

  void LibLapin::soundControl(Sound const &sound)
  {
    // TODO
  }

  void LibLapin::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
	  std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));
  }

  void LibLapin::updateMap(IMap const & map)
  {
    // TODO
    if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
      {

      }

    for (size_t l = 0; l < map.getLayerNb(); ++l)
      {
	for (size_t y = 0; y < m_mapHeight; ++y)
	  {
	    for (size_t x = 0; x < m_mapWidth; ++x)
	      {
		ITile const &tile = map.at(l, x, y);
		if (tile.getSpriteId() != 0 && false) // TODO: Enable
		  {
		  }
		else
		  {
		    Color color = tile.getColor();
		    if (color.a != 0)
		      {
			for (size_t _y = 0; _y < m_tileSize; ++_y)
			  {
			    for (size_t _x = 0; _x < m_tileSize; ++_x)
			      {
				size_t X = x * m_tileSize + _x;
				size_t Y = y * m_tileSize + _y;
				double a(color.a / 255.0);
			      }
			  }
		      }
		  }
	      }
	  }
      }
  }

  void LibLapin::updateGUI(IGUI & gui)
  {
    Color *pixels = reinterpret_cast<Color *>(m_gui->pixels);
    for (size_t i = 0; i < gui.size(); ++i)
      {
	IComponent const &comp = gui.at(i);
	size_t x = comp.getX() * m_width;
	size_t y = comp.getY() * m_height;
	size_t width = comp.getWidth() * m_width;
	size_t height = comp.getWidth() * m_height;
	Color color = comp.getBackgroundColor();
	double a(color.a / 255.0);
	if (color.a != 0)
	  {
	    for (size_t _y = 0; _y < height; ++_y)
	      {
		for (size_t _x = 0; _x < width; ++_x)
		  {
		    size_t pix = (y + _y) * m_width + (x + _x);
		    Color old(pixels[pix]);
		    Color merged(color.r * a + old.r * (1 - a),
				 color.g * a + old.g * (1 - a),
				 color.b * a + old.b * (1 - a),
				 color.a + old.a * (1 - a));
		    pixels[pix] = merged.full;
		  }
	      }
	  }
      }
  }

  void LibLapin::display()
  {
    bunny_loop(m_win, 60, nullptr);
  }

  void LibLapin::clear()
  {
    bunny_clear(&m_win->buffer, BLACK);
  }

  KeyboardKey LibLapin::getKeyboardKey(t_bunny_keysym code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibLapin::getMouseKey(t_bunny_mouse_button code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      return (m_mouse_keys[code]);
    return (MouseKey::M_NONE);
  }

  MousePos LibLapin::getMousePos()
  {
    MousePos pos;

    // TODO
    pos.x = 0;
    pos.y = 0;
    return (pos);
  }

  // LibLapin Handlers
  t_bunny_response LibLapin::_mainLoop(void *data)
  {
    static_cast<void>(data);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_eventLoop(void *data)
  {
    static_cast<void>(data);
    return (SWITCH_CONTEXT);
  }

  t_bunny_response LibLapin::_keyHandler(t_bunny_event_state state, t_bunny_keysym key,
					 void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    assert(e);
    e->type = EventType::ET_KEYBOARD;
    e->action = (state == GO_UP) ? ActionType::AT_RELEASED : ActionType::AT_PRESSED;
    e->kb_key = LibLapin::getKeyboardKey(key);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_clickHandler(t_bunny_event_state state, t_bunny_mouse_button but,
					   void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    assert(e);
    e->type = EventType::ET_MOUSE;
    e->action = (state == GO_UP) ? ActionType::AT_RELEASED : ActionType::AT_PRESSED;
    e->m_key = LibLapin::getMouseKey(but);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_moveHandler(t_bunny_position const*relative, void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    // TODO
    assert(e);
    static_cast<void>(relative);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_wheelHandler(int wheelId, int delta, void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    // TODO
    assert(e);
    static_cast<void>(wheelId);
    static_cast<void>(delta);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_lostFocusHandler(t_bunny_window const *win, void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    // TODO
    assert(e);
    static_cast<void>(win);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_gotFocusHandler(t_bunny_window const *win, void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    // TODO
    assert(e);
    static_cast<void>(win);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_resizeHandler(t_bunny_window const *win, t_bunny_position const *size, void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    // TODO
    assert(e);
    static_cast<void>(win);
    static_cast<void>(size);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_closeHandler(t_bunny_window const *win, void *dat)
  {
    Event	*e = static_cast<Event *>(dat);

    assert(e);
    static_cast<void>(win);
    e->type = EventType::ET_QUIT;
    return (EXIT_ON_SUCCESS);
  }
}
