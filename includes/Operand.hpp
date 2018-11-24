#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include <cmath>
#include <exception>
#include "IOperand.hpp"
#include "AVM_Exception.hpp"
#include "OperandFactory.hpp"

template <class T>
class Operand : public IOperand
{
private:
    T _value;
    OperandFactory factory;
    eOperandType _type;
    std::string  str;
    Operand<T>(void);
    Operand<T>(Operand<T> const & o) { *this = o; }
    Operand<T> & operator=(Operand<T> const & ) {}

public:
    Operand(T val, eOperandType type) : _value(val), _type(type) {
        str = std::to_string(_value);
    };
    int getPrecision() const {
        return this->_type;
    }
    eOperandType getType() const {
        return this->_type;
    }
    std::string const &toString() const {
        return str;
    }

    IOperand const * operator+( IOperand const & rhs ) const {
        eOperandType	precision;

        precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
        return this->factory.createOperand(precision, std::to_string(this->_value + std::stod(rhs.toString())));
    }

    IOperand const *operator-(IOperand const &rhs) const {
        eOperandType	precision;

        precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
        return this->factory.createOperand(precision, std::to_string(this->_value - std::stod(rhs.toString())));
    }
    IOperand const *operator*(IOperand const &rhs) const {
        eOperandType	precision;

        precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
        return this->factory.createOperand(precision, std::to_string(this->_value * std::stod(rhs.toString())));
    }
    IOperand const *operator/(IOperand const &rhs) const {
        if(std::stod(rhs.toString()) == 0)
            throw AVM_Exception::ZeroException("Division by zero");

        eOperandType	precision;

        precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
        return this->factory.createOperand(precision, std::to_string(this->_value / std::stod(rhs.toString())));
    }
    IOperand const *operator%(IOperand const &rhs) const {
        if(std::stod(rhs.toString()) == 0)
            throw AVM_Exception::ZeroException("Modulo by zero");
        eOperandType	precision;

        precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
        return this->factory.createOperand(precision, std::to_string(std::fmod(this->_value, std::stod(rhs.toString()))));
    }
};

#endif

