#ifndef GENNETWORK_HPP_
#define GENNETWORK_HPP_

#include <cstdint>

#if defined(__linux__)

typedef int					sock_t;
typedef struct sockaddr_in	sockaddr_in_t;
typedef struct sockaddr		sockaddr_t;
typedef struct in_addr		in_addr_t;

#elif defined(_WIN32)

#include <winsock2.h>

typedef SOCKET				sock_t;
typedef struct SOCKADDR_IN	sockaddr_in_t;
typedef struct SOCKADDR		sockaddr_t;
typedef struct IN_ADDR		in_addr_t;

#else

#error "Network is not supported for this plateform"

#endif

#endif // !GENNETWORK_HPP_
