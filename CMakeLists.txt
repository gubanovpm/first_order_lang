cmake_minimum_required(VERSION 3.10)
project(first_order_language)

set (SOURCES "./sources/main.cpp"
             "./sources/signature.cpp"
             "./sources/lexer.cpp"
             "./sources/predicate.cpp"
             "./sources/function.cpp"
             "./sources/term.cpp"
             "./sources/formula.cpp"
             "./sources/finite_interpretation.cpp"
             )

set (HEADERS "./include/signature.hpp"
             "./include/default.hpp"
             "./include/predicate.hpp"
             "./include/function.hpp"
             "./include/lexer.hpp"
             "./include/term.hpp"
             "./include/formula.hpp"
             "./include/finite_interpretation.hpp"
            )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 --std=c++2a")

add_executable(first_order_language ${SOURCES})
