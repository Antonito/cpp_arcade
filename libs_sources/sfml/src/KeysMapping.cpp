#include "LibSFML.hpp"

namespace arcade
{
  // Mapping SFML Mouse Button with MouseKey enum
  std::map<sf::Mouse::Button, MouseKey> LibSFML::m_mouse_keys =
    {
      { sf::Mouse::Button::Left, M_LEFT_CLICK },
      { sf::Mouse::Button::Middle, M_MIDDLE_CLICK },
      { sf::Mouse::Button::Right, M_RIGHT_CLICK },
      { sf::Mouse::Button::XButton1, M_BT0 },
      { sf::Mouse::Button::XButton2, M_BT1 }
    };

  std::map<sf::Keyboard::Key, KeyboardKey> LibSFML::m_kb_keys =
    {
      { sf::Keyboard::Key::Num0, KB_0 },
      { sf::Keyboard::Key::Num1, KB_1 },
      { sf::Keyboard::Key::Num2, KB_2 },
      { sf::Keyboard::Key::Num3, KB_3 },
      { sf::Keyboard::Key::Num4, KB_4 },
      { sf::Keyboard::Key::Num5, KB_5 },
      { sf::Keyboard::Key::Num6, KB_6 },
      { sf::Keyboard::Key::Num7, KB_7 },
      { sf::Keyboard::Key::Num8, KB_8 },
      { sf::Keyboard::Key::Num9, KB_9 },
      { sf::Keyboard::Key::A, KB_A },
      { sf::Keyboard::Key::B, KB_B },
      { sf::Keyboard::Key::C, KB_C },
      { sf::Keyboard::Key::D, KB_D },
      { sf::Keyboard::Key::E, KB_E },
      { sf::Keyboard::Key::F, KB_F },
      { sf::Keyboard::Key::G, KB_G },
      { sf::Keyboard::Key::H, KB_H },
      { sf::Keyboard::Key::I, KB_I },
      { sf::Keyboard::Key::J, KB_J },
      { sf::Keyboard::Key::K, KB_K },
      { sf::Keyboard::Key::L, KB_L },
      { sf::Keyboard::Key::M, KB_M },
      { sf::Keyboard::Key::N, KB_N },
      { sf::Keyboard::Key::O, KB_O },
      { sf::Keyboard::Key::P, KB_P },
      { sf::Keyboard::Key::Q, KB_Q },
      { sf::Keyboard::Key::R, KB_R },
      { sf::Keyboard::Key::S, KB_S },
      { sf::Keyboard::Key::T, KB_T },
      { sf::Keyboard::Key::U, KB_U },
      { sf::Keyboard::Key::V, KB_V },
      { sf::Keyboard::Key::W, KB_W },
      { sf::Keyboard::Key::X, KB_X },
      { sf::Keyboard::Key::Y, KB_Y },
      { sf::Keyboard::Key::Z, KB_Z },
      { sf::Keyboard::Key::BackSlash, KB_BACKSLASH },
      { sf::Keyboard::Key::BackSpace, KB_BACKSPACE },
      //{ sf::Keyboard::Key::, KB_CAPSLOCK },
      { sf::Keyboard::Key::Comma, KB_COMMA },
      { sf::Keyboard::Key::Delete, KB_DELETE },
      { sf::Keyboard::Key::Down, KB_ARROW_DOWN },
      { sf::Keyboard::Key::End, KB_END },
      { sf::Keyboard::Key::Equal, KB_EQUALS },
      { sf::Keyboard::Key::Escape, KB_ESCAPE },
      { sf::Keyboard::Key::F1, KB_FN1 },
      { sf::Keyboard::Key::F2, KB_FN2 },
      { sf::Keyboard::Key::F3, KB_FN3 },
      { sf::Keyboard::Key::F4, KB_FN4 },
      { sf::Keyboard::Key::F5, KB_FN5 },
      { sf::Keyboard::Key::F6, KB_FN6 },
      { sf::Keyboard::Key::F7, KB_FN7 },
      { sf::Keyboard::Key::F8, KB_FN8 },
      { sf::Keyboard::Key::F9, KB_FN9 },
      { sf::Keyboard::Key::F10, KB_FN10 },
      { sf::Keyboard::Key::F11, KB_FN11 },
      { sf::Keyboard::Key::F12, KB_FN12 },
      { sf::Keyboard::Key::Home, KB_HOME },
      { sf::Keyboard::Key::Numpad0, KB_0 },
      { sf::Keyboard::Key::Numpad1, KB_1 },
      { sf::Keyboard::Key::Numpad2, KB_2 },
      { sf::Keyboard::Key::Numpad3, KB_3 },
      { sf::Keyboard::Key::Numpad4, KB_4 },
      { sf::Keyboard::Key::Numpad5, KB_5 },
      { sf::Keyboard::Key::Numpad6, KB_6 },
      { sf::Keyboard::Key::Numpad7, KB_7 },
      { sf::Keyboard::Key::Numpad8, KB_8 },
      { sf::Keyboard::Key::Numpad9, KB_9 },
      { sf::Keyboard::Key::Subtract, KB_MINUS },
      { sf::Keyboard::Key::Multiply, KB_ASTERISK },
      //{ SDLK_KP_PERCENT, KB_PERCENT },
      { sf::Keyboard::Key::Period, KB_DOT },
      { sf::Keyboard::Key::Add, KB_PLUS },
      { sf::Keyboard::Key::Dash, KB_MINUS },
      { sf::Keyboard::Key::LAlt, KB_LALT },
      { sf::Keyboard::Key::LControl, KB_LCTRL },
      { sf::Keyboard::Key::Left, KB_ARROW_LEFT },
      { sf::Keyboard::Key::LBracket, KB_LEFTBRACKET },
      { sf::Keyboard::Key::LShift, KB_LSHIFT },
      { sf::Keyboard::Key::Dash, KB_MINUS },
      { sf::Keyboard::Key::PageDown, KB_PAGEDOWN },
      { sf::Keyboard::Key::PageUp, KB_PAGEUP },
      { sf::Keyboard::Key::Period, KB_DOT },
      { sf::Keyboard::Key::RAlt, KB_RALT },
      { sf::Keyboard::Key::RControl, KB_RCTRL },
      { sf::Keyboard::Key::Right, KB_ARROW_RIGHT },
      { sf::Keyboard::Key::RBracket, KB_RIGHTBRACKET },
      { sf::Keyboard::Key::RShift, KB_RSHIFT },
      { sf::Keyboard::Key::SemiColon, KB_SEMICOLON },
      { sf::Keyboard::Key::Divide, KB_SLASH },
      { sf::Keyboard::Key::Space, KB_SPACE },
      { sf::Keyboard::Key::Tab, KB_TAB },
      { sf::Keyboard::Key::Up, KB_ARROW_UP },
      //{ SDLK_AMPERSAND, KB_AMPERSAND },
      { sf::Keyboard::Key::Multiply, KB_ASTERISK },
      //{ SDLK_AT, KB_ATSYMBOL },
      //{ SDLK_CARET, KB_CIRCUMFLEX },
      //{ SDLK_COLON, KB_COLON },
      //{ SDLK_DOLLAR, KB_DOLLAR },
      //{ SDLK_EXCLAIM, KB_EXCLAMATION },
      //{ SDLK_GREATER, KB_SUPERIOR },
      //{ SDLK_HASH, KB_HASHTAG },
      //{ SDLK_LEFTPAREN, KB_LEFTPAREN },
      //{ SDLK_LESS, KB_INFERIOR },OB
      //{ SDLK_PERCENT, KB_PERCENT },
      { sf::Keyboard::Key::Add, KB_PLUS },
      { sf::Keyboard::Key::Return, KB_ENTER}
      //{ SDLK_QUESTION, KB_QUESTION },
      //{ SDLK_QUOTEDBL, KB_DOUBLEQUOTE },
      //{ SDLK_RIGHTPAREN, KB_RIGHTPAREN },
      //{ SDLK_UNDERSCORE, KB_UNDERSCORE }
    };
}
