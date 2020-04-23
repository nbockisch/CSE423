CC=g++
CFLAGS=-std=c++11 -Wall -g

TARGETS = lexer compiler

DEPENDS = tokens.o ir.o symtable.o X86.o node.h nodevisitor.h printvisitor.h symvisitor.h

all: $(TARGETS)

lexer: tokens.l
	lex -o tokens.cpp $^

compiler: parser.o $(DEPENDS)
	$(CC) $(CFLAGS) -o $@ $^

parser.o: parser.y
	bison -Wall -d -o parser.cpp parser.y
	$(CC) $(CFLAGS) -c parser.cpp

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
#Remove auto generated BISON files to force re-generation next time
	rm parser.hpp
	rm parser.cpp
	rm $(TARGETS)

