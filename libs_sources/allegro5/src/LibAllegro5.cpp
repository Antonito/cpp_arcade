#include <exception>
#include <iostream>
#include <cstring>
#include "LibAllegro5.hpp"
#include "ITile.hpp"
#include "IMap.hpp"

namespace arcade
{
  LibAllegro5::LibAllegro5(size_t width, size_t height) : m_width(width), m_height(height), m_mapWidth(0), m_mapHeight(0), m_gui(nullptr), m_map(nullptr)
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
    al_set_window_title(m_win, "Arcade allegro");
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
    int flags = al_get_new_bitmap_flags();
    al_set_new_bitmap_flags(flags | ALLEGRO_MEMORY_BITMAP);
    m_gui = al_create_bitmap(m_width, m_height);
    if (!m_gui)
    {
      std::cerr << "Cannot get bitmap Allegro5" << std::endl;
      throw std::exception(); // TODO
    }
    al_set_new_bitmap_flags(flags);
  }

  LibAllegro5::~LibAllegro5()
  {
    al_destroy_bitmap(m_gui);
    al_destroy_timer(m_timer);
    al_destroy_display(m_win);
    al_destroy_event_queue(m_event);
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
        e.m_key = LibAllegro5::getMouseKey(events.mouse.button);
        break;
      case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        e.type = EventType::ET_MOUSE;
        e.action = ActionType::AT_RELEASED;
        e.m_key = LibAllegro5::getMouseKey(events.mouse.button);
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
    if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
    {
      m_mapWidth = map.getWidth();
      m_mapHeight = map.getHeight();
      int flags = al_get_new_bitmap_flags();
      al_set_new_bitmap_flags(flags | ALLEGRO_MEMORY_BITMAP);
      m_map = al_create_bitmap(m_mapWidth * m_tileSize, m_mapHeight * m_tileSize);
      if (!m_map)
      {
        std::cerr << "Cannot get bitmap Allegro5" << std::endl;
        throw std::exception(); // TODO
      }
      al_set_new_bitmap_flags(flags);
    }
    size_t mapWidth = m_mapWidth * m_tileSize;

    if (al_lock_bitmap(m_map, al_get_bitmap_format(m_map), ALLEGRO_LOCK_READWRITE))
    {
      al_set_target_bitmap(m_map);
      for (size_t l = 0; l < map.getLayerNb(); ++l)
      {
        for (size_t y = 0; y < map.getHeight(); ++y)
        {
          for (size_t x = 0; x < map.getWidth(); ++x)
          {
            ITile const &tile = map.at(l, x, y);
            Color color = tile.getColor();
            double a(color.a / 255.0);
            if (color.a != 0)
            {
              for (size_t _y = 0; _y < m_tileSize; ++_y)
              {
                for (size_t _x = 0; _x < m_tileSize; ++_x)
                {
                  size_t X = x * m_tileSize + _x;
                  size_t Y = y * m_tileSize + _y;

                  Color old;
                  ALLEGRO_COLOR cur = al_get_pixel(m_map, X, Y);
                  al_unmap_rgba(cur, &old.r, &old.g, &old.b, &old.a);
                  Color merged(color.r * a + old.r * (1 - a),
                    color.g * a + old.g * (1 - a),
                    color.b * a + old.b * (1 - a),
                    color.a + old.a * (1 - a));
                  al_put_pixel(X, Y, al_map_rgba(merged.r, merged.g, merged.b, merged.a));
                }
              }
            }
          }
        }
      }
      al_unlock_bitmap(m_map);
      al_set_target_backbuffer(m_win);
    }
  }

  void LibAllegro5::updateGUI(IGUI & gui)
  {
    return;
    if (al_lock_bitmap(m_gui, al_get_bitmap_format(m_gui), ALLEGRO_LOCK_READWRITE))
    {
      al_set_target_bitmap(m_gui);
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
              Color old;
              std::cout << m_gui << std::endl;
              std::cout << x << std::endl;
              std::cout << _x << std::endl;
              std::cout << y << std::endl;
              std::cout << _y << std::endl;
              ALLEGRO_COLOR cur = al_get_pixel(m_gui, x + _x, y + _y);
              al_unmap_rgba(cur, &old.r, &old.g, &old.b, &old.a);
              Color merged(color.r * a + old.r * (1 - a),
                color.g * a + old.g * (1 - a),
                color.b * a + old.b * (1 - a),
                color.a + old.a * (1 - a));
              al_put_pixel(x + _x, y + _y, al_map_rgba(merged.r, merged.g, merged.b, merged.a));
              exit(1);
            }
          }
        }
      }
      al_unlock_bitmap(m_gui);
      al_set_target_backbuffer(m_win);
    }
  }

  void LibAllegro5::display()
  {
    al_draw_bitmap(m_map, 0, 0, 0);
    //al_draw_bitmap(m_gui, 0, 0, 0);
    al_flip_display();
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
