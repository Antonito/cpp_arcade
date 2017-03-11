#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <string>
#include <functional>

#if defined(__linux__) || ( __APPLE__)
typedef void * gen_lib_t;
#elif defined(_WIN32)
typedef HINSTANCE gen_lib_t;
#else 
#error "Unsupported dynamic library format"
#endif

class Library
{
public:
	explicit Library(std::string const &filename);
	Library(Library const &);
	~Library();
	Library &operator=(Library const &);

	template<typename T>
	std::function<T> getFunction(std::string const &sym) const
	{
#if defined(__linux__) || ( __APPLE__)
		std::function<T> func = dlsym(m_libPtr, sym.c_str());
#elif defined(_WIN32)
		std::function<T> func = GetProcAddress(m_libPtr, sym.c_str());
#endif
		return (func);
	}

private:
	std::string		m_filename;
	gen_lib_t		m_libPtr;
};

#endif // !LIBRARY_HPP_
