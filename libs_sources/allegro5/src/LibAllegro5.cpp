#include <exception>
#include <iostream>
#include <cstring>
#include "LibAllegro5.hpp"

namespace arcade
{
  LibAllegro5::LibAllegro5(size_t width, size_t height) : m_width(width), m_height(height), m_mapWidth(0), m_mapHeight(0)
  {
    if (!al_init())
      {
	std::cerr << "Cannot initialize Lib Allegro5" << std::endl;
	throw std::exception(); // TODO
      }
    m_win = al_create_display(width, height);
    if (!m_win)
      {
	std::cerr << "Cannot create Allegro5 window" << std::endl;
	throw std::exception(); // TODO
      }
    al_set_window_title(m_win, "Arcade");
    if (!al_install_keyboard())
      {
	std::cerr << "Cannot install keyboard handler Allegro5" << std::endl;
	throw std::exception(); // TODO
      }
    if (!al_install_mouse())
      {
	std::cerr << "Cannot install mouse handler Allegro5" << std::endl;
	throw std::exception(); // TODO
      }
    m_timer = al_create_timer(1.0 / 60);
    if (!m_timer)
      {
	std::cerr << "Cannot create timer Allegro5" << std::endl;
	throw std::exception(); // TODO
      }
    m_event = al_create_event_queue();
    if (!m_event)
      {
	std::cerr << "Cannot get event queue Allegro5" << std::endl;
	throw std::exception(); // TODO
      }
    al_register_event_source(m_event, al_get_timer_event_source(m_timer));
    al_register_event_source(m_event, al_get_keyboard_event_source());
    al_register_event_source(m_event, al_get_display_event_source(m_win));
  }

  LibAllegro5::~LibAllegro5()
  {
    al_destroy_timer(m_timer);
    al_destroy_event_queue(m_event);
    al_destroy_display(m_win);
  }

  bool LibAllegro5::pollEvent(Event & e)
  {
    ALLEGRO_EVENT events;

    if (al_get_next_event(m_event, &events))
      {
	switch (events.type)
	  {
	  case ALLEGRO_EVENT_TIMER:
	    break;
	  case ALLEGRO_EVENT_DISPLAY_RESIZE:
	    break;
	  case ALLEGRO_EVENT_DISPLAY_CLOSE:
	    e.type = EventType::ET_QUIT;
	    break;

	    // Mouse
	  case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_PRESSED;
	    e.m_key = LibAllegro5::getMouseKey(event.mouse.button);
	    break;
	  case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_RELEASED;
	    e.m_key = LibAllegro5::getMouseKey(event.mouse.button);
	    break;

	    // Keyboard
	  case ALLEGRO_EVENT_KEY_DOWN:
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_PRESSED;
	    e.kb_key = LibAllegro5::getKeyboardKey(events.keyboard.keycode);
	    break;
	  case ALLEGRO_EVENT_KEY_UP:
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_RELEASED;
	    e.kb_key = LibAllegro5::getKeyboardKey(events.keyboard.keycode);
	    break;
	  default:
	    break;
	  }
	return (true);
      }
    return (false);
  }

  bool LibAllegro5::doesSupportSound() const
  {
    return (false); // TODO
  }

  void LibAllegro5::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds)
  {
    // TODO
  }

  void LibAllegro5::soundControl(Sound const &sound)
  {
    // TODO
  }

  void LibAllegro5::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
    std::vector<std::unique_ptr<ISprite>> sp(std::move(sprites));
    (void)sp;
  }

  void LibAllegro5::updateMap(IMap const & map)
  {
    // if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
    //{
    // TODO
    //}
    size_t mapWidth = m_mapWidth * m_tileSize;

    for (size_t l = 0; l < map.getLayerNb(); ++l)
      {
	for (size_t y = 0; y < m_mapWidth; ++y)
	  {
	    for (size_t x = 0; x < m_mapHeight; ++x)
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
				size_t pix = Y * mapWidth + X;
				double a(color.a / 255.0);
				Color old(0);//pixels[pix]);
				Color merged(color.r * a + old.r * (1 - a),
					     color.g * a + old.g * (1 - a),
					     color.b * a + old.b * (1 - a),
					     color.a + old.a * (1 - a));
				// TODO
			      }
			  }
		      }
		  }
	      }
	  }
      }
  }

  void LibAllegro5::updateGUI(IGUI & gui)
  {
    // TODO
    for (size_t i = 0; i < gui.size(); ++i)
      {
	IComponent const &comp = gui.at(i);
	size_t x = comp.getX() * m_width;
	size_t y = comp.getY() * m_height;
	size_t width = comp.getWidth() * m_width;
	size_t height = comp.getHeight() * m_height;
	Color color = comp.getBackgroundColor();
	double a(color.a / 255.0);
	if (color.a != 0)
	  {
	    for (size_t _y = 0; _y < height; ++_y)
	      {
		for (size_t _x = 0; _x < width; ++_x)
		  {
		    size_t pix = (y + _y) * m_width + (x + _x);
		    Color old(0);//pixels[pix]);
		    Color merged(color.r * a + old.r * (1 - a),
				 color.g * a + old.g * (1 - a),
				 color.b * a + old.b * (1 - a),
				 color.a + old.a * (1 - a));
		    // TODO
		  }
	      }
	  }
      }
  }

  void LibAllegro5::display()
  {
    // TODO
  }
  void LibAllegro5::clear()
  {
    al_clear_to_color(al_map_rgb(0, 0, 0));
  }

  KeyboardKey LibAllegro5::getKeyboardKey(int code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibAllegro5::getMouseKey(int code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      return (m_mouse_keys[code]);
    return (MouseKey::M_NONE);
  }

  MouseKey LibAllegro5::getMouseWheel(int code)
  {
    // TODO : implement
    (void)code;
    return (MouseKey::M_NONE);
  }

  MousePos LibAllegro5::getMousePos()
  {
    MousePos	pos;

    pos.x = 0;
    pos.y = 0;
    return (pos);
  }
}
