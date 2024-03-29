#include <iostream>
#include <sstream>
#include "GenLibrary.hpp"
#include "RessourceError.hpp"

namespace arcade
{
  GenLibrary::GenLibrary() : m_filename(""), m_name(""), m_libPtr(nullptr)
  {
  }

  GenLibrary::GenLibrary(std::string const &filename, std::string const &name) :
    m_filename(filename),
    m_name(name)
  {
    this->load(filename);
  }

  GenLibrary::GenLibrary(GenLibrary const &other)
      : GenLibrary(other.m_filename, other.m_name)
  {
  }

  GenLibrary::~GenLibrary()
  {
    if (m_libPtr)
      {
#if defined(__linux__) || (__APPLE__)
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

  void GenLibrary::load(std::string const &filename)
  {
    m_filename = filename;
#if defined(__linux__) || (__APPLE__)
    m_libPtr = dlopen(m_filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (!m_libPtr)
      {
	throw RessourceError("Cannot load '" + m_filename + "' ! Error : " +
	                     dlerror());
      }
#elif defined(_WIN32)
    m_libPtr = LoadLibraryA(m_filename.c_str());
    if (!m_libPtr)
      {
	std::stringstream ss;

	ss << "Cannot load '" << m_filename
	   << "' ! Error : " << GetLastError();
	throw RessourceError(ss.str());
      }
#endif
  }

  std::string GenLibrary::getName() const
  {
    if (m_name.size() < 14)
      return ("");
    return (m_name.substr(11).substr(0, m_name.size() - 14));
  }
}