#include <exception>
#include <iostream>
#include "LibSDL.hpp"

namespace arcade
{
	LibSDL::LibSDL(size_t width, size_t height) :
		m_map(nullptr), m_mapWidth(0), m_mapHeight(0), m_gui(nullptr)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "Error while initializing SDL2 : " << SDL_GetError() << std::endl;
			throw std::exception(); // TODO: create a good exception
		}

		m_win = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (m_win == NULL)
		{
			std::cerr << "Error while creating SDL2 Window (1): " << SDL_GetError() << std::endl;
			throw std::exception(); // TODO: create a good exception
		}

		m_winSurface = SDL_GetWindowSurface(m_win);

		if (m_winSurface == NULL)
		{
			std::cerr << "Error while creating SDL2 Window (2): " << SDL_GetError() << std::endl;
			throw std::exception(); // TODO: create a good exception
		}
	}

	LibSDL::~LibSDL()
	{
		SDL_DestroyWindow(m_win);
		SDL_Quit();
	}

	bool LibSDL::pollEvent(Event & e)
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
				// TODO : add mouse position
				break;
			case SDL_MOUSEBUTTONDOWN:
				e.type = EventType::ET_MOUSE;
				e.action = ActionType::AT_PRESSED;
				e.m_key = LibSDL::getMouseKey(ev.button.button);
				// TODO : add mouse position
				break;
			case SDL_MOUSEBUTTONUP:
				e.type = EventType::ET_MOUSE;
				e.action = ActionType::AT_RELEASED;
				e.m_key = LibSDL::getMouseKey(ev.button.button);
				// TODO : add mouse position
				break;
			case SDL_MOUSEWHEEL:
				e.type = EventType::ET_MOUSE;
				e.action = ActionType::AT_NONE;
				e.m_key = LibSDL::getMouseWheel(ev.wheel);
				// TODO : add mouse position
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
		return (true);
	}

	void LibSDL::loadSounds(std::vector<std::string> const & sounds)
	{
		(void)sounds;
		// TODO : implement
	}

	void LibSDL::playSound(int soundId)
	{
		(void)soundId;
		// TODO : implement
	}

	void LibSDL::updateMap(IMap const & map)
	{
		if (!m_map || m_mapWidth != map.getWidth() || m_mapHeight != map.getHeight())
		{
			if (m_map)
			{
				SDL_FreeSurface(m_map);
			}
			m_mapWidth = map.getWidth();
			m_mapHeight = map.getHeight();

			m_map = SDL_CreateRGBSurface(0, m_mapWidth * m_tileSize, m_mapHeight * m_tileSize, 32, 0, 0, 0, 0);
			if (!m_map)
			{
				std::cerr << "Failed to create SDL RGB surface"
#ifdef DEBUG
					<< " (" << m_mapWidth * m_tileSize << "x" << m_mapHeight * m_tileSize << ")"
#endif
					<< std::endl;
				throw std::exception(); // TODO : create good exception
			}

		}

		uint32_t *pixels = static_cast<uint32_t *>(m_map->pixels);

		for (size_t l = 0; l < map.getLayerNb(); ++l)
		{
			for (size_t y = 0; y < m_mapHeight; ++y)
			{
				for (size_t x = 0; x < m_mapWidth; ++x)
				{
					ITile const &tile = *map[l][y][x];

					if (tile.getSpriteId() != 0 && false) // TODO: enable
					{

					}
					else
					{
						Color color = tile.getColor();

						for (size_t _y = 0; _y < m_tileSize; ++_y)
						{
							for (size_t _x = 0; _x < m_tileSize; ++_x)
							{
								size_t X = x * m_tileSize + _x;
								size_t Y = y * m_tileSize + _y;

								pixels[Y * m_map->w + X] = color.full;
							}
						}
					}
				}
			}
		}
	}

	void LibSDL::updateGUI(IGUI const & gui)
	{
		(void)gui;
		// TODO : implement
	}

	void LibSDL::display()
	{
		// TODO : implement
		SDL_Rect rec = { 1000, 1000, 0, 0 };

		SDL_BlitSurface(m_map, NULL, m_winSurface, NULL);
		SDL_UpdateWindowSurface(m_win);
	}
	void LibSDL::clear()
	{
		// TODO : implement
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

	MouseKey LibSDL::getMouseWheel(SDL_MouseWheelEvent const & code)
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


}