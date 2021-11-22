cmake_minimum_required(VERSION 2.6)
project(first_order_language)

set (SOURCES "./sources/main.cpp"
             "./sources/signature.cpp"
             "./sources/lexer.cpp"
             "./sources/predicate.cpp"
             "./sources/function.cpp"
             )

set (HEADERS "./include/signature.hpp"
             "./include/default.hpp"
             "./include/predicate.hpp"
             "./include/function.hpp"
             "./include/lexer.hpp"
            )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra --std=c++2a")

add_executable(first_order_language ${SOURCES})
