#include "OperandFactory.hpp"
#include "AVM_Exception.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory() {}
OperandFactory::~OperandFactory() {}
OperandFactory::OperandFactory(const OperandFactory &rhs) {
    *this = rhs;
}
OperandFactory& OperandFactory::operator=(const OperandFactory &rhs) = default;

const IOperand * OperandFactory::createInt8(const std::string &value) const {
    if (std::stod(value) < std::numeric_limits<int8_t>::min())
        throw AVM_Exception::UnderflowException("Int8 underflow");
    if(std::stod(value) > std::numeric_limits<int8_t>::max())
        throw AVM_Exception::OverflowException("Int16 overflow");
    return new Operand<int8_t>(static_cast<int8_t>(std::stoi(value)), Int8);

}

const IOperand * OperandFactory::createInt16(const std::string &value) const {
    if (std::stod(value) < std::numeric_limits<int16_t>::min())
        throw AVM_Exception::UnderflowException("Int16 underflow");
    if(std::stod(value) > std::numeric_limits<int16_t>::max())
        throw AVM_Exception::OverflowException("Int16 overflow");
    return new Operand<int16_t>(static_cast<int16_t>(std::stoi(value)), Int16);

}

const IOperand * OperandFactory::createInt32(const std::string &value) const {
    if (std::stod(value) < std::numeric_limits<int32_t>::min())
        throw AVM_Exception::UnderflowException("Int32 underflow");
    if(std::stod(value) > std::numeric_limits<int32_t>::max())
        throw AVM_Exception::OverflowException("Int32 overflow");
    return new Operand<int32_t>(static_cast<int32_t>(std::stoi(value)), Int32);
}
const IOperand * OperandFactory::createFloat(const std::string &value) const {
    if (std::stod(value) < std::numeric_limits<float>::min())
        throw AVM_Exception::FloatingPointException("Float underflow");
    if(std::stod(value) > std::numeric_limits<float>::max())
        throw AVM_Exception::FloatingPointException("Float overflow");
    return new Operand<float>(std::stof(value), Float);
}

const IOperand * OperandFactory::createDouble(const std::string &value) const {
    return new Operand<double>(std::stod(value), Double);
}

const IOperand * OperandFactory::createOperand(eOperandType type, const std::string &value) const {
    IOperand const *((OperandFactory::*arrayFunction[]))(std::string const &value) const {
        &OperandFactory::createInt8,
        &OperandFactory::createInt16,
        &OperandFactory::createInt32,
        &OperandFactory::createFloat,
        &OperandFactory::createDouble};
    return (this->*arrayFunction[type])(value);
}

