#include <exception>
#include <iostream>
#include "LibSFML.hpp"

namespace arcade
{
  LibSFML::LibSFML(size_t width, size_t height) : m_guiPix(nullptr), m_gui(nullptr), m_guiSprite(nullptr)
  {
    m_win = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Arcade");
    m_mousePos = sf::Mouse::getPosition(*m_win.get());
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
    (void)map;
    // TODO : implement
  }

  void LibSFML::updateGUI(IGUI const & gui)
  {
    sf::Vector2u size = m_win->getSize();

    if (!m_gui)
      {
	// Create GUI
	m_guiPix = std::make_unique<uint32_t[]>(size.x * size.y);
	memset(m_guiPix.get(), 0, size.x * size.y * sizeof(Color));
	m_gui = std::make_unique<sf::Texture>();
	if (!m_gui->create(size.x, size.y))
	  throw std::exception(); // TODO: Exception
	// Create GUI sprite
	m_guiSprite = std::make_unique<sf::Sprite>(*m_gui);
      }
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
    // TODO : Implement
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
