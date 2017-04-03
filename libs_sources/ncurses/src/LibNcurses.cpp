#include <exception>
#include <iostream>
#include <curses.h>
#include <cstdio>
#include <sys/poll.h>
#include "LibNcurses.hpp"

namespace arcade
{
  LibNcurses::LibNcurses(size_t width, size_t height) : m_win(nullptr), m_map(nullptr), m_gui(nullptr),
							m_mapWidth(0), m_mapHeight(0)
  {
    initscr();
    clear();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    nodelay(stdscr, true);
    scrollok(stdscr, TRUE);
    m_win = newwin(height, width, 0, 0);
    m_height = height;
    m_width = width;
    if (!m_win)
      {
	std::cerr << "Cannot create ncurses window" << std::endl;
	throw std::exception(); // TODO: Exception
      }
  }

  LibNcurses::~LibNcurses()
  {
    delwin(m_win);
    endwin();
  }

  bool LibNcurses::pollEvent(Event &e)
  {
    struct pollfd	fds;
    int			fd = fileno(stdin);

    fds.fd = fd;
    fds.events = POLLIN;
    switch(poll(&fds, 1, 0))
      {
      case -1:
	refresh();
	break;
      default:
	if (fds.revents & POLLIN)
	  {
	    int key;
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_PRESSED;
	    key = getch();
	    if (key == 27)
	      {
		poll(&fds, 1, 1);
		if (fds.revents & POLLIN)
		  {
		    getch();
		    e.kb_key = KeyboardKey::KB_NONE;
		  }
		else
		  e.kb_key = KeyboardKey::KB_ESCAPE;
	      }
	    else
	      e.kb_key = LibNcurses::getKeyboardKey(key);
	    return (true);
	  }
      }
    return (false);
  }

  bool LibNcurses::doesSupportSound() const
  {
    return (false);
  }

  void LibNcurses::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds)
  {
    static_cast<void>(sounds);
  }

  void LibNcurses::soundControl(Sound const &sound)
  {
    static_cast<void>(sound);
  }

  void LibNcurses::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
    std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));
    (void)s;
  }

  void LibNcurses::updateMap(IMap const & map)
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
		    if (color.rgba[3] != 0) // TODO: color.a ?
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

  void LibNcurses::updateGUI(IGUI & gui)
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

  void LibNcurses::display()
  {
    refresh();
  }

  void LibNcurses::clear()
  {
    // TODO
  }

  KeyboardKey LibNcurses::getKeyboardKey(int code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibNcurses::getMouseKey(int code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      return (m_mouse_keys[code]);
    return (MouseKey::M_NONE);
  }

  MousePos LibNcurses::getMousePos()
  {
    MousePos pos;
    // TODO
    pos.x = 0;
    pos.y = 0;
    return (pos);
  }
}
