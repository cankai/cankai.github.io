#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception{

public :
	Exception(const std::string& cause) : m_cause(cause){};

	virtual ~Exception() throw() {};
	virtual const char* what() const throw() { return m_cause.c_str(); };

protected:
	std::string m_cause;
};

class InitException : public Exception{
public:
	InitException(const std::string& what) : Exception(what){};
};

class ProtocolException : public Exception{
public:
	ProtocolException(const std::string& what) : Exception(what){};
};

class command_buffer_underflow_exception : public Exception{
public:
	command_buffer_underflow_exception(const std::string& what) : Exception(what){};
};

class command_buffer_overflow_exception : public Exception{
public:
	command_buffer_overflow_exception(const std::string& what) : Exception(what){};
};

class invalid_data_exception : public Exception
{
public:
	invalid_data_exception(const std::string& what) : Exception(what){}
};

#endif

