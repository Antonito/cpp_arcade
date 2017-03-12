#ifndef GENNETWORK_HPP_
#define GENNETWORK_HPP_

#include <cstddef>
#include <cstdint>

#if defined(__linux__) || defined(__APPLE__)

#define closesocket(s)		close(s)

typedef int					sock_t;
typedef struct sockaddr_in	sockaddr_in_t;
typedef struct sockaddr		sockaddr_t;
typedef struct in_addr		in_addr_t;

#elif defined(_WIN32)

// Prevent inclusion of winsock.h in windows.h
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS // TODO: Remove

#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

typedef SOCKET				sock_t;
typedef SOCKADDR_IN			sockaddr_in_t;
typedef SOCKADDR			sockaddr_t;
typedef IN_ADDR				in_addr_t;
typedef SSIZE_T				ssize_t;
#else

#error "Network is not supported for this plateform"

#endif

#endif // !GENNETWORK_HPP_
