#include "ProtocolViolationException.h"

ProtocolViolationException::ProtocolViolationException(std::string const& message)
:std::logic_error(message)
{}
//ProtocolViolationException::ProtocolViolationException(char const* message)
//:exception(message)
//{}
ProtocolViolationException::ProtocolViolationException(ProtocolViolationException const& e)
:std::logic_error(e)
{}

