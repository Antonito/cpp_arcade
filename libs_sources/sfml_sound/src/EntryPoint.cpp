#if defined(_WIN32)
#include <Windows.h>
#include <cstdbool>
#endif
#include "LibSFMLSound.hpp"
#include "IGfxLib.hpp"

#if defined(__linux__) || (__APPLE__)
#define GFXLIB_API
#else
#define GFXLIB_API __declspec(dllexport)
#endif

#include <iostream>
extern "C" {
GFXLIB_API arcade::IGfxLib *getLib()
{
  return (new arcade::LibSFMLSound());
}

#if defined(_WIN32)
BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
{
  return (true);
}
#endif
}
