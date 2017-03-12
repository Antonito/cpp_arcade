#ifndef SOCKERROR_HPP_
#define SOCKERROR_HPP_

#include "AException.hpp"

namespace Network
{
	class SockError : public AException
	{
	public:
		SockError(std::string const &msg = "");
	};
}

#endif // !SOCKERROR_HPP_
