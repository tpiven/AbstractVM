#ifndef AbstractVM_HPP
#define AbstractVM_HPP

#include <iostream>
#include <list>
#include <map>
#include <exception>
#include <stdexcept>
#include <regex>
#include <sstream>
#include <fstream>
#include "Operand.hpp"

#define RED "\033[0;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CLOSE "\033[0m"

class AbstractVM
{
private:
    std::list<const IOperand *> _Stack;

    OperandFactory factory;
    int _line = 0;
    bool _flag = false;
    bool _isExit = false;
    bool _fromFile = false;
    std::stringstream _out;


    struct  token {
        std::string command;
        std::string type;
        std::string number;
    }       t;

    AbstractVM();
    void _push(std::string const &value, eOperandType type);
    void _pop(std::string const &value, eOperandType type);
    void _dump(std::string const &value, eOperandType type);
    void _assert(std::string const &value, eOperandType type);
    void _add(std::string const &value, eOperandType type);
    void _sub(std::string const &value, eOperandType type);
    void _mul(std::string const &value, eOperandType type);
    void _div(std::string const &value, eOperandType type);
    void _mod(std::string const &value, eOperandType type);
    void _print(std::string const &value, eOperandType type);
    void _exit(std::string const &value, eOperandType type);
    void _clear(std::string const &value, eOperandType type);
    void _end();
    void _size(std::string const &value, eOperandType type);
    void _execute(token t);
    void parser(std::string line);
    void lexer(std::string & line);
    void _getFromFile(const char *filename);

public:

    explicit AbstractVM(int argc, const char *argv[]);
    AbstractVM &operator=(const AbstractVM &rhs);
    AbstractVM(const AbstractVM &rhs);
    ~AbstractVM();
};

#endif