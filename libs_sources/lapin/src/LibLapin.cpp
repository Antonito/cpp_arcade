#include <cassert>
#include <exception>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "LibLapin.hpp"
#include "WindowError.hpp"
#include "AllocationError.hpp"

namespace arcade
{
  LibLapin::LibLapin(size_t width, size_t height)
      : m_width(width), m_height(height), m_gui(nullptr), m_map(nullptr),
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
	throw WindowError("Cannot create LibLapin Window");
      }
    m_render = bunny_new_pixelarray(width, height);
    m_gui = bunny_new_pixelarray(width, height);
    if (!m_render || !m_gui)
      {
	throw AllocationError("Cannot create pixelarray");
      }
    bunny_set_loop_main_function(&LibLapin::_mainLoop);
    bunny_loop(m_win, 60, this);
  }

  LibLapin::~LibLapin()
  {
    for (t_bunny_sound *s : m_sound)
      {
	bunny_delete_sound(s);
      }
    bunny_stop(m_win);
    bunny_free(m_map);
    bunny_free(m_gui);
  }

  bool LibLapin::pollEvent(Event &e)
  {
    bool ret = false;

    bunny_set_key_response(&LibLapin::_keyHandler);
    /*bunny_set_click_response(&LibLapin::_clickHandler);
    bunny_set_move_response(&LibLapin::_moveHandler);
    bunny_set_wheel_response(&LibLapin::_wheelHandler);
    bunny_set_lost_focus_response(&LibLapin::_lostFocusHandler);
    bunny_set_get_focus_response(&LibLapin::_gotFocusHandler);
    bunny_set_resize_response(&LibLapin::_resizeHandler);
    bunny_set_close_response(&LibLapin::_closeHandler);*/
    bunny_set_loop_main_function(&LibLapin::_eventLoop);
    if (bunny_loop(m_win, 60, &e) == EXIT_ON_SUCCESS)
      {
	ret = true;
      }
    bunny_set_loop_main_function(&LibLapin::_mainLoop);
    bunny_set_key_response(nullptr);
    /*bunny_set_click_response(nullptr);
    bunny_set_move_response(nullptr);
    bunny_set_wheel_response(nullptr);
    bunny_set_lost_focus_response(nullptr);
    bunny_set_get_focus_response(nullptr);
    bunny_set_resize_response(nullptr);
    bunny_set_close_response(nullptr);*/
    return (ret);
  }

  bool LibLapin::doesSupportSound() const
  {
    return (true);
  }

  void LibLapin::loadSounds(
      std::vector<std::pair<std::string, SoundType>> const &sounds)
  {
    for (std::pair<std::string, SoundType> const &p : sounds)
      {
	if (p.second == SoundType::MUSIC)
	  {
	    t_bunny_music *cur = bunny_load_music(p.first.c_str());

	    if (!cur)
	      {
		std::cerr << "Cannot load music : " << p.first << std::endl;
	      }
	    else
	      {
		m_music.push_back(cur);
		m_sound.push_back(&cur->sound);
	      }
	  }
	else
	  {
	    t_bunny_effect *cur = bunny_load_effect(p.first.c_str());

	    if (!cur)
	      {
		std::cerr << "Cannot load sound : " << p.first << std::endl;
	      }
	    else
	      {
		m_effect.push_back(cur);
		m_sound.push_back(&cur->sound);
	      }
	  }
      }
  }

  void LibLapin::soundControl(Sound const &sound)
  {
    t_bunny_sound *cur;

    cur = m_sound[sound.id];
    switch (sound.mode)
      {
      case SoundAction::UNIQUE:
	bunny_sound_loop(cur, false);
	break;
      case SoundAction::REPEAT:
	bunny_sound_loop(cur, true);
	break;
      case SoundAction::VOLUME:
	bunny_sound_volume(cur, static_cast<double>(sound.volume));
	break;
      case SoundAction::PLAY:
      case SoundAction::RESUME:
	bunny_sound_play(cur);
	break;
      case SoundAction::PAUSE:
	break;
      case SoundAction::STOP:
	bunny_sound_stop(cur);
	break;
      default:
	break;
      }
  }

  void LibLapin::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));
  }

  void LibLapin::updateMap(IMap const &map)
  {
    if (map.getWidth() == 0 || map.getHeight() == 0)
      return;
    if (!m_map || m_mapWidth != map.getWidth() ||
        m_mapHeight != map.getHeight())
      {
	bunny_free(m_map);
	m_map = nullptr;
	m_mapWidth = map.getWidth();
	m_mapHeight = map.getHeight();
	if (!m_mapWidth || !m_mapHeight)
	  return;
	m_map = bunny_new_pixelarray(m_mapWidth * m_tileSize,
	                             m_mapHeight * m_tileSize);
	if (!m_map)
	  {
	    std::cerr << "Cannot create LibLapin pixelarray"
#if defined(DEBUG)
	              << " [" << m_mapWidth * m_tileSize << "x"
	              << m_mapHeight * m_tileSize << "]"
#endif
	              << std::endl;
	    throw AllocationError("Cannot create LibLapin pixelarray");
	  }
      }

    Color *pixels = reinterpret_cast<Color *>(m_map->pixels);
    for (size_t l = 0; l < map.getLayerNb(); ++l)
      {
	for (size_t y = 0; y < m_mapHeight; ++y)
	  {
	    for (size_t x = 0; x < m_mapWidth; ++x)
	      {
		ITile const &tile = map.at(l, x, y);
		if (tile.getSpriteId() != 0 && false)
		  {
		  }
		else
		  {
		    Color  color = tile.getColor();
		    double a(color.a / 255.0);
		    if (color.a != 0)
		      {
			for (size_t _y = 0; _y < m_tileSize; ++_y)
			  {
			    for (size_t _x = 0; _x < m_tileSize; ++_x)
			      {
				size_t X = x * m_tileSize + _x;
				size_t Y = y * m_tileSize + _y;
				size_t pix = Y * (m_mapWidth * m_tileSize) + X;
				Color  old(pixels[pix]);
				Color  merged(color.r * a + old.r * (1 - a),
				             color.g * a + old.g * (1 - a),
				             color.b * a + old.b * (1 - a),
				             color.a + old.a * (1 - a));
				pixels[pix] = merged.full;
			      }
			  }
		      }
		  }
	      }
	  }
      }
  }

  void LibLapin::updateGUI(IGUI &gui)
  {
    Color *pixels = reinterpret_cast<Color *>(m_gui->pixels);
    std::memset(pixels, 0, m_width * m_height * sizeof(Color));
    for (size_t i = 0; i < gui.size(); ++i)
      {
	IComponent const &comp = gui.at(i);
	size_t            x = comp.getX() * m_width;
	size_t            y = comp.getY() * m_height;
	size_t            width = comp.getWidth() * m_width;
	size_t            height = comp.getHeight() * m_height;
	Color             color = comp.getBackgroundColor();
	double            a(color.a / 255.0);
	if (color.a != 0)
	  {
	    for (size_t _y = 0; _y < height; ++_y)
	      {
		for (size_t _x = 0; _x < width; ++_x)
		  {
		    size_t pix = (y + _y) * m_width + (x + _x);
		    Color  old(pixels[pix]);
		    Color  merged(color.r * a + old.r * (1 - a),
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
    bunny_loop(m_win, 60, this);
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

    pos.x = 0;
    pos.y = 0;
    return (pos);
  }

  t_bunny_window *LibLapin::getWin() const
  {
    return (m_win);
  }

  t_bunny_pixelarray *LibLapin::getMap() const
  {
    return (m_map);
  }

  t_bunny_pixelarray *LibLapin::getGui() const
  {
    return (m_gui);
  }

  t_bunny_pixelarray *LibLapin::getRender() const
  {
    return (m_render);
  }

  // LibLapin Handlers
  t_bunny_response LibLapin::_mainLoop(void *data)
  {
    LibLapin *          lib = static_cast<LibLapin *>(data);
    t_bunny_pixelarray *map = nullptr;
    t_bunny_pixelarray *gui = lib->getGui();
    t_bunny_pixelarray *render = lib->getRender();
    t_bunny_window *    win = lib->getWin();

    if (map)
      _blit(render, map);
    if (gui)
      _blit(render, gui);
    bunny_blit(&win->buffer, &render->clipable, NULL);
    bunny_display(win);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_eventLoop(void *)
  {
    return (EXIT_ON_ERROR);
  }

  t_bunny_response LibLapin::_keyHandler(t_bunny_event_state state,
                                         t_bunny_keysym key, void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    e->type = EventType::ET_KEYBOARD;
    e->action =
        (state == GO_UP) ? ActionType::AT_RELEASED : ActionType::AT_PRESSED;
    e->kb_key = LibLapin::getKeyboardKey(key);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_clickHandler(t_bunny_event_state  state,
                                           t_bunny_mouse_button but, void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    e->type = EventType::ET_MOUSE;
    e->action =
        (state == GO_UP) ? ActionType::AT_RELEASED : ActionType::AT_PRESSED;
    e->m_key = LibLapin::getMouseKey(but);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_moveHandler(t_bunny_position const *, void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_wheelHandler(int, int, void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_lostFocusHandler(t_bunny_window const *,
                                               void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_gotFocusHandler(t_bunny_window const *,
                                              void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_resizeHandler(t_bunny_window const *,
                                            t_bunny_position const *,
                                            void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    static_cast<void>(e);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response LibLapin::_closeHandler(t_bunny_window const *, void *dat)
  {
    Event *e = static_cast<Event *>(dat);

    assert(e);
    e->type = EventType::ET_QUIT;
    return (EXIT_ON_SUCCESS);
  }

  void LibLapin::_blit(t_bunny_pixelarray *dest, t_bunny_pixelarray const *src)
  {
    size_t width =
        std::min(dest->clipable.clip_width, src->clipable.clip_width);
    size_t height =
        std::min(dest->clipable.clip_height, src->clipable.clip_height);
    Color *dest_pixels = static_cast<Color *>(dest->pixels);
    Color *src_pixels = static_cast<Color *>(src->pixels);

    for (size_t y = 0; y < height; ++y)
      {
	for (size_t x = 0; x < width; ++x)
	  {
	    Color  old = dest_pixels[y * dest->clipable.clip_width + x];
	    Color  color = src_pixels[y * src->clipable.clip_width + x];
	    double a = color.a / 255.0;

	    Color merged(
	        color.r * a + old.r * (1 - a), color.g * a + old.g * (1 - a),
	        color.b * a + old.b * (1 - a), color.a + old.a * (1 - a));
	    dest_pixels[y * dest->clipable.clip_width + x] = merged.full;
	  }
      }
  }
}
