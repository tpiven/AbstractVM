#include "AbstractVM.hpp"

AbstractVM::AbstractVM() = default;

AbstractVM::AbstractVM(int argc, const char *argv[]) {
    std::string str;
   const char *filename;

    if (argc == 1) {
        while (getline(std::cin, str))
            parser(str);
        try {
            if (!_isExit) {
                _isExit = !_isExit;
                throw AVM_Exception::NoExitException("No \"exit\" command");
            } else {
                _end();
            }
        }
        catch (AVM_Exception::NoExitException &exception) {
            if (_flag)
                _out << BLUE << "Line " << _line << ": " << CLOSE;
            _out << RED << "Exit Exception: " << exception.what() << CLOSE << std::endl;
            _end();
        }
    }
    else if (argc == 2 && argv[1][0] != '-' && argv[1][1] != 'd')
        filename = argv[1];
    else if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'd')
    {
        _flag = true;
        while (getline(std::cin, str))
            parser(str);
        try {
            if (!_isExit) {
                _isExit = !_isExit;
                throw AVM_Exception::NoExitException("No \"exit\" command");
            } else {
                _end();
            }
        }
        catch (AVM_Exception::NoExitException &exception) {
            if (_flag)
                _out << BLUE << "Line " << _line << ": " << CLOSE;
            _out << RED << "Exit Exception: " << exception.what() << CLOSE << std::endl;
            _end();
        }
    }
    else {
        filename = argv[2];
        _flag = true;
    }
    if (argc > 1)
        _getFromFile(filename);
}

AbstractVM::~AbstractVM()
{
    _Stack.clear();
}

AbstractVM &AbstractVM::operator=(const AbstractVM &rhs)
{
    _Stack = rhs._Stack;
    return *this;
}

AbstractVM::AbstractVM(const AbstractVM &rhs)
{
    *this = rhs;
}

void AbstractVM::_getFromFile(const char *filename) {
    std::ifstream file(filename);
    std::string str;

    if (file.is_open()) {
        _fromFile = true;
        while (getline(file, str))
            parser(str);
        try {
            if (!_isExit) {
                _isExit = !_isExit;
                throw AVM_Exception::NoExitException("No \"exit\" command in file");
            } else {
                _end();
            }
        }
        catch (AVM_Exception::NoExitException &exception) {
            if (_flag)
                _out << BLUE << "Line " << _line << ": " << CLOSE;
            _out << RED << "Exit Exception: " << exception.what() << CLOSE << std::endl;
            _end();
        }
        file.close();
    } else
        std::cout << "Unable to open file" << std::endl;
}
void AbstractVM::parser(std::string line)
{
    std::cmatch result;
    if (line.empty())
        return ;
    try
    {
        lexer(line);
        std::regex r("(\\b\\d*\\.?\\d+)");
        std::regex_search(line.c_str(), result, r);
        t.number = result[1];
        std::regex r2 ("(push|assert|pop|dump|add|sub|mul|div|mod|print|exit|clear|size)");
        std::regex_search(line.c_str(), result, r2);
        t.command = result[1];
        std::regex r3("(int(8|16|32)|double|float)");
        std::regex_search(line.c_str(), result, r3);
        t.type = result[1];
        AbstractVM::_execute(t);
    }
    catch (AVM_Exception::NoExitException &exception)
    {
        if (_flag)
            _out << BLUE << "Line " << _line << ": " << CLOSE;
        _out << RED << "Exit Exception: " << exception.what() << CLOSE << std::endl;
        _end();
    }
    catch (std::exception &exception)
    {
        if (_flag)
            _out << BLUE << "Line " << _line << ": " << CLOSE;
        _out << RED << "Exception: " << exception.what() << CLOSE<< std::endl;
    }

}

void AbstractVM::_push(std::string const &value, eOperandType type)
{
     const IOperand *operand = factory.createOperand(type, value);
    _Stack.push_front(operand);
    if (_flag)
        _out << BLUE << "Line " << _line << ": "<< CLOSE <<  "push " << value  << std::endl;
};

void AbstractVM::_pop(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.empty())
    {
        throw AVM_Exception::StackException("Instruction \"pop\" on an empty stack");
    }
    delete(_Stack.front());
    _Stack.pop_front();
    if (_flag)
        _out << BLUE << "Line " << _line << ": "<< CLOSE <<  "pop" << std::endl;

}

void AbstractVM::_assert(std::string const &value, eOperandType type) {
    (void) type;
    if (_Stack.empty()) {
        throw AVM_Exception::StackException("Instruction \"asert\" on an empty stack");
    }
    const IOperand *op = *(_Stack.begin());
    if (op->toString() != value) {
        throw AVM_Exception::AssertionException("Wrong value in assert!");

    }
    if (_flag)
        _out << BLUE << "Line " << _line << ": "<< CLOSE <<  "assert " << value << std::endl;
}

void AbstractVM::_add(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.size() < 2) {
        throw AVM_Exception::StackException("Insufficient values");
    }
    const IOperand* one = _Stack.front();
    _Stack.pop_front();
    const IOperand* two = _Stack.front();
    _Stack.pop_front();
    const IOperand* result  = *two + *one;
    delete one;
    delete two;
    _Stack.push_front(result);
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "add" << std::endl;
}

