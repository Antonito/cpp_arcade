#include "LibSDL.hpp"

extern "C" arcade::IGfxLib* getLib();

arcade::IGfxLib* getLib()
{
	return (new arcade::LibSDL(1280, 720));
}