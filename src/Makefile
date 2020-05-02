CC=g++
CPPFLAGS=-std=c++11 -Wall -g

ifdef RUN_TESTS
CPPFLAGS := $(CPPFLAGS) -DRUN_TESTS
endif

TARGETS = lexer compiler

DEPENDS = tokens.cpp ir.cpp symtable.cpp X86.cpp node.h nodevisitor.h printvisitor.h symvisitor.h

all: $(TARGETS)

lexer: tokens.l
	lex -o tokens.cpp $^

compiler: parser.o $(DEPENDS)
	$(CC) $(CPPFLAGS) -o $@ $^

tests:
	$(MAKE) RUN_TESTS=1 all

parser.o: parser.y
	bison -Wall -d -o parser.cpp parser.y
	$(CC) $(CPPFLAGS) -c parser.cpp

#%.o : %.cpp
#	$(CC) $(CPPFLAGS) -c $<

clean:
	rm *.o
#Remove auto generated BISON files to force re-generation next time
	rm parser.hpp
	rm parser.cpp
	rm $(TARGETS)

