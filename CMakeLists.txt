cmake_minimum_required(VERSION 3.9)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 11)
include_directories(includes)

add_executable(AbstractVM src/main.cpp
        src/AbstractVM.cpp
        src/AVM_Exception.cpp
        src/OperandFactory.cpp
       )