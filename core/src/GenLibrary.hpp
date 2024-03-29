#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#if defined(__linux__) || (__APPLE__)
#include <dlfcn.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

#include <string>
#include <functional>

namespace arcade
{
// Uniform type declaration
#if defined(__linux__) || (__APPLE__)
  typedef void *gen_lib_t;
#elif defined(_WIN32)
  typedef HINSTANCE    gen_lib_t;
#else
#error "Unsupported dynamic library format"
#endif

  class GenLibrary
  {
  public:
    GenLibrary();
    GenLibrary(std::string const &filename, std::string const &name);
    GenLibrary(GenLibrary const &);
    ~GenLibrary();
    GenLibrary &operator=(GenLibrary const &);

    void load(std::string const &filename);

    // Allows someone to load a function form a .so or .dll
    template <typename T>
    std::function<T> getFunction(std::string const &sym) const
    {
#if defined(__linux__) || (__APPLE__)
      std::function<T> func =
          reinterpret_cast<T *>(dlsym(m_libPtr, sym.c_str()));
#elif defined(_WIN32)
      std::function<T> func =
          reinterpret_cast<T *>(GetProcAddress(m_libPtr, sym.c_str()));
#endif
      return (func);
    }

    std::string getName() const;

  private:
    std::string m_filename;
    std::string m_name;
    gen_lib_t   m_libPtr;
  };
}

#endif // !LIBRARY_HPP_