void AbstractVM::_sub(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.size() < 2) {
        throw AVM_Exception::StackException("Insufficient values");
    }
    const IOperand* one = _Stack.front();
    _Stack.pop_front();
    const IOperand* two = _Stack.front();
    _Stack.pop_front();
    const IOperand* result  = *two - *one;
    delete one;
    delete two;
    _Stack.push_front(result);
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "sub" << std::endl;
}

void AbstractVM::_mul(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.size() < 2) {
        throw AVM_Exception::StackException("Insufficient values");
    }
    const IOperand* one = _Stack.front();
    _Stack.pop_front();
    const IOperand* two = _Stack.front();
    _Stack.pop_front();
    const IOperand* result  = *one * *two;
    delete one;
    delete two;
    _Stack.push_front(result);
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "mul" << std::endl;
}

void AbstractVM::_div(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.size() < 2) {
        throw AVM_Exception::StackException("Insufficient values");
    }
    const IOperand* one = _Stack.front();
    _Stack.pop_front();
    const IOperand* two = _Stack.front();
    _Stack.pop_front();
    const IOperand* result  = *two / *one;
    delete one;
    delete two;
    _Stack.push_front(result);
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "div" << std::endl;
}

void AbstractVM::_mod(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.size() < 2) {
        throw AVM_Exception::StackException("Insufficient values");
    }
    const IOperand* one = _Stack.front();
    _Stack.pop_front();
    const IOperand* two = _Stack.front();
    _Stack.pop_front();
    const IOperand* result  = *two % *one;
    delete one;
    delete two;
    _Stack.push_front(result);
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "mod" << std::endl;
}

void AbstractVM::lexer(std::string &line)
{
    _line++;
    if (_isExit && line != ";;")
        throw(AVM_Exception::WrongExitException("The program has an \"exit\" instruction"));
    if (line == ";;")
    {
        if (_isExit && !_fromFile)
            _end();
        else if (!_isExit && !_fromFile)
        {
            _isExit = true;
            throw AVM_Exception::NoExitException("The program does not have an exit instruction");
        }
    }
    std::regex reg("(^[\\s]*?(((push|assert)\\s*?((int((8|16|32)\\([-]?\\d+?\\)))|"
                   "((double|float)\\(([-]?\\d+?\\.?\\d+?\\)))))|pop|dump|add|sub|mul|div|mod|print|exit|clear|size)\\s*?((?=[\\;]).*|$))");
    if (!std::regex_match(line.begin(), line.end(), reg) && !line.empty())
        throw AVM_Exception::InputException("Unknown instruction or invalid input");
    line = line.substr(0, line.find(';', 0));
}

void AbstractVM::_dump(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.empty())
        throw AVM_Exception::StackException("Instruction \"dump\" on an empty stack");
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "dump" << std::endl;
    for (auto iterator = _Stack.begin(); iterator != _Stack.end(); iterator++)
    {
        _out << GREEN << ((*iterator)->toString()) << CLOSE << std::endl;
    }
};

void AbstractVM::_print(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_Stack.empty())
        throw AVM_Exception::StackException("Instruction \"print\" on an empty stack");
    else if (_Stack.front()->getType() == Int8)
    {
        if(_flag)
            _out << BLUE << "Line " << _line << ": " << CLOSE << "print" << std::endl;
        _out << YELLOW << static_cast<char>(std::stoi(_Stack.front()->toString())) << CLOSE << std::endl;

    }
    else
        throw AVM_Exception::AssertionException("Printing failed, the first operand in stack is not Int8");
}

void AbstractVM::_exit(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if (_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "exit" << std::endl;
    _isExit = true;
}

void AbstractVM::_end()
{
    if (!_isExit && !_fromFile)
    {
        std::cout << _out.str();
        throw(AVM_Exception::WrongExitException("The program does not have an exit instruction"));

    }
    std::cout << _out.str();
    exit(0);
}


void AbstractVM::_execute(token t)
{
    std::map<std::string, void (AbstractVM::*)(std::string const &, eOperandType type)> commands =
            {
                    {"add", &AbstractVM::_add},
                    {"dump", &AbstractVM::_dump},
                    {"print", &AbstractVM::_print},
                    {"pop", &AbstractVM::_pop},
                    {"sub", &AbstractVM::_sub},
                    {"mul", &AbstractVM::_mul},
                    {"div", &AbstractVM::_div},
                    {"mod", &AbstractVM::_mod},
                    {"size", &AbstractVM::_size},
                    {"exit", &AbstractVM::_exit},
                    {"push", &AbstractVM::_push},
                    {"size", &AbstractVM::_size},
                    {"clear", &AbstractVM::_clear},
                    {"assert", &AbstractVM::_assert}
            };
    std::map<std::string, eOperandType> types =
            {
                    {"int8", Int8},
                    {"int16", Int16},
                    {"int32", Int32},
                    {"float", Float},
                    {"double", Double}};
    (this->*commands[t.command])(t.number, types[t.type]);

}


void AbstractVM::_size(std::string const &value, eOperandType type)
{
    (void)value;
    (void)type;
    if(_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << std::endl;
    _out << GREEN  << "size:  " << _Stack.size() << CLOSE <<std::endl;
}

void AbstractVM::_clear(std::string const &value, eOperandType type) {
    (void) value;
    (void) type;

    for (auto elem = this->_Stack.begin(); elem != this->_Stack.end(); ++elem) {
        delete (*elem);
    }
    this->_Stack.clear();
    if(_flag)
        _out << BLUE << "Line " << _line << ": " << CLOSE << "clear" << std::endl;

}

