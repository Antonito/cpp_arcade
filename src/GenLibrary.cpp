#if defined(__linux__) || ( __APPLE__)
#include <dlfcn.h>
#endif

#include "GenLibrary.hpp"

Library::Library(std::string const &filename) : m_filename(filename)
{
#if defined(__linux__) || ( __APPLE__)
	m_libPtr = dlopen(m_filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
#elif defined(_WIN32)
	m_libPtr = LoadLibraryA(m_filename.c_str());
#endif
	// TODO: Check m_libPtr
}

Library::Library(Library const &other) : Library(other.m_filename)
{
}

Library::~Library()
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

Library &Library::operator=(Library const &other)
{
	if (&other != this)
	{
		m_filename = other.m_filename;
		m_libPtr = other.m_libPtr;
	}
	return (*this);
}
