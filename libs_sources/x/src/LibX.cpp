#include <exception>
#include <iostream>
#include <sys/select.h>
#include "LibX.hpp"

namespace arcade
{
  LibX::LibX(size_t width, size_t height) : m_mapWidth(0), m_mapHeight(0)
  {
    m_width = width;
    m_height = height;
    m_disp = XOpenDisplay(nullptr);
    if (!m_disp)
      {
	std::cerr << "Cannot open X Display" << std::endl;
	throw std::exception(); // TODO
      }
    // Map keyboard and mouse
    setKeyMapping();

    // Set up a window
    m_screen = DefaultScreen(m_disp);
    m_gc = DefaultGC(m_disp, m_screen);
    m_root = RootWindow(m_disp, m_screen);
    m_whitePixel = WhitePixel(m_disp, m_screen);
    m_blackPixel = BlackPixel(m_disp, m_screen);
    m_win = XCreateSimpleWindow(m_disp, m_root, 10, 10, width, height, 2, m_blackPixel, m_whitePixel);
    m_del = XInternAtom(m_disp, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(m_disp , m_win, &m_del, 1);
    XSelectInput(m_disp, m_win, LibX::eventMask);
    XMapWindow(m_disp, m_win);
    XRaiseWindow(m_disp, m_win);
    m_fd = ConnectionNumber(m_disp);
    XFlush(m_disp);
  }

  LibX::~LibX()
  {
    // TODO : implement
    XUnmapWindow(m_disp, m_win);
    XDestroyWindow(m_disp, m_win);
    XCloseDisplay(m_disp);
  }

  bool LibX::pollEvent(Event &e)
  {
    // TODO
    struct timeval	tv;
    fd_set		readfds;
    int			ret;

    FD_ZERO(&readfds);
    FD_SET(m_fd, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 1;
    ret = select(m_fd + 1, &readfds, nullptr, nullptr, &tv);
    if (ret == -1)
      {
	std::cerr << "Cannot read LibX events" << std::endl;
	throw std::exception(); // TODO
      }
    else if (ret)
      {
	// Handle events here
	if (XPending(m_disp))
	  {
	    XEvent ev;

	    XNextEvent(m_disp, &ev);
	    switch (ev.type)
	      {
	      case ClientMessage:
		e.type = EventType::ET_QUIT;
		break;
	      case ResizeRequest:
		// Ask for a resize
		e.type = EventType::ET_NONE;
		e.action = ActionType::AT_NONE;
		break;

		// Mouse
	      case ButtonPress:
		e.type = EventType::ET_MOUSE;
		e.action = ActionType::AT_PRESSED;
		// TODO
		break;
	      case ButtonRelease:
		e.type = EventType::ET_MOUSE;
		e.action = ActionType::AT_RELEASED;
		// TODO
		break;
	      case MotionNotify:
		e.type = EventType::ET_MOUSE;
		e.action = ActionType::AT_MOVED;
		// TODO
		break;

		// Keyboard
	      case KeyPress:
		e.type = EventType::ET_KEYBOARD;
		e.action = ActionType::AT_PRESSED;
		e.kb_key = LibX::getKeyboardKey(ev.xkey.keycode);
		break;
	      case KeyRelease:
		e.type = EventType::ET_KEYBOARD;
		e.action = ActionType::AT_PRESSED;
		// TODO
		std::cout << "A key was released" << std::endl;
		break;
	      default:
		break;
	      }
	  }
	return (true);
      }
    return (false);
  }

  bool LibX::doesSupportSound() const
  {
    return (false);
  }

  void LibX::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds)
  {
    static_cast<void>(sounds);
  }

  void LibX::soundControl(Sound const &sound)
  {
    static_cast<void>(sound);
  }

  void LibX::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
    std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));
    static_cast<void>(s);
  }

  void LibX::updateMap(IMap const & map)
  {
    //if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
    //{
    // TODO
    //}

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
				double a(color.a / 255.0);
				// TODO
			      }
			  }
		      }
		  }
	      }
	  }
      }
  }

  void LibX::updateGUI(IGUI & gui)
  {
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
		    // TODO
		  }
	      }
	  }
      }
  }

  void LibX::display()
  {
    // TODO
  }

  void LibX::clear()
  {
    // TODO
  }

  KeyboardKey LibX::getKeyboardKey(int code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibX::getMouseKey(int code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      return (m_mouse_keys[code]);
    return (MouseKey::M_NONE);
  }

  MousePos LibX::getMousePos()
  {
    MousePos pos;

    // TODO : Check correctness
    pos.x = 0;
    pos.y = 0;
    return (pos);
  }
}
