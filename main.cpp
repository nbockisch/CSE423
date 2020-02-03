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
        char *charstream = scanner->removeWhitespace(size);

        /* printf("Size: %d\n", size);
        printf("Charstream:\n");
        printf("'%s'\n", charstream); */

	std::vector<token_t> tokens = scanner->tokenize(charstream, size);

	std::cout << tokens.front().contents << '\n';
        
        delete scanner;
        free(charstream);
}
