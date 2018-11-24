#include "AVM_Exception.hpp"

AVM_Exception::InputException::InputException(const std::string msg) : logic_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::InputException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::InputException::~InputException() = default;


AVM_Exception::OverflowException::OverflowException(const std::string msg) : overflow_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::OverflowException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::OverflowException::~OverflowException() = default;


AVM_Exception::UnderflowException::UnderflowException(const std::string msg) : underflow_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::UnderflowException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::UnderflowException::~UnderflowException() = default;


AVM_Exception::FloatingPointException::FloatingPointException(const std::string msg)  : range_error(msg) {
    _error_message = msg;
}
const char* AVM_Exception::FloatingPointException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::FloatingPointException::~FloatingPointException() = default;


AVM_Exception::StackException::StackException(const std::string msg) :  runtime_error(msg) {
    _error_message = msg;
}
const char* AVM_Exception::StackException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::StackException::~StackException() = default;


AVM_Exception::ZeroException::ZeroException(const std::string msg) : runtime_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::ZeroException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::ZeroException::~ZeroException() = default;


AVM_Exception::AssertionException::AssertionException(const std::string msg) : runtime_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::AssertionException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::AssertionException::~AssertionException() = default;


AVM_Exception::WrongExitException::WrongExitException(const std::string msg) : logic_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::WrongExitException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::WrongExitException::~WrongExitException() = default;


AVM_Exception::NoExitException::NoExitException(const std::string msg) : logic_error(msg) {
    _error_message = msg;
}
const char *AVM_Exception::NoExitException::what() const noexcept {
    return _error_message.c_str();
}
AVM_Exception::NoExitException::~NoExitException() = default;
