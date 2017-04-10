#include <exception>
#include <iostream>
#include "Libcaca.hpp"
#include "WindowError.hpp"
#include "AllocationError.hpp"

namespace arcade
{
  Libcaca::Libcaca(size_t width, size_t height) : m_win(nullptr), m_canvas(nullptr), m_map(nullptr),
						  m_mapWidth(0), m_mapHeight(0)
  {
    m_canvas = caca_create_canvas(width, height);
    if (!m_canvas)
      {
	throw AllocationError("Cannot create LibCaca Canvas");
      }
    m_win = caca_create_display(m_canvas);
    if (!m_win)
      {
	throw WindowError("Cannot create LibCaca Window");
      }
    caca_set_display_title(m_win, "Arcade caca");
    m_width = caca_get_canvas_width(m_canvas);
    m_height = caca_get_canvas_height(m_canvas);
  }

  Libcaca::~Libcaca()
  {
    // TODO : implement
    if (m_map)
      caca_free_canvas(m_map);
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

  void Libcaca::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds)
  {
    static_cast<void>(sounds);
  }

  void Libcaca::soundControl(Sound const &sound)
  {
    static_cast<void>(sound);
  }

  void Libcaca::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
	  std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));

	  (void)s;
  }

  void Libcaca::updateMap(IMap const & map)
  {
    // TODO: Blit on canvas, how ??
    if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
    {
      if (m_map)
      {
        caca_free_canvas(m_map);
        m_map = nullptr;
      }
      m_mapWidth = map.getWidth();
      m_mapHeight = map.getHeight();
      if (!m_mapWidth || !m_mapHeight)
        return;
      m_map = caca_create_canvas(m_mapWidth * m_tileSize, m_mapHeight * m_tileSize);
      if (!m_map)
      {
        throw AllocationError("Cannot create LibCaca Canvas [map]");
      }
    }

    // Loop on every tile
    for (size_t l = 0; l < map.getLayerNb(); ++l)
    {
      for (size_t y = 0; y < m_mapHeight; ++y)
      {
        for (size_t x = 0; x < m_mapWidth; ++x)
        {
          ITile const &tile = map.at(l, x, y);

          // In case of sprite
          if (tile.getSpriteId() != 0 && false) // TODO: Enable
          {
          }
          // Display color
          else
          {
            Color color = tile.getColor();

            // Check if there is alpha
            if (color.a != 0)
            {
              double a(color.a / 255.0);
              uint32_t attr = caca_get_attr(m_canvas, x, y);
              uint8_t old[sizeof(uint64_t)];
              caca_attr_to_argb64(attr, old);
              Color bg(color.r * a + old[1] * (1 - a),
                color.g * a + old[2] * (1 - a),
                color.b * a + old[3] * (1 - a),
                color.a + old[0] * (1 - a));
              uint16_t _bg = convert32bitsColorTo16Bits(bg);
              caca_set_color_argb(m_canvas, 0xffff, _bg);
              caca_printf(m_canvas, x, y, " ");
            }
          }
        }
      }
    }
  }

  void Libcaca::updateGUI(IGUI & gui)
  {
    return;
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
		    uint32_t attr = caca_get_attr(m_canvas, x + _x, y + _y);
		    uint8_t old[sizeof(uint64_t)];
		    caca_attr_to_argb64(attr, old);
		    Color bg(color.r * a + old[1] * (1 - a),
			     color.g * a + old[2] * (1 - a),
			     color.b * a + old[3] * (1 - a),
			     color.a + old[0] * (1 - a));
		    uint16_t _bg = convert32bitsColorTo16Bits(bg);
		    caca_set_color_argb(m_canvas, 0xffff, _bg);
		    caca_printf(m_canvas, x + _x, y + _y, "  ");
		  }
	      }
	  }
      }
  }

  void Libcaca::display()
  {
    caca_refresh_display(m_win);
  }

  void Libcaca::clear()
  {
    caca_set_color_argb(m_canvas, 0xffff, 0);
    if (m_map)
      caca_clear_canvas(m_map);
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

  uint16_t Libcaca::convert32bitsColorTo16Bits(Color color) const
  {
    uint8_t a = color.a >> 4;
    uint8_t r = color.r >> 4;
    uint8_t g = color.g >> 4;
    uint8_t b = color.b >> 4;

    return ((a << 12) | (b << 8) | (g << 4) | (r));
	/*uint8_t a = color.a >> 3;
	uint8_t r = color.r >> 3;
	uint8_t g = color.g >> 3;
	uint8_t b = color.b >> 3;

	return ((a << 15) | (b << 10) | (g << 5) | (r));*/
    // TODO: Clean
  }
}
