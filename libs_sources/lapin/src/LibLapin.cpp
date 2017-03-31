#include <exception>
#include <iostream>
#include "LibLapin.hpp"

namespace arcade
{
  LibLapin::LibLapin(size_t width, size_t height) : m_width(width), m_height(height),
						    m_map(nullptr),
						    m_mapWidth(0), m_mapHeight(0)
  {
    m_win = bunny_start(width, height, false, "Arcade");
    if (!m_win)
      {
	std::cerr << "Cannot create libLapin Window"
#if defined(DEBUG)
		  << " [" << width << "x" << height << "]"
#endif
		  << std::endl;
      }
  }

  LibLapin::~LibLapin()
  {
    if (m_win)
      bunny_stop(m_win);
  }

  bool LibLapin::pollEvent(Event &e)
  {
    // TODO
    return (false);
  }

  bool LibLapin::doesSupportSound() const
  {
    return (true);
  }

  void LibLapin::loadSounds(std::vector<std::string> const & sounds)
  {
    // TODO
  }

  void LibLapin::playSound(int soundId)
  {
    // TODO
  }

  void LibLapin::updateMap(IMap const & map)
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

  void LibLapin::updateGUI(IGUI const & gui)
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

  void LibLapin::display()
  {
    // TODO
  }

  void LibLapin::clear()
  {
    if (m_win)
      bunny_clear(&m_win->buffer, BLACK);
  }

  KeyboardKey LibLapin::getKeyboardKey(int code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibLapin::getMouseKey(int code)
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
}
