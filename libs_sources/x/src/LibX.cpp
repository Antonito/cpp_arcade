#include <exception>
#include <iostream>
#include <cstring>
#include <sys/select.h>
#include "LibX.hpp"
#include <X11/Xutil.h> // Must be after LibX.hpp
#include <X11/Xlibint.h>
#include "WindowError.hpp"
#include "AllocationError.hpp"
#include "CapabilityError.hpp"

namespace arcade
{
  LibX::LibX(size_t width, size_t height)
      : m_mapData(nullptr), m_map(nullptr), m_guiData(nullptr), m_gui(nullptr),
        m_mapWidth(0), m_mapHeight(0), m_canDraw(true)
  {
    m_width = width;
    m_height = height;
    m_disp = XOpenDisplay(nullptr);
    if (!m_disp)
      {
	throw WindowError("Cannot open X Display");
      }
    // Map keyboard and mouse
    setKeyMapping();
    m_vis = DefaultVisual(m_disp, 0);
    if (m_vis->c_class != TrueColor)
      {
	throw CapabilityError("TrueColor not supported");
      }

    // Set up a window
    m_screen = DefaultScreen(m_disp);
    m_gc = DefaultGC(m_disp, m_screen);
    m_root = RootWindow(m_disp, m_screen);
    m_whitePixel = WhitePixel(m_disp, m_screen);
    m_blackPixel = BlackPixel(m_disp, m_screen);
    m_win = XCreateSimpleWindow(m_disp, m_root, 10, 10, width, height, 2,
                                m_blackPixel, m_whitePixel);
    m_del = XInternAtom(m_disp, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(m_disp, m_win, &m_del, 1);
    XSelectInput(m_disp, m_win, LibX::eventMask);
    XMapWindow(m_disp, m_win);
    XRaiseWindow(m_disp, m_win);
    m_fd = ConnectionNumber(m_disp);

    // Create an image
    m_guiData = static_cast<uint32_t *>(
        Xmalloc(m_width * m_height * sizeof(uint32_t)));
    std::memset(m_guiData, 0, m_width * m_height * sizeof(Color));
    m_gui = XCreateImage(
        m_disp, m_vis, DefaultDepth(m_disp, DefaultScreen(m_disp)), ZPixmap, 0,
        reinterpret_cast<char *>(m_guiData), m_width, m_height, 32, 0);
    if (!m_gui)
      {
	throw AllocationError("Cannot create XImage");
      }
    XFlush(m_disp);
  }

  LibX::~LibX()
  {
    XUnmapWindow(m_disp, m_win);
    if (m_map)
      XDestroyImage(m_map);
    XDestroyImage(m_gui);
    XDestroyWindow(m_disp, m_win);
    XCloseDisplay(m_disp);
  }

  bool LibX::pollEvent(Event &e)
  {
    struct timeval tv;
    fd_set         readfds;
    int            ret;

    FD_ZERO(&readfds);
    FD_SET(m_fd, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 1;
    ret = select(m_fd + 1, &readfds, nullptr, nullptr, &tv);
    if (ret == -1)
      {
	throw std::runtime_error("Cannot read LibX events");
      }
    else if (ret)
      {
	// Handle events here
	if (XPending(m_disp))
	  {
	    XEvent ev;

	    XNextEvent(m_disp, &ev);
	    m_canDraw = false;
	    switch (ev.type)
	      {
	      case Expose:
		std::cout << "Expose" << std::endl;
		m_canDraw = true;
		return (false);
		break;
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
		m_canDraw = false;
		e.type = EventType::ET_MOUSE;
		e.action = ActionType::AT_PRESSED;
		// TODO
		break;
	      case ButtonRelease:
		m_canDraw = false;
		e.type = EventType::ET_MOUSE;
		e.action = ActionType::AT_RELEASED;
		// TODO
		break;
	      case MotionNotify:
		m_canDraw = false;
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
		e.action = ActionType::AT_RELEASED;
		e.kb_key = LibX::getKeyboardKey(ev.xkey.keycode);
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

  void LibX::loadSounds(
      std::vector<std::pair<std::string, SoundType>> const &sounds)
  {
    static_cast<void>(sounds);
  }

  void LibX::soundControl(Sound const &sound)
  {
    static_cast<void>(sound);
  }

  void LibX::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));
    static_cast<void>(s);
  }

  void LibX::updateMap(IMap const &map)
  {
    if (!m_mapData || m_mapWidth != map.getWidth() ||
        m_mapHeight != map.getHeight())
      {
	if (m_map)
	  XDestroyImage(m_map);
	m_map = nullptr;
	m_mapData = nullptr;
	m_mapWidth = map.getWidth();
	m_mapHeight = map.getHeight();
	if (!m_mapWidth || !m_mapHeight)
	  return;
	m_mapData = static_cast<uint32_t *>(Xmalloc(m_mapWidth * m_tileSize *
	                                            m_mapHeight * m_tileSize *
	                                            sizeof(uint32_t)));
	m_map = XCreateImage(
	    m_disp, m_vis, DefaultDepth(m_disp, DefaultScreen(m_disp)),
	    ZPixmap, 0, reinterpret_cast<char *>(m_mapData),
	    m_mapWidth * m_tileSize, m_mapHeight * m_tileSize, 32, 0);
	if (!m_map)
	  {
	    throw AllocationError("Cannot create XImage map");
	  }
      }

    Color *pixels = reinterpret_cast<Color *>(m_mapData);
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
				double a(color.a / 255.0);
				Color  old(pixels[Y * mapWidth + X]);
				Color  merged(color.r * a + old.r * (1 - a),
				             color.g * a + old.g * (1 - a),
				             color.b * a + old.b * (1 - a),
				             color.a + old.a * (1 - a));
				putPixel(X, Y, merged, m_map);
			      }
			  }
		      }
		  }
	      }
	  }
      }
  }

  void LibX::updateGUI(IGUI &gui)
  {
    Color *pixels = reinterpret_cast<Color *>(m_guiData);
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
		    Color old(pixels[(y + _y) * m_width + x + _x]);
		    Color merged(color.r * a + old.r * (1 - a),
		                 color.g * a + old.g * (1 - a),
		                 color.b * a + old.b * (1 - a),
		                 color.a + old.a * (1 - a));
		    putPixel(x + _x, y + _y, merged, m_gui);
		  }
	      }
	  }
      }
  }

  void LibX::display()
  {
    if (m_canDraw)
      {
	if (m_map)
	  XPutImage(m_disp, m_win, m_gc, m_map, 0, 0, 0, 0, m_width, m_height);
	XPutImage(m_disp, m_win, m_gc, m_gui, 0, 0, 0, 0, m_width, m_height);
	XFlush(m_disp);
	m_canDraw = true;
      }
  }

  void LibX::clear()
  {
    if (m_canDraw)
      XClearWindow(m_disp, m_win);
  }

  void LibX::drawPixel(size_t x, size_t y, Color color)
  {
    XColor col;

    col.pixel = ((color.b & 0xff) | ((color.g & 0xff) << 8) |
                 ((color.r & 0xff) << 16));
    XSetForeground(m_disp, m_gc, col.pixel);
    XDrawPoint(m_disp, m_win, m_gc, x, y);
  }

  void LibX::putPixel(size_t x, size_t y, Color color, XImage *img)
  {
    XColor col;

    col.pixel = ((color.b & 0xff) | ((color.g & 0xff) << 8) |
                 ((color.r & 0xff) << 16));
    XPutPixel(img, x, y, col.pixel);
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
