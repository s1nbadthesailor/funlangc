all: main

CXXFLAGS+=-g -Wall
LDLIBS+=-lstdc++
main: main.o token.o ast.o lexer.o parser.o parser_tests.o
