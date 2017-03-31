#include <exception>
#include <iostream>
#include <curses.h>
#include <cstdio>
#include <sys/select.h>
#include <sys/time.h>
#include "LibNcurses.hpp"

namespace arcade
{
  LibNcurses::LibNcurses(size_t width, size_t height) : m_win(nullptr), m_map(nullptr), m_gui(nullptr),
							m_mapWidth(0), m_mapHeight(0)
  {
    // TODO : implement
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    scrollok(stdscr, TRUE);
    m_win = newwin(height, width, 0, 0);
    if (!m_win)
      {
	std::cerr << "Cannot create ncurses window" << std::endl;
	throw std::exception(); // TODO: Exception
      }
  }

  LibNcurses::~LibNcurses()
  {
    // TODO : implement
    delwin(m_win);
    endwin();
  }

  bool LibNcurses::pollEvent(Event &e)
  {
    fd_set	readfds;
    int		fd = fileno(stdin);
    int		ret;
    struct timeval	tv;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    ret = select(fd + 1, &readfds, NULL, NULL, &tv);
    if (ret == -1)
      {
	std::cerr << "select() failed" << std::endl;
	throw std::exception(); // TODO
      }
    else if (ret)
      {
	int key;
	e.type = EventType::ET_KEYBOARD;
	e.action = ActionType::AT_PRESSED;
	key = getch();
	if (key == 27)
	  {
	    fd_set	_readfds;
	    FD_ZERO(&_readfds);
	    FD_SET(fd, &_readfds);
	    tv.tv_sec = 0;
	    tv.tv_usec = 0;
	    ret = select(fd + 1, &_readfds, NULL, NULL, &tv);
	    if (ret)
	      {
		getch();
		getch();
		e.kb_key = KB_NONE;
		return (true);
	      }
	  }
	e.kb_key = LibNcurses::getKeyboardKey(key);
	return (true);
      }
    return (false);
  }

  bool LibNcurses::doesSupportSound() const
  {
    return (false);
  }

  void LibNcurses::loadSounds(std::vector<std::string> const & sounds)
  {
    static_cast<void>(sounds);
  }

  void LibNcurses::playSound(int soundId)
  {
    static_cast<void>(soundId);
  }

  void LibNcurses::updateMap(IMap const & map)
  {
    // TODO
    if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
      {
      }

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

  void LibNcurses::updateGUI(IGUI const & gui)
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
    // TODO
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
