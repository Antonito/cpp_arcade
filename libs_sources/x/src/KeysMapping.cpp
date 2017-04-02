#include <X11/keysym.h>
#include "LibX.hpp"

namespace arcade
{
  void LibX::setKeyMapping() const
  {
    std::function<void(int, KeyboardKey)> set = [this](int keysym, KeyboardKey key) {
      m_kb_keys[XKeysymToKeycode(m_disp, keysym)] = key;
    };

    set(XK_BackSpace, KB_BACKSPACE);
    set(XK_Tab, KB_TAB);
    set(XK_Return, KB_ENTER);
    set(XK_Escape, KB_ESCAPE);
    set(XK_Delete, KB_DELETE);
    set(XK_Home, KB_HOME);
    set(XK_Left, KB_ARROW_LEFT);
    set(XK_Up, KB_ARROW_UP);
    set(XK_Right, KB_ARROW_RIGHT);
    set(XK_Down, KB_ARROW_DOWN);
    set(XK_KP_Space, KB_SPACE);
    set(XK_KP_Tab, KB_TAB);
    set(XK_KP_Enter, KB_ENTER);
    set(XK_KP_F1, KB_FN1);
    set(XK_KP_F2, KB_FN2);
    set(XK_KP_F3, KB_FN3);
    set(XK_KP_F4, KB_FN4);
    set(XK_KP_Home, KB_HOME);
    set(XK_KP_Left, KB_ARROW_LEFT);
    set(XK_KP_Up, KB_ARROW_UP);
    set(XK_KP_Right, KB_ARROW_RIGHT);
    set(XK_KP_Down, KB_ARROW_DOWN);
    set(XK_KP_Page_Up, KB_PAGEUP);
    set(XK_KP_Page_Down, KB_PAGEDOWN);
    set(XK_KP_Delete, KB_DELETE);
    set(XK_KP_Equal, KB_EQUALS);
    set(XK_KP_Multiply, KB_ASTERISK);
    set(XK_KP_Add, KB_PLUS);
    set(XK_KP_Subtract, KB_MINUS);
    set(XK_KP_Divide, KB_SLASH);
    set(XK_KP_0, KB_0);
    set(XK_KP_1, KB_1);
    set(XK_KP_2, KB_2);
    set(XK_KP_3, KB_3);
    set(XK_KP_4, KB_4);
    set(XK_KP_5, KB_5);
    set(XK_KP_6, KB_6);
    set(XK_KP_7, KB_7);
    set(XK_KP_8, KB_8);
    set(XK_KP_9, KB_9);
    set(XK_space, KB_SPACE);
    set(XK_exclam, KB_EXCLAMATION);
    set(XK_quotedbl, KB_DOUBLEQUOTE);
    set(XK_dollar, KB_DOLLAR);
    set(XK_percent, KB_PERCENT);
    set(XK_ampersand, KB_AMPERSAND);
    set(XK_apostrophe, KB_SIMPLEQUOTE);
    set(XK_quoteright, KB_SIMPLEQUOTE);
    set(XK_parenleft, KB_LEFTPAREN);
    set(XK_parenright, KB_RIGHTPAREN);
    set(XK_asterisk, KB_ASTERISK);
    set(XK_plus, KB_PLUS);
    set(XK_comma, KB_COMMA);
    set(XK_minus, KB_MINUS);
    set(XK_period, KB_DOT);
    set(XK_slash, KB_SLASH);
    set(XK_0, KB_0);
    set(XK_1, KB_1);
    set(XK_2, KB_2);
    set(XK_3, KB_3);
    set(XK_4, KB_4);
    set(XK_5, KB_5);
    set(XK_6, KB_6);
    set(XK_7, KB_7);
    set(XK_8, KB_8);
    set(XK_9, KB_9);
    set(XK_A, KB_A);
    set(XK_a, KB_A);
    set(XK_B, KB_B);
    set(XK_b, KB_B);
    set(XK_C, KB_C);
    set(XK_c, KB_C);
    set(XK_D, KB_D);
    set(XK_d, KB_D);
    set(XK_E, KB_E);
    set(XK_e, KB_E);
    set(XK_F, KB_F);
    set(XK_f, KB_F);
    set(XK_G, KB_G);
    set(XK_g, KB_G);
    set(XK_H, KB_H);
    set(XK_h, KB_H);
    set(XK_I, KB_I);
    set(XK_i, KB_I);
    set(XK_J, KB_J);
    set(XK_j, KB_J);
    set(XK_K, KB_K);
    set(XK_k, KB_K);
    set(XK_L, KB_L);
    set(XK_l, KB_L);
    set(XK_M, KB_M);
    set(XK_m, KB_M);
    set(XK_N, KB_N);
    set(XK_n, KB_N);
    set(XK_O, KB_O);
    set(XK_o, KB_O);
    set(XK_P, KB_P);
    set(XK_p, KB_P);
    set(XK_Q, KB_Q);
    set(XK_q, KB_Q);
    set(XK_R, KB_R);
    set(XK_r, KB_R);
    set(XK_S, KB_S);
    set(XK_s, KB_S);
    set(XK_T, KB_T);
    set(XK_t, KB_T);
    set(XK_U, KB_U);
    set(XK_u, KB_U);
    set(XK_V, KB_V);
    set(XK_v, KB_V);
    set(XK_W, KB_W);
    set(XK_w, KB_W);
    set(XK_X, KB_X);
    set(XK_x, KB_X);
    set(XK_Y, KB_Y);
    set(XK_y, KB_Y);
    set(XK_Z, KB_Z);
    set(XK_z, KB_Z);
    set(XK_braceleft, KB_LEFTBRACE);
    set(XK_braceright, KB_RIGHTBRACE);
    set(XK_bar, KB_VERTICALBAR);
    set(XK_bracketleft, KB_LEFTBRACKET);
    set(XK_bracketright, KB_RIGHTBRACKET);
    set(XK_backslash, KB_BACKSLASH);
    set(XK_asciicircum, KB_CIRCUMFLEX);
    set(XK_underscore, KB_UNDERSCORE);
    set(XK_colon, KB_COLON);
    set(XK_semicolon, KB_SEMICOLON);
    set(XK_equal, KB_EQUALS);
    set(XK_less, KB_INFERIOR);
    set(XK_greater, KB_SUPERIOR);
    set(XK_question, KB_QUESTION);
    set(XK_at, KB_ATSYMBOL);
  }
  // Mapping caca Mouse Button with MouseKey enum
  std::map<int, MouseKey> LibX::m_mouse_keys =
    {
      { -1, M_LEFT_CLICK },
      { -1, M_MIDDLE_CLICK },
      { -1, M_RIGHT_CLICK },
      { -1, M_SCROLL_UP },
      { -1, M_SCROLL_DOWN },
      { -1, M_BT0 },
      { -1, M_BT1 }
    };

  // Mapping caca keyboard map
  std::map<int, KeyboardKey> LibX::m_kb_keys = {};
}
