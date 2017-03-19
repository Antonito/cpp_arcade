#include "LibSDL.hpp"

namespace arcade
{
	// Mapping SDL Mouse Button with MouseKey enum
	std::map<Uint8, MouseKey> LibSDL::m_mouse_keys =
	{
		{ SDL_BUTTON_LEFT, M_LEFT_CLICK },
		{ SDL_BUTTON_MIDDLE, M_MIDDLE_CLICK },
		{ SDL_BUTTON_RIGHT, M_RIGHT_CLICK },
		{ SDL_BUTTON_X1, M_BT0 },
		{ SDL_BUTTON_X2, M_BT1 }
	};

	std::map<SDL_Keycode, KeyboardKey> LibSDL::m_kb_keys = 
	{
		{ SDLK_0, KB_0 },
		{ SDLK_1, KB_1 },
		{ SDLK_2, KB_2 },
		{ SDLK_3, KB_3 },
		{ SDLK_4, KB_4 },
		{ SDLK_5, KB_5 },
		{ SDLK_6, KB_6 },
		{ SDLK_7, KB_7 },
		{ SDLK_8, KB_8 },
		{ SDLK_9, KB_9 },
		{ SDLK_a, KB_A },
		{ SDLK_b, KB_B },
		{ SDLK_c, KB_C },
		{ SDLK_d, KB_D },
		{ SDLK_e, KB_E },
		{ SDLK_f, KB_F },
		{ SDLK_g, KB_G },
		{ SDLK_h, KB_H },
		{ SDLK_i, KB_I },
		{ SDLK_j, KB_J },
		{ SDLK_k, KB_K },
		{ SDLK_l, KB_L },
		{ SDLK_m, KB_M },
		{ SDLK_n, KB_N },
		{ SDLK_o, KB_O },
		{ SDLK_p, KB_P },
		{ SDLK_q, KB_Q },
		{ SDLK_r, KB_R },
		{ SDLK_s, KB_S },
		{ SDLK_t, KB_T },
		{ SDLK_u, KB_U },
		{ SDLK_v, KB_V },
		{ SDLK_w, KB_W },
		{ SDLK_x, KB_X },
		{ SDLK_y, KB_Y },
		{ SDLK_z, KB_Z },
		{ SDLK_BACKSLASH, KB_BACKSLASH },
		{ SDLK_BACKSPACE, KB_BACKSPACE },
		{ SDLK_CAPSLOCK, KB_CAPSLOCK },
		{ SDLK_COMMA, KB_COMMA },
		{ SDLK_DELETE, KB_DELETE },
		{ SDLK_DOWN, KB_ARROW_DOWN },
		{ SDLK_END, KB_END },
		{ SDLK_EQUALS, KB_EQUALS },
		{ SDLK_ESCAPE, KB_ESCAPE },
		{ SDLK_F1, KB_FN1 },
		{ SDLK_F2, KB_FN2 },
		{ SDLK_F3, KB_FN3 },
		{ SDLK_F4, KB_FN4 },
		{ SDLK_F5, KB_FN5 },
		{ SDLK_F6, KB_FN6 },
		{ SDLK_F7, KB_FN7 },
		{ SDLK_F8, KB_FN8 },
		{ SDLK_F9, KB_FN9 },
		{ SDLK_F10, KB_FN10 },
		{ SDLK_F11, KB_FN11 },
		{ SDLK_F12, KB_FN12 },
		{ SDLK_HOME, KB_HOME },
		{ SDLK_KP_0, KB_0 },
		{ SDLK_KP_1, KB_1 },
		{ SDLK_KP_2, KB_2 },
		{ SDLK_KP_3, KB_3 },
		{ SDLK_KP_4, KB_4 },
		{ SDLK_KP_5, KB_5 },
		{ SDLK_KP_6, KB_6 },
		{ SDLK_KP_7, KB_7 },
		{ SDLK_KP_8, KB_8 },
		{ SDLK_KP_9, KB_9 },
		{ SDLK_KP_MINUS, KB_MINUS },
		{ SDLK_KP_MULTIPLY, KB_ASTERISK },
		{ SDLK_KP_PERCENT, KB_PERCENT },
		{ SDLK_KP_PERIOD, KB_DOT },
		{ SDLK_KP_PLUS, KB_PLUS },
		{ SDLK_KP_MINUS, KB_MINUS },
		{ SDLK_LALT, KB_LALT },
		{ SDLK_LCTRL, KB_LCTRL },
		{ SDLK_LEFT, KB_ARROW_LEFT },
		{ SDLK_LEFTBRACKET, KB_LEFTBRACKET },
		{ SDLK_LSHIFT, KB_LSHIFT },
		{ SDLK_MINUS, KB_MINUS },
		{ SDLK_PAGEDOWN, KB_PAGEDOWN },
		{ SDLK_PAGEUP, KB_PAGEUP },
		{ SDLK_PERIOD, KB_DOT },
		{ SDLK_RALT, KB_RALT },
		{ SDLK_RCTRL, KB_RCTRL },
		{ SDLK_RIGHT, KB_ARROW_RIGHT },
		{ SDLK_RIGHTBRACKET, KB_RIGHTBRACKET },
		{ SDLK_RSHIFT, KB_RSHIFT },
		{ SDLK_SEMICOLON, KB_SEMICOLON },
		{ SDLK_SLASH, KB_SLASH },
		{ SDLK_SPACE, KB_SPACE },
		{ SDLK_TAB, KB_TAB },
		{ SDLK_UP, KB_ARROW_UP },
		{ SDLK_AMPERSAND, KB_AMPERSAND },
		{ SDLK_ASTERISK, KB_ASTERISK },
		{ SDLK_AT, KB_ATSYMBOL },
		{ SDLK_CARET, KB_CIRCUMFLEX },
		{ SDLK_COLON, KB_COLON },
		{ SDLK_DOLLAR, KB_DOLLAR },
		{ SDLK_EXCLAIM, KB_EXCLAMATION },
		{ SDLK_GREATER, KB_SUPERIOR },
		{ SDLK_HASH, KB_HASHTAG },
		{ SDLK_LEFTPAREN, KB_LEFTPAREN },
		{ SDLK_LESS, KB_INFERIOR },
		{ SDLK_PERCENT, KB_PERCENT },
		{ SDLK_PLUS, KB_PLUS },
		{ SDLK_QUESTION, KB_QUESTION },
		{ SDLK_QUOTEDBL, KB_DOUBLEQUOTE },
		{ SDLK_RIGHTPAREN, KB_RIGHTPAREN },
		{ SDLK_UNDERSCORE, KB_UNDERSCORE }
	};
}