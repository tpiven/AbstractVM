//
// Created by Таня on 23.11.2018.
//

#ifndef AVM_EXCEPTION_HPP
#define AVM_EXCEPTION_HPP

#include <exception>
#include <iostream>


class AVM_Exception
{
public:
    class InputException : public std::logic_error
    {
        std::string _error_message;

    public:
        InputException(const std::string msg);
        const char *what() const noexcept  override;
        ~InputException() override;
    };

    class OverflowException : public std::overflow_error
    {

        std::string _error_message;

    public:
        explicit OverflowException(const std::string msg);
        const char *what() const noexcept  override;
        ~OverflowException() override;
    };

    class UnderflowException : public std::underflow_error
    {
        std::string _error_message;

    public:
        explicit UnderflowException(const std::string msg);
        const char *what() const noexcept  override;
        ~UnderflowException() override;
    };

    class FloatingPointException : public std::range_error
    {
        std::string _error_message;

    public:
        explicit FloatingPointException(const std::string msg);
        const char *what() const noexcept  override;
        ~FloatingPointException() override;
    };


    class StackException : public std::runtime_error
    {
        std::string _error_message;

    public:
        explicit StackException(const std::string msg);
        const char *what() const noexcept  override;
        ~StackException() override;
    };

    class ZeroException : public std::runtime_error
    {
        std::string _error_message;

    public:
        explicit ZeroException(const std::string msg);
        const char *what() const noexcept  override;
        ~ZeroException() override;
    };

    class AssertionException : public std::runtime_error
    {
        std::string _error_message;

    public:
        explicit AssertionException(const std::string msg);
        const char *what() const noexcept  override;
        ~AssertionException()  override;
    };

    class WrongExitException : public std::logic_error
    {
        std::string _error_message;

    public:
        explicit WrongExitException(const std::string msg);
        const char *what() const noexcept override;
        ~WrongExitException() override;
    };
    class NoExitException : public std::logic_error
    {
        std::string _error_message;

    public:
        explicit NoExitException(const std::string msg);
        const char *what() const noexcept override;
        ~NoExitException() override;
    };
};

#endif