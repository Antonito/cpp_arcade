#include <iostream>
#include "GenLibrary.hpp"

namespace arcade
{
	GenLibrary::GenLibrary(std::string const &filename) : m_filename(filename)
	{
#if defined(__linux__) || ( __APPLE__)
		m_libPtr = dlopen(m_filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
		if (!m_libPtr)
		{
			std::cerr << dlerror() << std::endl;
		}
#elif defined(_WIN32)
		m_libPtr = LoadLibraryA(m_filename.c_str());
#endif
		// TODO: Check m_libPtr (no such file)
	}

	GenLibrary::GenLibrary(GenLibrary const &other) : GenLibrary(other.m_filename)
	{
	}

	GenLibrary::~GenLibrary()
	{
		if (m_libPtr)
		{
#if defined(__linux__) || ( __APPLE__)
			dlclose(m_libPtr);
#elif defined(_WIN32)
			FreeLibrary(m_libPtr);
#endif
			m_libPtr = nullptr;
		}
	}

	GenLibrary &GenLibrary::operator=(GenLibrary const &other)
	{
		if (&other != this)
		{
			m_filename = other.m_filename;
			m_libPtr = other.m_libPtr;
		}
		return (*this);
	}
}