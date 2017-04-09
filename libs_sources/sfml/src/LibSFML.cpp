#include <exception>
#include <iostream>
#include <cstring>
#include "LibSFML.hpp"
#include "RessourceError.hpp"

namespace arcade
{
  LibSFML::LibSFML(size_t width, size_t height)
  {
      m_win = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Arcade sfml");
      m_mousePos = sf::Mouse::getPosition(*m_win);
      if (!m_font.loadFromFile("assets/fonts/arial.ttf"))
      {
        throw RessourceError("Cannot load assets/fonts/arial.ttf");
      }
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

  void LibSFML::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds)
  {
    size_t index;

    m_sound.clear();
    m_soundBuffer.clear();
    m_music.clear();
    for (std::pair<std::string, SoundType> const &p : sounds)
      {
	if (p.second == SoundType::MUSIC)
	  {
	    m_music.push_back(std::make_unique<sf::Music>());
	    sf::Music &cur = *m_music.back();
	    if (!cur.openFromFile(p.first))
	      {
		std::cerr << "Cannot open music: " << p.first << std::endl;
		throw RessourceError("Error loading music");
	      }
            index = m_music.size() - 1;
	  }
	else
	  {
	  m_soundBuffer.emplace_back();
          sf::SoundBuffer &buf = m_soundBuffer.back();
	    if (!buf.loadFromFile(p.first))
	      {
		std::cerr << "Cannot open sound: " << p.first << std::endl;
		throw RessourceError("Error loading sound");
	      }
	    m_sound.emplace_back();
            sf::Sound &sound = m_sound.back();
            sound.setBuffer(buf);
            index = m_sound.size() - 1;
	  }
        m_soundIndex.emplace_back(p.second, index);
      }
  }

  void LibSFML::soundControl(Sound const &sound)
  {
    SoundType type = m_soundIndex[sound.id].first;
    size_t index = m_soundIndex[sound.id].second;

    if (type == SoundType::MUSIC)
    {
      m_music[index]->play();
    }
    else
    {
      m_sound[index].play();
    }
  }

  void LibSFML::loadSprites(std::vector<std::unique_ptr<ISprite>>&& sprites)
  {
    // Move the given vector
    std::vector<std::unique_ptr<ISprite>> sp(std::move(sprites));

    // Remove all the current sprites
    m_sprites.clear();

    // Loop on every sprites
    for (std::unique_ptr<ISprite> const &s : sp)
    {
      // Current sprite (with multiple slot for animation)
      m_sprites.emplace_back();
      std::vector<sf::Texture> &sprite = m_sprites.back();

      // Loop on every frame
      for (size_t i = 0; i < s->spritesCount(); ++i)
      {
        sprite.emplace_back();
        sf::Texture &tex = sprite.back();

        // Load the current image
        if (!tex.loadFromFile(s->getGraphicPath(i)))
        {
          throw RessourceError("Error loading image");
        }
      }
    }
  }

  void LibSFML::updateMap(IMap const & map)
  {
    size_t tileSize;
    sf::Vector2u winSize = m_win->getSize();
    sf::Vector2u mapSize(map.getWidth(), map.getHeight());

    // Check if the map is displayable (and avoid dividing by zero)
    if (mapSize.x == 0 || mapSize.y == 0)
      return;

    // Calculate the size of one tile (in pixels)
    tileSize = std::min(winSize.x / mapSize.x, winSize.y / mapSize.y);
    tileSize = std::min(tileSize, static_cast<size_t>(24));

    // Loop on each layer
    for (size_t layer = 0; layer < map.getLayerNb(); ++layer)
    {
      // Loop on each line
      for (size_t y = 0; y < mapSize.y; ++y)
      {
        // Loop on each tile
        for (size_t x = 0; x < mapSize.x; ++x)
        {
          // Get the current tile
          ITile const &tile = map.at(layer, x, y);
          Color color = tile.getColor();

          sf::RectangleShape rectangle;

          // Set the sprite or the color
          if (tile.hasSprite())
          {
            rectangle.setTexture(&m_sprites[tile.getSpriteId()][tile.getSpritePos()]);
          }
          else
          {
            rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
          }

          // Calculate and set the position and size
          size_t posX = winSize.x / 2 - (mapSize.x / 2 - x) * tileSize;
          size_t posY = winSize.y / 2 - (mapSize.y / 2 - y) * tileSize;

          rectangle.setPosition(sf::Vector2f(posX, posY));
          rectangle.setSize(sf::Vector2f(tileSize, tileSize));

          // Draw
          m_win->draw(rectangle);
        }
      }
    }
  }

  void LibSFML::updateGUI(IGUI & gui)
  {
    // Get the Window size
    sf::Vector2u const size = m_win->getSize();

    // Loop on every components
    for (size_t i = 0; i < gui.size(); ++i)
      {
        // Get the current component
	IComponent const &comp = gui.at(i);

        // Calculate it's position and size
	size_t x = comp.getX() * size.x;
	size_t y = comp.getY() * size.y;
	size_t width = comp.getWidth() * size.x;
	size_t height = comp.getHeight() * size.y;

        // Get the component properties
        size_t backgroundId = comp.getBackgroundId();
        Color color = comp.getBackgroundColor();
        std::string str = comp.getText();

        // If there is a background (image or color), display it
        if (comp.hasSprite() || color.a != 0)
        {
          sf::RectangleShape shape;

          // Set texture OR color
          if (comp.hasSprite())
            shape.setTexture(&m_sprites[backgroundId][0]);
          else
            shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));

          // Set position and size
          shape.setPosition(x, y);
          shape.setSize(sf::Vector2f(width, height));

          // Draw
          m_win->draw(shape);
        }

        // Create and display text if there is one
        /*if (str.length() > 0)
        {
          sf::Text text(str, m_font);

          text.setPosition(x, y);

          m_win->draw(text);
        }*/
      }
  }

  void LibSFML::display()
  {
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
