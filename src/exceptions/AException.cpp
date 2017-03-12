#include "AException.hpp"

AException::AException(std::string const &spe, std::string const &msg) : m_message(spe + msg)
{

}

AException::AException(AException const &other) : m_message(other.m_message)
{
}

AException::~AException() throw()
{
}

AException &AException::operator=(AException const &other)
{
	if (this != &other)
	{
		m_message = other.m_message;
	}
	return (*this);
}

char const *AException::what() const throw()
{
	return (m_message.c_str());
}