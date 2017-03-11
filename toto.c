#include <stdio.h>

#if defined(__linux__) || (__APPLE__)
#define TOTO_API
#else
#define TOTO_API __declspec(dllexport)
#endif

TOTO_API int	my_print(char const *str)
{
  printf("%s\n", str);
  return (1337);
}

#if defined(_WIN32)
#include <Windows.h>
#include <stdbool.h>

BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
 {
  return true;
 }
#endif
