#include <exception>
#include <iostream>
#include <cstring>
#include "LibSFML.hpp"

namespace arcade
{
  LibSFML::LibSFML(size_t width, size_t height) : m_guiPix(nullptr), m_gui(nullptr), m_guiSprite(nullptr), m_mapPix(nullptr), m_map(nullptr), m_mapSprite(nullptr), m_mapWidth(0), m_mapHeight(0)
  {
    m_win = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Arcade");
    m_mousePos = sf::Mouse::getPosition(*m_win.get());

    // Create GUI
    m_guiPix = std::make_unique<uint32_t[]>(width * height);
    memset(static_cast<void *>(m_guiPix.get()), 0, width * height * sizeof(Color));
    m_gui = std::make_unique<sf::Texture>();
    if (!m_gui->create(width, height))
      {
	std::cerr << "Cannot create SFML Texture"
#if defined(DEBUG)
		  << " (" << width << "x" << height << ")"
#endif
		  << std::endl;
	throw std::exception(); // TODO: Exception
      }
    // Create GUI sprite
    m_guiSprite = std::make_unique<sf::Sprite>(*m_gui);
  }

  LibSFML::~LibSFML()
  {
    m_win->close();
  }

  bool LibSFML::pollEvent(Event & e)
  {
    sf::Event	event;

    if (m_win->pollEvent(event))
      {
	switch (event.type)
	  {
	  case sf::Event::Closed:
	    // The window requested to be closed
	    e.type = EventType::ET_QUIT;
	    break;
	  case sf::Event::Resized:
	    // The window was resized
	    break;
	  case sf::Event::LostFocus:
	    // The window lost focus
	    break;
	  case sf::Event::GainedFocus:
	    break;

	  case sf::Event::KeyPressed:
	    // A key was pressed
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_PRESSED;
	    e.kb_key = LibSFML::getKeyboardKey(event.key.code);
	    break;
	  case sf::Event::KeyReleased:
	    // A key was released
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_RELEASED;
	    e.kb_key = LibSFML::getKeyboardKey(event.key.code);
	    break;

	  case sf::Event::MouseMoved:
	    // The mouse moved
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_MOVED;
	    e.m_key = MouseKey::M_NONE;
	    e.pos_abs = LibSFML::getMousePos();
	    break;
	  case sf::Event::MouseButtonPressed:
	    // A mouse button was pressed
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_PRESSED;
	    e.m_key = LibSFML::getMouseKey(event.mouseButton.button);
	    e.pos_abs = LibSFML::getMousePos();
	    break;
	  case sf::Event::MouseButtonReleased:
	    // A mouse button was released
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_RELEASED;
	    e.m_key = LibSFML::getMouseKey(event.mouseButton.button);
	    e.pos_abs = LibSFML::getMousePos();
	    break;
	  case sf::Event::MouseWheelScrolled:
	    // A mouse wheel was scrolled
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_NONE;
	    //e.m_key = ;
	    e.pos_abs = LibSFML::getMousePos();
	    // TODO: Get mousekey
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

  bool LibSFML::doesSupportSound() const
  {
    return (true);
  }

  void LibSFML::loadSounds(std::vector<std::string> const & sounds)
  {
    m_soundBuffer.reserve(sounds.size());
    for (std::vector<std::string>::size_type i = 0; i != sounds.size(); i++)
      {
	m_soundBuffer[i] = std::make_unique<sf::SoundBuffer>();
	if (m_soundBuffer[i]->loadFromFile(sounds[i].c_str()))
	  {
	    throw std::exception(); // TODO: Exception
	  }
	m_sound[i] = std::make_unique<sf::Sound>();
	m_sound[i]->setBuffer(*m_soundBuffer[i]);
      }
  }

  void LibSFML::playSound(int soundId)
  {
    m_sound[soundId]->play();
  }

  void LibSFML::updateMap(IMap const & map)
  {
    if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
      {
	m_mapPix.release();
	m_map.release();
	m_mapSprite.release();
	m_mapWidth = map.getWidth();
	m_mapHeight = map.getHeight();
	if (!m_mapWidth || !m_mapHeight)
	  return ;
	// Create MAP
	m_mapPix = std::make_unique<uint32_t[]>(m_mapWidth * m_tileSize * m_mapHeight * m_tileSize);
	m_map = std::make_unique<sf::Texture>();
	if (!m_map->create(m_mapWidth * m_tileSize, m_mapHeight * m_tileSize))
	  {
	    std::cerr << "Cannot create SFML Texture"
#if defined(DEBUG)
		      << " (" << m_mapWidth * m_tileSize << "x" << m_mapHeight * m_tileSize << ")"
#endif
		      << std::endl;
	    throw std::exception(); // TODO: create good exception
	  }
	m_mapSprite = std::make_unique<sf::Sprite>(*m_map);
      }
    Color *pixels = reinterpret_cast<Color *>(m_mapPix.get());
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
		    if (color.rgba[3] != 0) // TODO: color.a ?
		      {
			for (size_t _y = 0; _y < m_tileSize; ++_y)
			  {
			    for (size_t _x = 0; _x < m_tileSize; ++_x)
			      {
				size_t X = x * m_tileSize + _x;
				size_t Y = y * m_tileSize + _y;
				size_t pix = Y * mapWidth + X;
				double a(color.a / 255.0);
				Color old(pixels[pix]);
				Color merged(color.r * a + old.r * (1 - a),
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
    m_map->update(reinterpret_cast<uint8_t *>(m_mapPix.get()));
  }

  void LibSFML::updateGUI(IGUI const & gui)
  {
    sf::Vector2u const size = m_win->getSize();

    // TODO: Check reinterpret_cast
    Color *pixels = reinterpret_cast<Color *>(m_guiPix.get());
    memset(pixels, 0, size.x * size.y * sizeof(Color));
    for (size_t i = 0; i < gui.size(); ++i)
      {
	IComponent const &comp = gui.at(i);
	size_t x = comp.getX() * size.x;
	size_t y = comp.getY() * size.y;
	size_t width = comp.getWidth() * size.x;
	size_t height = comp.getHeight() * size.y;
	Color color = comp.getBackgroundColor();
	double a(color.a / 255.0);
	if (color.a != 0)
	  {
	    for (size_t _y = 0; _y < height; ++_y)
	      {
		for (size_t _x = 0; _x < width; ++_x)
		  {
		    size_t pix = (y + _y) * size.x + (x + _x);
		    Color old(pixels[pix]);
		    Color merged(color.r * a + old.r * (1 - a),
				 color.g * a + old.g * (1 - a),
				 color.b * a + old.b * (1 - a),
				 color.a + old.a * (1 - a));
		    pixels[pix] = merged.full;
		  }
	      }
	  }
      }
    m_gui->update(reinterpret_cast<uint8_t *>(m_guiPix.get()));
  }

  void LibSFML::display()
  {
    if (m_mapSprite)
      m_win->draw(*m_mapSprite);
    m_win->draw(*m_guiSprite);
    m_win->display();
  }
  void LibSFML::clear()
  {
    m_win->clear();
  }

  KeyboardKey LibSFML::getKeyboardKey(sf::Keyboard::Key code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibSFML::getMouseKey(sf::Mouse::Button code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      return (m_mouse_keys[code]);
    return (MouseKey::M_NONE);
  }

  MouseKey LibSFML::getMouseWheel(sf::Mouse::Wheel code)
  {
    // TODO : implement
    (void)code;
    return (MouseKey::M_NONE);
  }

  MousePos LibSFML::getMousePos()
  {
    MousePos	pos;

    m_mousePos = sf::Mouse::getPosition(*m_win.get());
    pos.x = static_cast<double>(m_mousePos.x);
    pos.y = static_cast<double>(m_mousePos.y);
    return (pos);
  }
}
