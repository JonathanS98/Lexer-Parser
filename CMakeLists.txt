cmake_minimum_required(VERSION 3.27)
project(Labb1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Labb1 main.cpp
        Header/Lexer.h
        CPP/Lexer.cpp
        Header/Parser.h
        Header/Node.h)
