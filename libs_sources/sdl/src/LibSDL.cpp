#include <exception>
#include <iostream>
#include <algorithm>
#if defined(_WIN32)
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#include "LibSDL.hpp"
#include "WindowError.hpp"
#include "InitializationError.hpp"
#include "RessourceError.hpp"

namespace arcade
{
  LibSDL::LibSDL(size_t width, size_t height)
  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
      {
	throw InitializationError("Error while initializing SDL2 : " +
	                          std::string(SDL_GetError()));
      }

    m_win = SDL_CreateWindow("Arcade sdl", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, width, height,
                             SDL_WINDOW_SHOWN);

    if (m_win == NULL)
      {
	throw WindowError("Cannot create SDL2 Window: " +
	                  std::string(SDL_GetError()));
      }

    m_winSurface = SDL_GetWindowSurface(m_win);

    if (m_winSurface == NULL)
      {
	throw WindowError("Cannot create SDL2 Window Surface: " +
	                  std::string(SDL_GetError()));
      }

    if (TTF_Init() == -1)
      {
	throw InitializationError("Error while initializing SDL ttf");
      }

    m_font = TTF_OpenFont("assets/fonts/arial.ttf", 30);
  }

  LibSDL::~LibSDL()
  {
    SDL_DestroyWindow(m_win);
    SDL_Quit();
    TTF_CloseFont(m_font);
    TTF_Quit();
  }

  bool LibSDL::pollEvent(Event &e)
  {
    SDL_Event ev;

    if (SDL_PollEvent(&ev))
      {
	switch (ev.type)
	  {
	  case SDL_KEYUP:
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_RELEASED;
	    e.kb_key = LibSDL::getKeyboardKey(ev.key.keysym.sym);
	    break;
	  case SDL_KEYDOWN:
	    e.type = EventType::ET_KEYBOARD;
	    e.action = ActionType::AT_PRESSED;
	    e.kb_key = LibSDL::getKeyboardKey(ev.key.keysym.sym);
	    break;
	  case SDL_MOUSEMOTION:
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_MOVED;
	    e.m_key = MouseKey::M_NONE;
	    break;
	  case SDL_MOUSEBUTTONDOWN:
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_PRESSED;
	    e.m_key = LibSDL::getMouseKey(ev.button.button);
	    break;
	  case SDL_MOUSEBUTTONUP:
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_RELEASED;
	    e.m_key = LibSDL::getMouseKey(ev.button.button);
	    break;
	  case SDL_MOUSEWHEEL:
	    e.type = EventType::ET_MOUSE;
	    e.action = ActionType::AT_NONE;
	    e.m_key = LibSDL::getMouseWheel(ev.wheel);
	    break;
	  case SDL_QUIT:
	    e.type = EventType::ET_QUIT;
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

  bool LibSDL::doesSupportSound() const
  {
    return (false);
  }

  void LibSDL::loadSounds(
      std::vector<std::pair<std::string, SoundType>> const &sounds)
  {
    static_cast<void>(sounds);
  }

  void LibSDL::soundControl(Sound const &sound)
  {
    static_cast<void>(sound);
  }

  void LibSDL::updateMap(IMap const &map)
  {
    // If there is nothing to display, return (and avoid dividing by zero)
    if (map.getWidth() == 0 || map.getHeight() == 0)
      {
	return;
      }

    // Calculate the current tile size
    int tileSize = std::min(m_winSurface->w / map.getWidth(),
                            m_winSurface->h / map.getHeight());

    tileSize = std::min(tileSize, static_cast<int>(m_maxTileSize));

    // Loop on each layer
    for (size_t l = 0; l < map.getLayerNb(); ++l)
      {
	// Loop on each line
	for (size_t y = 0; y < map.getHeight(); ++y)
	  {
	    // Loop on each tile
	    for (size_t x = 0; x < map.getWidth(); ++x)
	      {
		// Get the current tile
		ITile const &tile = map.at(l, x, y);
		Color        color = tile.getColor();

		// Calculate centered position
		int posX = m_winSurface->w / 2 -
		           (map.getWidth() * tileSize / 2) +
		           (x + tile.getShiftX()) * tileSize;
		int posY = m_winSurface->h / 2 -
		           (map.getHeight() * tileSize / 2) +
		           (y + tile.getShiftY()) * tileSize;
		// int posX = (x + tile.getShiftX()) * tileSize;
		// int posY = (y + tile.getShiftY()) * tileSize;
		SDL_Rect rect = {posX, posY, tileSize, tileSize};

		// If it has sprite, draw it
		if (tile.hasSprite() &&
		    m_sprites[tile.getSpriteId()][tile.getSpritePos()])
		  {
		    SDL_BlitScaled(
		        m_sprites[tile.getSpriteId()][tile.getSpritePos()],
		        NULL, m_winSurface, &rect);
		  }
		// Else if it has color, draw it
		else if (color.a != 0)
		  {
		    fillRect(m_winSurface, &rect, color);
		  }
	      }
	  }
      }
  }

  void LibSDL::updateGUI(IGUI &gui)
  {
    for (size_t i = 0; i < gui.size(); ++i)
      {
	IComponent const &comp = gui.at(i);
	int               x = comp.getX() * m_winSurface->w;
	int               y = comp.getY() * m_winSurface->h;
	int               width = comp.getWidth() * m_winSurface->w;
	int               height = comp.getHeight() * m_winSurface->h;
	std::string       str = comp.getText();

	Color color = comp.getBackgroundColor();

	SDL_Rect rect = {x, y, width, height};

	if (comp.hasSprite() && m_sprites[comp.getBackgroundId()][0])
	  {
	    SDL_BlitScaled(m_sprites[comp.getBackgroundId()][0], NULL,
	                   m_winSurface, &rect);
	  }
	else if (color.a != 0)
	  {
	    fillRect(m_winSurface, &rect, color);
	  }

	if (str.length() > 0)
	  {
	    SDL_Color c = {255, 255, 255, 255};
	    if (!m_font)
	      continue;
	    SDL_Surface *text = TTF_RenderText_Blended(m_font, str.c_str(), c);
	    SDL_Rect     pos;

	    if (text == nullptr)
	      continue;

	    pos.x = x;
	    pos.y = y;
	    SDL_BlitSurface(text, NULL, m_winSurface, &pos);
	    SDL_FreeSurface(text);
	  }
      }
  }

  void LibSDL::display()
  {
    SDL_UpdateWindowSurface(m_win);
  }

  void LibSDL::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    std::vector<std::unique_ptr<ISprite>> s(std::move(sprites));

    for (std::vector<SDL_Surface *> &s : m_sprites)
      {
	for (SDL_Surface *_s : s)
	  {
	    if (_s)
	      {
		SDL_FreeSurface(_s);
	      }
	  }
      }
    m_sprites.clear();

    for (std::unique_ptr<ISprite> const &sprite : s)
      {
	std::vector<SDL_Surface *> images;

#if defined(DEBUG)
	std::cout << "Loading sprite " << m_sprites.size() << ", "
	          << sprite->spritesCount() << std::endl;
#endif
	for (size_t i = 0; i < sprite->spritesCount(); ++i)
	  {
#if defined(DEBUG)
	    std::cout << "File: '" << sprite->getGraphicPath(i) << "'"
	              << std::endl;
#endif
	    SDL_Surface *surface = IMG_Load(sprite->getGraphicPath(i).c_str());

	    if (!surface)
	      {
		throw RessourceError("File not found: " +
		                     sprite->getGraphicPath(i));
	      }
#if defined(DEBUG)
	    std::cout << "Loaded " << surface->w << "x" << surface->h
	              << std::endl;
#endif
	    // SDL_FillRect(surface, NULL, Color::Black.full);
	    images.push_back(surface);
	  }
	m_sprites.push_back(images);
      }
  }

  void LibSDL::clear()
  {
    SDL_FillRect(m_winSurface, NULL, Color::Black.full);
  }

  KeyboardKey LibSDL::getKeyboardKey(SDL_Keycode code)
  {
    if (m_kb_keys.find(code) != m_kb_keys.end())
      return (m_kb_keys[code]);
    return (KeyboardKey::KB_NONE);
  }

  MouseKey LibSDL::getMouseKey(Uint8 code)
  {
    if (m_mouse_keys.find(code) != m_mouse_keys.end())
      {
	return (m_mouse_keys[code]);
      }
    return (MouseKey::M_NONE);
  }

  MouseKey LibSDL::getMouseWheel(SDL_MouseWheelEvent const &code)
  {
    if (code.y == 0)
      {
	return (MouseKey::M_NONE);
      }
    else if ((code.y > 0 && code.direction == SDL_MOUSEWHEEL_NORMAL) ||
             (code.y < 0 && code.direction == SDL_MOUSEWHEEL_FLIPPED))
      {
	return (MouseKey::M_SCROLL_UP);
      }
    else
      {
	return (MouseKey::M_SCROLL_DOWN);
      }
  }

  void LibSDL::fillRect(SDL_Surface *surface, SDL_Rect *rect, Color color)
  {
    if (rect->x >= surface->w || rect->y >= surface->h)
      {
	return;
      }

    if (color.a == 255)
      {
	SDL_FillRect(surface, rect, color.full);
	return;
      }

    // Calculate position and size
    int posX = std::max(0, rect->x);
    int posY = std::max(0, rect->y);
    int width = std::min(rect->w, surface->w - posX);
    int height = std::min(rect->h, surface->h - posY);

    // Get pixel array
    Color *pixels = static_cast<Color *>(surface->pixels);

    // Get the color alpha
    double a = color.a / 255.0;
    double _a = 1.0 - a;

    for (int y = 0; y < height; ++y)
      {
	for (int x = 0; x < width; ++x)
	  {
	    int   X = posX + x;
	    int   Y = posY + y;
	    Color old = pixels[Y * surface->w + X];

	    Color merged(color.r * a + old.r * _a, color.g * a + old.g * _a,
	                 color.b * a + old.b * _a, 255);

	    pixels[Y * surface->w + X] = merged;
	  }
      }
  }
}
