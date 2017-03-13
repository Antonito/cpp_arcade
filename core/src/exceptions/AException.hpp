#ifndef AEXCEPTION_HPP_
#define AEXCEPTION_HPP_

#include <stdexcept>
#include <string>

class AException : public std::exception
{
public:
	AException(AException const &other);
	~AException() throw() = 0;

	AException &operator=(AException const &other);
	char const *what() const throw();

protected:
	AException(std::string const &spe, std::string const &msg);

private:
	std::string m_message;
};

#endif // !AEXCEPTION_HPP_
