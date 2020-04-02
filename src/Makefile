CC=g++

all: parser.cpp tokens.cpp ir.o
	$(CC) -o compiler parser.cpp tokens.cpp ir.o

ir.o: ir.cpp ir.h
	$(CC) -c ir.cpp

clean:
	rm *.o
