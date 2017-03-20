#if defined(_WIN32)
#include <Windows.h>
#include <cstdbool>
#endif
#include "IGame.hpp"
#include "Snake.hpp"

#if defined(__linux__) || (__APPLE__)
#define GAME_API
#else
#define GAME_API __declspec(dllexport)
#endif

#include <iostream>
extern "C"
{
	GAME_API arcade::IGame * getGame()
	{
		return (new arcade::Snake());
	}

#if defined(_WIN32)
	BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
	{
		return (true);
	}
#endif
}