/**
 * @file main.cpp
 * @brief Main driver for compiler
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Scanner.h"

int main(int argc, char **argv) {

        Scanner *scanner = new Scanner(argv[1]);
	int size;

	std::vector<token_t> tokens = scanner->tokenize(scanner->readFile(size));
 
        delete scanner;
}
