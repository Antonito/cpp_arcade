#include <exception>
#include <curses.h>
#include <cstdio>
#include <sys/poll.h>
#include "LibNcurses.hpp"
#include "WindowError.hpp"

namespace arcade
{
  LibNcurses::LibNcurses(size_t width, size_t height)
      : m_win(nullptr), m_map(nullptr), m_gui(nullptr), m_mapWidth(0),
        m_mapHeight(0)
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
	throw WindowError("Cannot create Ncurses window");
      }
    if (has_colors())
      {
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_CYAN);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
      }
  }

  LibNcurses::~LibNcurses()
  {
    delwin(m_win);
    endwin();
  }

  bool LibNcurses::pollEvent(Event &e)
  {
    struct pollfd fds;
    int           fd = fileno(stdin);

    fds.fd = fd;
    fds.events = POLLIN;
    switch (poll(&fds, 1, 0))
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

  void LibNcurses::loadSounds(
      std::vector<std::pair<std::string, SoundType>> const &sounds)
  {
    static_cast<void>(sounds);
  }

  void LibNcurses::soundControl(Sound const &sound)
  {
    static_cast<void>(sound);
  }

  void LibNcurses::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));

    for (std::unique_ptr<ISprite> const &sp : s)
      {
	m_sprites.emplace_back();
	for (size_t i = 0; i < sp->spritesCount(); ++i)
	  {
	    m_sprites.back() += sp->getAscii(i);
	  }
      }
  }

  void LibNcurses::updateMap(IMap const &map)
  {
    int w;
    int h;

    getmaxyx(stdscr, h, w);

    int posX = (w - map.getWidth()) / 2;
    int posY = (h - map.getHeight()) / 2;

    for (size_t l = 0; l < map.getLayerNb(); ++l)
      {
	for (size_t y = 0; y < map.getHeight(); ++y)
	  {
	    for (size_t x = 0; x < map.getWidth(); ++x)
	      {
		ITile const &tile = map.at(l, x, y);
		size_t       id = tile.getSpriteId();
		size_t       pos = tile.getSpritePos();
		size_t       color = getColor(tile.getColor());

		if (tile.hasSprite())
		  {
		    if (color)
		      attron(COLOR_PAIR(color));
		    mvprintw(y + posY + 1, x + posX + 1, "%c",
		             m_sprites[id][pos]);
		    if (color)
		      attroff(COLOR_PAIR(color));
		  }
		else
		  {
		    if (color)
		      attron(COLOR_PAIR(color));
		    mvprintw(y + posY + 1, x + posX + 1, " ");
		    if (color)
		      attroff(COLOR_PAIR(color));
		  }
	      }
	  }
      }
    char border = '*';
    for (size_t y = 0; y < map.getHeight() + 2; ++y)
      {
	mvprintw(y + posY, posX, "%c", border);
	mvprintw(y + posY, posX + map.getWidth() + 2, "%c", border);
      }
    for (size_t x = 0; x < map.getWidth() + 2; ++x)
      {
	mvprintw(posY, x + posX, "%c", border);
	mvprintw(posY + map.getHeight() + 2, x + posX, "%c", border);
      }
  }

  void LibNcurses::updateGUI(IGUI &gui)
  {
    int w;
    int h;

    getmaxyx(stdscr, h, w);
    for (size_t i = 0; i < gui.size(); ++i)
      {
	IComponent const &comp = gui.at(i);
	size_t            x = comp.getX() * w;
	size_t            y = comp.getY() * h;
	size_t            width = comp.getWidth() * w;
	size_t            height = comp.getWidth() * h;
	size_t            color = getColor(comp.getBackgroundColor());

	if (color)
	  {
	    attron(COLOR_PAIR(color));
	    for (size_t _y = 0; _y < height; ++_y)
	      {
		for (size_t _x = 0; _x < width; ++_x)
		  {
		    mvprintw(y + _y, x + _x, " ");
		  }
	      }
	    attroff(COLOR_PAIR(color));
	  }
	if (comp.getText().size())
	  {
	    size_t c = getColor(comp.getTextColor());

	    if (c)
	      attron(COLOR_PAIR(color));
	    mvprintw(y, x, comp.getText().c_str());
	    if (c)
	      attroff(COLOR_PAIR(color));
	  }
      }
  }

  void LibNcurses::display()
  {
    ::refresh();
  }

  void LibNcurses::clear()
  {
    ::clear();
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

    pos.x = 0;
    pos.y = 0;
    return (pos);
  }

  size_t LibNcurses::getColor(Color c)
  {
    int r = c.r >> 7;
    int g = c.g >> 7;
    int b = c.b >> 7;

    return ((b << 2) | (g << 1) | (r));
  }
}
