#ifndef PROTOCOLVIOLATIONEXCEPTION_H
#define PROTOCOLVIOLATIONEXCEPTION_H

#include <string>
#include<stdexcept>

class ProtocolViolationException : public std::logic_error {
public:

	explicit ProtocolViolationException(std::string const& message);
	ProtocolViolationException(const ProtocolViolationException& e);

};
#endif //PROTOCOLVIOLATIONEXCEPTION_H
