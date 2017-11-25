#ifndef ILLEGALAMPELSTATEEXCEPTION_H
#define ILLEGALAMPELSTATEEXCEPTION_H

#include <string>
#include<stdexcept>

class ProtocolViolationException : public std::logic_error {
public:

	explicit ProtocolViolationException(std::string const& message);
	ProtocolViolationException(const ProtocolViolationException& e);

};
#endif //ILLEGALAMPELSTATEEXCEPTION_H
