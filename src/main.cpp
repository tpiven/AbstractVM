#include <iostream>
#include "AbstractVM.hpp"

int main(int argc, const char *argv[]) {
    if (argc <= 3)
        AbstractVM AbstractVM(argc, argv);
   else
       std::cout << "usage: ./avm  [-d][filename]" << std::endl;
   return 0;
}


